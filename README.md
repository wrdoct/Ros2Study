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