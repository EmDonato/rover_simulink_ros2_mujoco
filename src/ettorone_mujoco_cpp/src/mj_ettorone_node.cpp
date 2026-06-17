#include "ettorone_mujoco_cpp/mj_ettorone_node.hpp"
#include <chrono>
#include <thread>
#include <cmath>
#include <string>

double getWheelSlipAngle(const mjModel* m, const mjData* d, const std::string& wheel_body_name)
{
    int body_id = mj_name2id(m, mjOBJ_BODY, wheel_body_name.c_str());
    if (body_id < 0) {
        return 0.0;
    }


    mjtNum vel[6];
    mj_objectVelocity(m, d, mjOBJ_BODY, body_id, vel, 0);

    double vx = vel[3];
    double vy = vel[4];
    double vz = vel[5];

    const mjtNum* xmat = d->xmat + body_id * 9;


    double forward[3] = { xmat[0], xmat[3], xmat[6] };  
    double lateral[3] = { xmat[1], xmat[4], xmat[7] }; 

    double v_forward = vx*forward[0] + vy*forward[1] + vz*forward[2];
    double v_lateral = vx*lateral[0] + vy*lateral[1] + vz*lateral[2];

    double v_planar = std::sqrt(vx*vx + vy*vy);
    if (v_planar < 0.05) {  
        return 0.0;
    }

    return std::atan2(v_lateral, v_forward);
}




// stato mouse file-local
namespace {
    bool button_left = false;
    bool button_middle = false;
    bool button_right = false;
    double lastx = 0.0;
    double lasty = 0.0;
} //            
// ================= GLFW CALLBACKS =================
void MjEttorone::mouse_button_callback(GLFWwindow* window, int, int, int) {
    button_left   = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT)   == GLFW_PRESS;
    button_middle = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS;
    button_right  = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT)  == GLFW_PRESS;
    glfwGetCursorPos(window, &lastx, &lasty);
}

void MjEttorone::mouse_move_callback(GLFWwindow* window, double xpos, double ypos) {
    auto* node = static_cast<MjEttorone*>(glfwGetWindowUserPointer(window));
    if (!node || (!button_left && !button_middle && !button_right)) return;

    double dx = xpos - lastx;
    double dy = ypos - lasty;
    lastx = xpos; lasty = ypos;

    int width, height;
    glfwGetWindowSize(window, &width, &height);
    if (height <= 0) return;

    bool mod_shift = (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ||
                      glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS);

    mjtMouse action;
    if (button_right)      action = mod_shift ? mjMOUSE_MOVE_H : mjMOUSE_MOVE_V;
    else if (button_left)  action = mod_shift ? mjMOUSE_ROTATE_H : mjMOUSE_ROTATE_V;
    else                   action = mjMOUSE_ZOOM;

    std::lock_guard<std::mutex> lock(node->mutex_);
    mjv_moveCamera(node->model_, action, dx / height, dy / height, &node->scn_, &node->cam_);
}

void MjEttorone::scroll_callback(GLFWwindow* window, double, double yoffset) {
    auto* node = static_cast<MjEttorone*>(glfwGetWindowUserPointer(window));
    if (!node) return;
    std::lock_guard<std::mutex> lock(node->mutex_);
    mjv_moveCamera(node->model_, mjMOUSE_ZOOM, 0.0, -0.05 * yoffset, &node->scn_, &node->cam_);
}

