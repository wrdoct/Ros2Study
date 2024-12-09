#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/transform_stamped.hpp" // 提供消息接口
#include "tf2/LinearMath/Quaternion.h"             // 提供tf2::Quaternion类
#include "tf2_geometry_msgs/tf2_geometry_msgs.hpp" // 消息类型转换函数
#include "tf2_ros/transform_listener.h"            // 坐标监听类
#include "tf2_ros/buffer.h"                        // 提供Buffer
#include "tf2/utils.h"                             // 提供了四元数转欧拉角
#include <chrono>

using namespace std::chrono_literals;

class TFListener : public rclcpp::Node
{
private:
    std::shared_ptr<tf2_ros::TransformListener> listener_;
    rclcpp::TimerBase::SharedPtr timer_;
    std::shared_ptr<tf2_ros::Buffer> buffer_;

public:
    TFListener(/* args */) : Node("tf_listener")
    {
        buffer_ = std::make_shared<tf2_ros::Buffer>(this->get_clock());
        listener_ = std::make_shared<tf2_ros::TransformListener>(*buffer_, this);
        // this->publish_tf();
        timer_ = this->create_wall_timer(6s, std::bind(&TFListener::get_transform, this));
    }

    void get_transform()
    {
        // 到buffer_里查询坐标关系
        try
        {
            // 查询坐标关系
            const auto transform = buffer_->lookupTransform("base_link", "target_point", this->get_clock()->now(), rclcpp::Duration::from_seconds(1.0f));
            // 获取查询结果
            auto translation = transform.transform.translation;
            auto rotation = transform.transform.rotation;
            double y, p, r;
            tf2::getEulerYPR(rotation, y, p, r);
            RCLCPP_INFO(get_logger(), "平移:%f,%f,%f", translation.x, translation.y, translation.z);
            RCLCPP_INFO(get_logger(), "旋转:%f,%f,%f", y, p, r);
        }
        catch (const std::exception &e)
        {
            RCLCPP_WARN(get_logger(), "%s", e.what());
        }
    }

    // void publish_tf()
    // {
    //     geometry_msgs::msg::TransformStamped transform;
    //     transform.header.stamp = this->get_clock()->now();
    //     transform.header.frame_id = "map";      // 父坐标系名字
    //     transform.child_frame_id = "base_link"; // 子坐标系名字
    //     transform.transform.translation.x = 2.0;
    //     transform.transform.translation.y = 3.0;
    //     transform.transform.translation.z = 0.0;
    //     tf2::Quaternion q;
    //     q.setRPY(0.0, 0.0, 30 * M_PI / 180.0);
    //     transform.transform.rotation = tf2::toMsg(q);
    //     this->listener_->sendTransform(transform);
    // }
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<TFListener>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}