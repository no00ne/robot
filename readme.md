### 1 leap motion

build

```shell
colcon build --packages-select handpose_interfaces
# build handpose消息接口
colcon build --packages-select handpose_publisher
# build 基于leap motion2 驱动的handpose_publisher节点


```

run
```shell
source install/setup.bash
ros2 run handpose_publisher leap_handpose_publisher
#run 基于leap motion2 驱动的handpose_publisher节点

```
echo handpose topic 以监测
```shell
source install/setup.bash
ros2 topic echo /handpose/flange
```

### 2 机械臂
build

```shell

colcon build --packages-skip handpose_publisher
bash src/Piper_ros/can_activate.sh can0 1000000
# build handpose_interfaces piper_handpose_controller piper(ros2)
```

一个终端run piper driver（官方）
```shell
source install/setup.bash
ros2 launch piper start_single_piper_rviz.launch.py can_port:=can0 auto_enable:=true gripper_exist:=true gripper_val_mutiple:=2 log_level:=warn


```

等待 driver 就绪（/enable_flag 会变为 true）后,一个终端run piper 控制节点

```shell
source install/setup.bash
ros2 run piper_handpose_controller handpose_controller

```
参数可在运行时或 launch 中覆盖（例如 pos_alpha、max_lin_vel 等）：
```shell
ros2 run piper_handpose_controller handpose_controller --ros-args -p pos_alpha:=0.25 -p max_lin_vel:=0.2
```