// ================= COSTRUTTORE =================
MjEttorone::MjEttorone() : Node("mj_ettorone_node") {
    callback_group_ = this->create_callback_group(rclcpp::CallbackGroupType::Reentrant);
    rclcpp::SubscriptionOptions sub_options;
    sub_options.callback_group = callback_group_;
    std::cout << "MuJoCo version: " << mj_versionString() << std::endl;



    
    // QoS ottimizzato per Simulink (500Hz Best Effort)
    publisher_ = this->create_publisher<interfaces::msg::Float32Array12>("/ettorone/feedback", rclcpp::SensorDataQoS());

    publisher_center_vel_ = this->create_publisher<interfaces::msg::Float32Array8>("/ettorone/body_vel", rclcpp::SensorDataQoS());

    subscription_ = this->create_subscription<interfaces::msg::Float32Array8>(
        "/ettorone/actuator", 10, std::bind(&MjEttorone::listener_callback, this, std::placeholders::_1), sub_options);
    
    // MUJOCO INIT
    char error[1000] = "Could not load model";
    model_ = mj_loadXML("src/ettorone_mujoco_cpp/model/ettorone.xml", nullptr, error, sizeof(error));
    if (!model_) throw std::runtime_error(error);

    // Ottimizzazioni solutore
    model_->opt.integrator = mjINT_IMPLICITFAST;
    model_->opt.iterations = 50;
    model_->opt.tolerance = 1e-5;
    body_id = mj_name2id(model_, mjOBJ_BODY, "base");

    data_ = mj_makeData(model_);
    data_render_ = mj_makeData(model_);
    dt_ = model_->opt.timestep; 

    // VIEWER INIT
    if (!glfwInit()) throw std::runtime_error("Could not initialize GLFW");

    window_ = glfwCreateWindow(1200, 900, "MuJoCo Viewer", nullptr, nullptr);
    if (!window_) { glfwTerminate(); throw std::runtime_error("Failed to create GLFW window"); }

    glfwMakeContextCurrent(window_);
    glfwSwapInterval(0); 

    glfwSetWindowUserPointer(window_, this);
    glfwSetMouseButtonCallback(window_, MjEttorone::mouse_button_callback);
    glfwSetCursorPosCallback(window_, MjEttorone::mouse_move_callback);
    glfwSetScrollCallback(window_, MjEttorone::scroll_callback);

    mjv_defaultCamera(&cam_);
    cam_.type = mjCAMERA_TRACKING;
    cam_.trackbodyid = body_id;
    cam_.distance = 2.0;

    mjv_defaultOption(&opt_);
    mjv_defaultScene(&scn_);
    mjr_defaultContext(&con_);
    mjv_makeScene(model_, &scn_, 20000);
    mjr_makeContext(model_, &con_, mjFONTSCALE_150);
    

    fl_wheel_id = mj_name2id(model_, mjOBJ_JOINT, "fl_wheel_joint");
    fr_wheel_id = mj_name2id(model_, mjOBJ_JOINT, "fr_wheel_joint");
    bl_wheel_id = mj_name2id(model_, mjOBJ_JOINT, "bl_wheel_joint");
    br_wheel_id = mj_name2id(model_, mjOBJ_JOINT, "br_wheel_joint");

    fl_steer_id = mj_name2id(model_, mjOBJ_JOINT, "fl_steering_joint");
    fr_steer_id = mj_name2id(model_, mjOBJ_JOINT, "fr_steering_joint");
    bl_steer_id = mj_name2id(model_, mjOBJ_JOINT, "bl_steering_joint");
    br_steer_id = mj_name2id(model_, mjOBJ_JOINT, "br_steering_joint");

    opt_.flags[mjVIS_JOINT] = 1;

    // (opzionale) mostra anche:
    opt_.flags[mjVIS_ACTUATOR] = 1;   // direzione attuatori
    opt_.flags[mjVIS_CONTACTPOINT] = 1;
    opt_.flags[mjVIS_CONTACTFORCE] = 1;
    opt_.frame = mjFRAME_BODY;

    running_ = true;
    physics_thread_ = std::thread(&MjEttorone::physics_loop, this);

}

MjEttorone::~MjEttorone() {
    running_ = false;
    if (physics_thread_.joinable()) physics_thread_.join();
    mjr_freeContext(&con_);
    mjv_freeScene(&scn_);
    if (window_) { glfwDestroyWindow(window_); glfwTerminate(); }
    if (data_) mj_deleteData(data_);
    if (data_render_) mj_deleteData(data_render_);
    if (model_) mj_deleteModel(model_);
}

void MjEttorone::listener_callback(const interfaces::msg::Float32Array8 msg) {
    std::lock_guard<std::mutex> lock(mutex_);
    for(int i = 0;i < 8; i++){
        act_[i] = msg.data[i];
    }
}

