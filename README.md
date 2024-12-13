wget http://fishros.com/install -O fishros && . fishros
选择humble版本的ROS2即可
# 安装的是humble版本的ROS，所以安装目录在/opt/ros/humble下  echo "source /opt/ros/humble/setup.bash" >> ~/.bashrc
# sudo apt remove ros-humble-*
# sudo apt autoremove

```
mkdir src
cd src/
ros2 pkg create example_cpp --build-type ament_cmake --dependencies rclcpp --license Apache-2.0
cd example_cpp/src
touch node_01.cpp
cd ../../..
colcon build --packages-select example_cpp
source install/setup.bash
ros2 run example_cpp node_03
```

3D旋转可视化：
```
sudo apt install ros-humble-mrpt2 -y
3d-rotation-converter 
```
查看TF树:
```
ros2 run tf2_tools view_frames 
```
直接看tf树： ros2 run rqt_tf_tree rqt_tf_tree（需要先安装sudo apt-get install ros-humble-rqt-tf-tree）

运行时后面加上 & 可以在后台执行

数据可视化工具 rviz2 

数据记录工具 ros2 bag
ros2 bag record /turtle1/cmd_vel
ros2 bag play rosbag2_2024_12_10-09_42_14/


使用URDF创建机器人

llw@llwubuntuserver:~/git/ros2-study/chapt6/src/fishbot_description/urdf$ urdf_to_graphviz first_robot.urdf 
以下两个插件可以读取urdf中的关节配置
sudo apt install ros-$ROS_DISTRO-joint-state-publisher
sudo apt install ros-$ROS_DISTRO-robot-state-publisher

Xacro(XML Macro)是基于XML的宏语言，用于简化URDF文件的创建和维护。
使用工具将xacro文件转为urdf
sudo apt install ros-$ROS_DISTRO-xacro
xacro /home/llw/git/ros2-study/chapt6/src/fishbot_description/urdf/first_robot.xacro


ros2 launch fishbot_description display_robot.launch.py model:=/home/llw/git/ros2-study/chapt6/src/fishbot_description/urdf/fishbot/fishbot.urdf.xacro


在Gazebo中完成机器人仿真
sudo apt install gazebo
之后输入 gazebo 打开
下载模型
mkdir -p ~/.gazebo
cd ~/.gazebo/
git clone https://gitee.com/ohhuo/gazebo_models.git ~/.gazebo/models
rm -rf ~/.gazebo/models/.git # 防止把.git误识别为模型

在Gazebo中加载机器人模型
sudo apt install ros-$ROS_DISTRO-gazebo-ros-pkgs

ros2 launch fishbot_description gazebo_sim.launch.py 
