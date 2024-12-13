cmake_minimum_required(VERSION 3.8)
project(pkg_cpp)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

find_package(rclcpp REQUIRED)

include_directories(include) # 包含include目录

add_executable(person_node src/person_node.cpp)
add_executable(test_auto src/test_auto.cpp)
add_executable(learn_thread src/learn_thread.cpp)

# 将rclcpp库链接到person_node目标
ament_target_dependencies(person_node rclcpp)
# 将可执行文件安装到项目的lib/<PROJECT_NAME>目录下
install(TARGETS
  person_node test_auto learn_thread
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