// ================= PHYSICS LOOP (500 HZ) =================
void MjEttorone::physics_loop() {
    using namespace std::chrono;

    const microseconds interval(2000);
    auto next_tick = high_resolution_clock::now();

    // ===== PRECOMPUTE ID (fuori dal loop) =====
    int base_joint_id = mj_name2id(model_, mjOBJ_JOINT, "base_free");
    int qadr  = model_->jnt_dofadr[base_joint_id];   // qvel index
    int qpos_adr = model_->jnt_qposadr[base_joint_id]; // qpos index
    


    while (rclcpp::ok() && running_) {

        {
            double alpha_fl = getWheelSlipAngle(model_, data_, "fl_steering_link");
            double alpha_fr = getWheelSlipAngle(model_, data_, "fr_steering_link");
            double alpha_bl = getWheelSlipAngle(model_, data_, "bl_steering_link");
            double alpha_br = getWheelSlipAngle(model_, data_, "br_steering_link");


            std::lock_guard<std::mutex> lock(mutex_);

            // ======================
            // CONTROL INPUT
            // ======================
            for (int i = 0; i < 8; i++)
                data_->ctrl[i] = act_[i];

            // ======================
            // STEP SIMULATION
            // ======================
            mj_step(model_, data_);
            mj_inverse(model_, data_);

            // ======================
            // WHEEL VELOCITIES
            // ======================
            pub_msg_.data[0] = data_->qvel[ model_->jnt_dofadr[fl_wheel_id] ];
            pub_msg_.data[1] = data_->qvel[ model_->jnt_dofadr[fr_wheel_id] ];
            pub_msg_.data[2] = data_->qvel[ model_->jnt_dofadr[bl_wheel_id] ];
            pub_msg_.data[3] = data_->qvel[ model_->jnt_dofadr[br_wheel_id] ];

            // ======================
            // STEERING ANGLES
            // ======================
            pub_msg_.data[4] = data_->qpos[ model_->jnt_qposadr[fl_steer_id] ];
            pub_msg_.data[5] = data_->qpos[ model_->jnt_qposadr[fr_steer_id] ];
            pub_msg_.data[6] = data_->qpos[ model_->jnt_qposadr[bl_steer_id] ];
            pub_msg_.data[7] = data_->qpos[ model_->jnt_qposadr[br_steer_id] ];

            // ======================
            // TORQUE
            // ======================
            int id_fl = model_->jnt_dofadr[fl_wheel_id];
            int id_fr = model_->jnt_dofadr[fr_wheel_id];
            int id_bl = model_->jnt_dofadr[bl_wheel_id];
            int id_br = model_->jnt_dofadr[br_wheel_id];

            pub_msg_.data[8]  = data_->qfrc_actuator[id_fl];
            pub_msg_.data[9]  = data_->qfrc_actuator[id_fr];
            pub_msg_.data[10] = data_->qfrc_actuator[id_bl];
            pub_msg_.data[11] = data_->qfrc_actuator[id_br];

            // ======================
            // VELOCITÀ WORLD
            // ======================
            double vx = data_->qvel[qadr + 0];
            double vy = data_->qvel[qadr + 1];

            // ======================
            // ORIENTAZIONE (yaw da quaternion)
            // qpos = [x y z qw qx qy qz]
            // ======================
            double* q = &data_->qpos[qpos_adr];

            double qw = q[3];
            double qx = q[4];
            double qy = q[5];
            double qz = q[6];

            double yaw = atan2(
                2.0 * (qw*qz + qx*qy),
                1.0 - 2.0 * (qy*qy + qz*qz)
            );

            // ======================
            // VELOCITÀ LONGITUDINALE (CORRETTA)
            // ======================
            double v_long = vx * cos(yaw) + vy * sin(yaw);

            // ======================
            // YAW RATE
            // ======================
            double wz = data_->qvel[qadr + 5];

            // ======================
            // PUBLISH
            // ======================
            pub_msg_center_vel_.data[0] = v_long;
            pub_msg_center_vel_.data[1] = wz;
            pub_msg_center_vel_.data[2] = alpha_fl;
            pub_msg_center_vel_.data[3] = alpha_fr;
            pub_msg_center_vel_.data[4] = alpha_bl;
            pub_msg_center_vel_.data[5] = alpha_br;
   

        }

        publisher_->publish(pub_msg_);
        publisher_center_vel_->publish(pub_msg_center_vel_);

        next_tick += interval;
        std::this_thread::sleep_until(next_tick);
    }
}
void MjEttorone::render_once() {
    if (!window_) return;
    glfwMakeContextCurrent(window_);

    {
        // Copia velocissima dello stato per il render asincrono
        std::lock_guard<std::mutex> lock(mutex_);
        mj_copyData(data_render_, model_, data_); 
    }

    mjrRect viewport{0, 0, 0, 0};
    glfwGetFramebufferSize(window_, &viewport.width, &viewport.height);

    // Update scena senza bloccare la fisica
    mjv_updateScene(model_, data_render_, &opt_, nullptr, &cam_, mjCAT_ALL, &scn_);
    mjr_render(viewport, &scn_, &con_);
    
    glfwSwapBuffers(window_);
    glfwPollEvents();
}

bool MjEttorone::viewer_running() const {
    return window_ && !glfwWindowShouldClose(window_);
}