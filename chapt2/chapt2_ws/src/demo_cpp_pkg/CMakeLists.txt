cmake_minimum_required(VERSION 3.8)
project(demo_cpp_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

add_executable(cpp_node src/cpp_node.cpp)
find_package(rclcpp REQUIRED)
# # 打印包含目录和库文件路径，用于调试
# message(STATUS "rclcpp_INCLUDE_DIRS: ${rclcpp_INCLUDE_DIRS}")
# message(STATUS "rclcpp_LIBRARIES: ${rclcpp_LIBRARIES}")
# # 为目标指定包含目录
# target_include_directories(cpp_node PUBLIC ${rclcpp_INCLUDE_DIRS}) # 头文件包含
# target_link_libraries(cpp_node ${rclcpp_LIBRARIES}) # 库文件链接
# 将rclcpp库链接到cpp_node目标
ament_target_dependencies(cpp_node rclcpp)
# 将可执行文件安装到项目的lib/<PROJECT_NAME>目录下
install(TARGETS
  cpp_node
  DESTINATION lib/${PROJECT_NAME}
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
