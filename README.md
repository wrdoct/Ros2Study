wget http://fishros.com/install -O fishros && . fishros
选择humble版本的ROS2即可
# 安装的是humble版本的ROS，所以安装目录在/opt/ros/humble下  echo "source /opt/ros/humble/setup.bash" >> ~/.bashrc
# sudo apt remove ros-humble-*
# sudo apt autoremove

```
mkdir src
cd src/
ros2 pkg create example_cpp --build-type ament_cmake --dependencies rclcpp
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