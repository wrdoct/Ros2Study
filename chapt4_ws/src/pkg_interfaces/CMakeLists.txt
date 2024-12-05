cmake_minimum_required(VERSION 3.8)
project(pkg_interfaces)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(rosidl_default_generators REQUIRED)

# 假设您的包中有自定义的消息和/或服务
# 设置消息和/或服务文件的路径
# set(msg_files
#   "msg/RadarTracker.msg"
#   "msg/VideoData.msg"
# )

set(srv_files
  "srv/FaceDetector.srv"
  "srv/Partol.srv"
)

# 生成接口 -- cmake函数，来自依赖 rosidl_default_generators 用于将msg等消息接口定义文件转换成库或者头文件夹
rosidl_generate_interfaces(${PROJECT_NAME}
  # ${msg_files}
  ${srv_files}
  DEPENDENCIES sensor_msgs  # 如果您的接口依赖于其他包
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
