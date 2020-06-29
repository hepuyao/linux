以任务栏为例讲解监听屏幕改变


20200629　sxy：监听　HDMI VGA屏幕相关热插拔的信号
:1.qguiapplication　－－这个办法有点上层，想要更底层
 2.mutter 用的是glib的实现监听
　3.GdkScreen的size-changed 或者monitors-changed可以监听
