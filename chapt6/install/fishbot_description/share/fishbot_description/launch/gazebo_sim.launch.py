import os
import launch
import launch.launch_description_sources
import launch_ros
from ament_index_python.packages import get_package_share_directory
import launch_ros.parameter_descriptions

def generate_launch_description():
    #  获取功能包的share路径
    default_xacro_path = os.path.join(
        get_package_share_directory('fishbot_description'),
        'urdf',
        'fishbot/fishbot.urdf.xacro'
    )
    # default_rviz_config_path = os.path.join(
    #     get_package_share_directory('fishbot_description'),
    #     'config',
    #     'display_robot_model.rviz'
    # )
    default_gazebo_world_path = os.path.join(
        get_package_share_directory('fishbot_description'),
        'world',
        'custom_room.world'
    )
    # 声明一个urdf目录的参数，方便修改
    action_declare_arg_mode_path = launch.actions.DeclareLaunchArgument(
        name='model',default_value=str(default_xacro_path),description='加载的模型文件路径'
    )
    # 通过文件路径，获取内容，并转换成参数值对象，以供传入 robot_state_publisher
    substitutions_command_result = launch.substitutions.Command(['xacro ', launch.substitutions.LaunchConfiguration('model')])
    robot_description_value = launch_ros.parameter_descriptions.ParameterValue(substitutions_command_result,value_type=str)

    action_robot_state_publisher = launch_ros.actions.Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        parameters=[{'robot_description':robot_description_value}]  # 节点参数--键值对
    )

    action_launch_gazebo = launch.actions.IncludeLaunchDescription(
        launch.launch_description_sources.PythonLaunchDescriptionSource(
            [get_package_share_directory('gazebo_ros'),'/launch','/gazebo.launch.py']
        ),
        launch_arguments=[('world',default_gazebo_world_path),('verbose','true')]  # ('verbose','true') 日志输出级别 -- 详细输出
    )

    action_spawn_entity = launch_ros.actions.Node(
        package='gazebo_ros',
        executable='spawn_entity.py',
        arguments=['-topic','/robot_description','-entity','fishbot']
    )

    return launch.LaunchDescription([
        action_declare_arg_mode_path,
        action_robot_state_publisher,
        action_launch_gazebo,
        action_spawn_entity,
    ])