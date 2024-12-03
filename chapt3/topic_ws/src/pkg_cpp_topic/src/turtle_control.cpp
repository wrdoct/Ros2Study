#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "turtlesim/msg/pose.hpp"
#include <chrono>

using namespace std::chrono_literals;

class TurtleControlNode : public rclcpp::Node
{
private:
    // rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_; // 发布者的智能指针
    rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr subscriber_;  // 订阅者的智能指针
    double target_x_{1.0};
    double target_y_{1.0};
    double k_{1.0};         // 比例系数
    double max_speed_{3.0}; // 最大速度

public:
    explicit TurtleControlNode(const std::string &node_name) : Node(node_name)
    {
        // timer_ = this->create_wall_timer(1000ms, std::bind(&TurtleControlNode::timer_callback, this));
        publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10);
        subscriber_ = this->create_subscription<turtlesim::msg::Pose>("/turtle1/pose", 10, std::bind(&TurtleControlNode::on_pose_received, this, std::placeholders::_1));
    };
    ~TurtleControlNode() {};

    // void timer_callback()
    // {
    //     auto msg = geometry_msgs::msg::Twist();
    //     msg.linear.x = 1.0;
    //     msg.angular.z = 0.5;
    //     publisher_->publish(msg);
    // }

    // 参数：收到数据的共享指针
    void on_pose_received(const turtlesim::msg::Pose::SharedPtr pose)
    {
        // 1. 获取当前位置
        auto current_x = pose->x;
        auto current_y = pose->y;
        RCLCPP_INFO(this->get_logger(), "当前:x=%f, y=%f", current_x, current_y);

        // 2. 计算当前海龟位置跟目标位置之间的距离差和角度差
        auto distance = std::sqrt(std::pow((target_x_ - current_x), 2) + std::pow((target_y_ - current_y), 2));
        auto angle = std::atan2(target_y_ - current_y, target_x_ - current_x) - pose->theta;

        // 3. 控制策略
        auto msg = geometry_msgs::msg::Twist();
        if (distance > 0.1)
        {
            if (fabs(angle) > 0.2)
            {
                msg.angular.z = fabs(angle);
            }
            else
            {
                msg.linear.x = k_ * distance;
            }
        }

        // 4. 限制线速度最大值
        if (msg.linear.x > max_speed_)
        {
            msg.linear.x = max_speed_;
        }

        // 5. 发布
        publisher_->publish(msg);
    }
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<TurtleControlNode>("turtle_control");
    rclcpp::spin(node);
    rclcpp::shutdown();

    return 0;
}