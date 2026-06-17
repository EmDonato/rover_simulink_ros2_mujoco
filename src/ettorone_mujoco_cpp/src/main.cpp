#include <rclcpp/rclcpp.hpp>
#include "ettorone_mujoco_cpp/mj_ettorone_node.hpp"

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);

    auto node = std::make_shared<MjEttorone>();

    rclcpp::executors::MultiThreadedExecutor executor;
    executor.add_node(node);


    std::thread ros_thread([&executor]() {
        executor.spin();   // gira libero
    });

    rclcpp::WallRate rate(60.0);

    while (rclcpp::ok() && node->viewer_running()) {
        node->render_once();
        rate.sleep();
    }


    executor.cancel();
    rclcpp::shutdown();
    if (ros_thread.joinable())
        ros_thread.join();
    return 0;
}