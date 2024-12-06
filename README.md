wget http://fishros.com/install -O fishros && . fishros
选择humble版本的ROS2即可

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