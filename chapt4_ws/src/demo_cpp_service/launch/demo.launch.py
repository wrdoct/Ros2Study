import launch
import launch_ros

# 运行命令：ros2 launch demo_cpp_service demo.launch.py launch_arg_bg:=255
def generate_launch_description():
    # 1. 声明一个参数 -- 声明了一个名为launch_arg_bg的launch参数，并为其设置了一个默认值"150"。这个参数可以在launch文件中被引用，并被传递给节点作为配置参数。DeclareLaunchArgument动作告诉launch系统存在这个参数，并定义了它的默认值。
    action_declare_arg_background_g = launch.actions.DeclareLaunchArgument('launch_arg_bg',default_value="150")
    # 2. 把launch的参数手动传递给某个节点 -- launch.substitutions.LaunchConfiguration用于从launch参数中获取值。这意味着background_g参数的值将被设置为launch文件中launch_arg_bg参数的值。如果launch_arg_bg没有被外部指定，它将使用默认值"150"
    """产生launch描述"""
    action_node_turtlesim_node = launch_ros.actions.Node(
        package='turtlesim',
        executable='turtlesim_node',
        parameters=[{'background_g': launch.substitutions.LaunchConfiguration('launch_arg_bg',default="150")}],
        output='screen'
    )

    action_node_turtle_control = launch_ros.actions.Node(
        package='demo_cpp_service',
        executable='turtle_control',
        output='log'
    )

    action_node_partol_client = launch_ros.actions.Node(
        package='demo_cpp_service',
        executable='partol_client',
        output='both'
    )

    # Launch description
    return launch.LaunchDescription([
        # action动作
        action_declare_arg_background_g,
        action_node_turtlesim_node,
        action_node_turtle_control,
        action_node_partol_client
    ])
