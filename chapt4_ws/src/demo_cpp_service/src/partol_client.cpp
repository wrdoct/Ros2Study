#include "rclcpp/rclcpp.hpp"
#include "pkg_interfaces/srv/partol.hpp"
#include <chrono>
#include <ctime>

using namespace std::chrono_literals; // 可以使用10s 100s

using Partol = pkg_interfaces::srv::Partol;

class PartolClientNode : public rclcpp::Node
{
private:
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Client<Partol>::SharedPtr partol_client_;

public:
    explicit PartolClientNode(const std::string &node_name) : Node(node_name)
    {
        srand(time(NULL)); // 初始化随机数种子
        partol_client_ = this->create_client<Partol>("partol");
        timer_ = this->create_wall_timer(10s, [&]() -> void
                                         {
                                             // 1. 检测服务端是否上线
                                             while (!this->partol_client_->wait_for_service(1s))
                                             {
                                                 if (rclcpp::ok())
                                                 {
                                                     RCLCPP_ERROR(this->get_logger(), "等待服务上线过程中，rclcpp挂了！");
                                                     return;
                                                 }
                                                 RCLCPP_INFO(this->get_logger(), "等待服务上线中...");
                                             }
                                             // 2. 构造请求对象
                                             auto request = std::make_shared<Partol::Request>();
                                             request->target_x = rand() % 15;
                                             request->target_y = rand() % 15;
                                             RCLCPP_INFO(this->get_logger(), "准备好目标点%f,%f",request->target_x,request->target_y);
                                             // 3. 发送请求
                                             this->partol_client_->async_send_request(request,[&](rclcpp::Client<Partol>::SharedFuture result_future)->void{
                                                auto response = result_future.get();
                                                if(response->result == Partol::Response::SUCCESS){
                                                    RCLCPP_INFO(this->get_logger(), "请求巡逻目标点成功");
                                                }
                                                if(response->result == Partol::Response::FAIL){
                                                    RCLCPP_INFO(this->get_logger(), "请求巡逻目标点失败");
                                                }

                                             }); });
    };
    ~PartolClientNode() {};
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<PartolClientNode>("partol_client");
    rclcpp::spin(node);
    rclcpp::shutdown();

    return 0;
}