#pragma once

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/float32.hpp>
#include <geometry_msgs/msg/twist.hpp>
#include "interfaces/msg/float32_array8.hpp"
#include "interfaces/msg/float32_array12.hpp"
#include <std_msgs/msg/float32_multi_array.hpp>
#include <mujoco/mujoco.h>
#include <GLFW/glfw3.h>
#include <thread>
#include <mutex>
#include <atomic>
#include <chrono>
#include <cstring>

class MjEttorone : public rclcpp::Node
{
public:
    MjEttorone();
    ~MjEttorone();

    void render_once();
    bool viewer_running() const;

private:
    // ================= ROS =================
    rclcpp::Publisher<interfaces::msg::Float32Array12>::SharedPtr publisher_;
    rclcpp::Publisher<interfaces::msg::Float32Array8>::SharedPtr publisher_center_vel_;
    rclcpp::Subscription<interfaces::msg::Float32Array8>::SharedPtr subscription_;
    rclcpp::CallbackGroup::SharedPtr callback_group_;

    interfaces::msg::Float32Array12 pub_msg_; 
    interfaces::msg::Float32Array8  pub_msg_center_vel_; 
    // ================= MuJoCo =================
    mjModel* model_ = nullptr;
    mjData* data_ = nullptr;
    mjData* data_render_  = nullptr;
    double dt_ = 0.0;

    // ================= Viewer =================
    int body_id;
    mjvCamera cam_;
    mjvOption opt_;
    mjvScene scn_;
    mjrContext con_;
    GLFWwindow* window_ = nullptr;

    // ================= Threading =================
    std::thread physics_thread_;
    std::mutex mutex_;
    std::atomic<bool> running_{false};

    float act_[8] = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};

    // ================= Methods =================
    void listener_callback(const interfaces::msg::Float32Array8 msg);
    void physics_loop();

    // GLFW callbacks
    static void mouse_button_callback(GLFWwindow* window, int button, int act, int mods);
    static void mouse_move_callback(GLFWwindow* window, double xpos, double ypos);
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

    // Joint IDs
    int fl_wheel_id;
    int fr_wheel_id;
    int bl_wheel_id;
    int br_wheel_id;

    int fl_steer_id;
    int fr_steer_id;
    int bl_steer_id;
    int br_steer_id;
};