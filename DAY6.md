DAY6

温湿度

访问文件

/sys/bus/iio/devices/%s/%s", device, filename

temp_raw：温度原始值

temp_offset：偏移量

temp_scale：温度系数

实际温度：(temp_raw + temp_offset) * temp_scale / 1000;

hum_raw：湿度原始值

hum_offset：偏移量

hum_scale：湿度系数

实际湿度：(hum_raw + hum_offset) * hum_scale / 1000



添加资源文件



![image-20260417145533646](C:\Users\10424\AppData\Roaming\Typora\typora-user-images\image-20260417145533646.png)



V4L2（Video for Linux 2）是Linux内核中的一个子系统，专门用于处理视频和音频设备。它是原始V4L（Video for Linux）的重写版本，提供了更强大、更灵活的接口来控制各种视频硬件设备。

V4L2是Video for Linux的第二版API，它是Linux内核的一个子系统，为各种视频设备提供统一的接口。



主要接口类型：
视频采集接口（Video Capture Interface）：用于摄像头等设备捕获视频

视频输出接口（Video Output Interface）：用于向外部设备输出视频

视频覆盖接口（Video Overlay Interface）：用于直接在显示器上叠加视频

视频模拟接口（Video Analog Interface）：用于控制模拟视频设备

调谐器接口（Tuner Interface）：用于控制电视调谐器





ioctl()调用



read、write、open、close区别：

专门输送出了write发送数据以外的特殊格式的数据、一些特殊参数选择需要用到你













