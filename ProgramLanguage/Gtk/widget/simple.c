#include <gtk/gtk.h>

void widget_screen_show()
{
  GdkScreen *screen;
  screen=gdk_screen_get_default();
  printf("widget_screen   \n");
  printf("widget_screen height:%d  \n",gdk_screen_get_width(screen));
  printf("widget_screen number is %d \n",gdk_screen_get_n_monitors(screen));
  printf("widget_screen primary %d \n",gdk_screen_get_primary_monitor(screen));
}

int main(int argc, char *argv[]) {

  GtkWidget *window;

  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_widget_show(window);
	
  widget_screen_show();  

  g_signal_connect(window, "destroy",
      G_CALLBACK(gtk_main_quit), NULL);  

  gtk_main();

  return 0;
}
