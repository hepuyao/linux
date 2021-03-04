 gcc -o simple simple.c  `pkg-config --libs --cflags gtk+-2.0`


GdkScreen相关API：
GdkScreen   *screen;
GdkRectangle dest_left, dest_right;
int width , height, monitor, monitor_left, monitor_right，screen_num;
screen = gdk_screen_get_default();             //获取当前屏幕
width = gdk_screen_get_width(screen);          //获取屏幕宽度
height = gdk_screen_get_height（screen）；      //获取屏幕高度
screen_num = gdk_screen_get_n_monitors(screen); //监控器个数  （屏幕个数）
monitor_left = gdk_screen_get_monitor_at_point(screen,0,0);        //双屏获取左屏幕的监控器
monitor_right = gdk_screen_get_monitor_at_point(screen,width,0);   //双屏获取右屏幕的监控器
gdk_screen_get_monitor_geometry(screen, monitor_left, &dest_left); //获取左监控器的宽高
dest_left.width,   dest_left.height  //宽和高
monitor = gdk_screen_get_primary_monitor(screen);//获取主屏监控器
if(monitor == monitor_left)  //如果主屏为左屏幕
{
 //进行参数相关操作
}
2)、Gdk屏幕信号监听事件：
/*屏幕变化回调函数*/
static void
on_screen_size_changed (GdkScreen *screen,
                       Manager   *manager)
{
    Display  *dpy = XOpenDisplay(NULL);   //获取Display
    gint width   = DisplayWidth(dpy, 0);  //获取整显示器宽
    gint height  = DisplayHeight(dpy, 0); //获取整显示器高度
    XCloseDisplay(dpy);                   //释放
    ... ...
}
void screenListenEvents()  //关于屏幕改变监听方式
{
   GdkDisplay *display = gdk_display_get_default();                //获取GdkDisplay
   GdkScreen *screen   = gdk_display_get_default_screen (display); //获取GdkScreen
   g_signal_connect (screen, "monitors-changed",
                     G_CALLBACK (on_screen_size_changed), manager); //监听屏幕监视器变化
    g_signal_connect (screen, "size-changed",
                     G_CALLBACK (on_screen_size_changed), manager);//监听屏幕分辨率变化
}
