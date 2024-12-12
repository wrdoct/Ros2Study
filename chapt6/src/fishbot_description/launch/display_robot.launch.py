import os
import launch
import launch_ros
from ament_index_python.packages import get_package_share_directory
import launch_ros.parameter_descriptions

def generate_launch_description():
    #  获取默认的urdf路径
    default_urdf_package_path = os.path.join(
        get_package_share_directory('fishbot_description'),
        'urdf',
        # 'first_robot.urdf' # 使用cat时
        'first_robot.xacro' # 使用xacro时
    )
    default_rviz_config_path = os.path.join(
        get_package_share_directory('fishbot_description'),
        'config',
        'display_robot_model.rviz'
    )
    # 声明一个urdf目录的参数，方便修改
    action_declare_arg_mode_path = launch.actions.DeclareLaunchArgument(
        name='model',default_value=str(default_urdf_package_path),description='加载的模型文件路径'
    )
    # 通过文件路径，获取内容，并转换成参数值对象，以供传入 robot_state_publisher
    # substitutions_command_result = launch.substitutions.Command(['cat ', launch.substitutions.LaunchConfiguration('model')])
    substitutions_command_result = launch.substitutions.Command(['xacro ', launch.substitutions.LaunchConfiguration('model')])
    robot_description_value = launch_ros.parameter_descriptions.ParameterValue(substitutions_command_result,value_type=str)

    action_robot_state_publisher = launch_ros.actions.Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        parameters=[{'robot_description':robot_description_value}]  # 节点参数--键值对
    )
    # 可以读取urdf中的关节配置
    action_joint_state_publisher = launch_ros.actions.Node(
        package='joint_state_publisher',
        executable='joint_state_publisher',
    )
    # 可以读取urdf中的关节配置
    action_rviz_node = launch_ros.actions.Node(
        package='rviz2',
        executable='rviz2',
        arguments=['-d', default_rviz_config_path]  # 命令行后面加的参数
    )

    return launch.LaunchDescription([
        action_declare_arg_mode_path,
        action_robot_state_publisher,
        action_joint_state_publisher,
        action_rviz_node,

    ])