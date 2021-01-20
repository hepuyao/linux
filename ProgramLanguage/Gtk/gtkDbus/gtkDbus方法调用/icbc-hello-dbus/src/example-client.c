#include <dbus/dbus-glib.h>
#include <stdio.h>
#include <stdlib.h>

static void lose (const char *fmt, ...) G_GNUC_NORETURN G_GNUC_PRINTF (1, 2);
static void lose_gerror (const char *prefix, GError *error) G_GNUC_NORETURN;

static void
lose (const char *str, ...)
{
  va_list args;

  va_start (args, str);

  vfprintf (stderr, str, args);
  fputc ('\n', stderr);

  va_end (args);

  exit (1);
}

static void
lose_gerror (const char *prefix, GError *error) 
{
  lose ("%s: %s", prefix, error->message);
}

static void
reload_signal_handler (DBusGProxy *proxy, const char * reload_string, gpointer user_data)
{
  printf ("Received signal and it says: %s\n", reload_string);
  exit(0);
}

int
main (int argc, char **argv)
{
  DBusGConnection *bus;
  DBusGProxy *remote_object;
  GMainLoop *mainloop;
  GError *error = NULL;
  char *reply;

  g_type_init ();

  mainloop = g_main_loop_new (NULL, FALSE);

  bus = dbus_g_bus_get (DBUS_BUS_SESSION, &error);
  if (!bus)
    lose_gerror ("Couldn't connect to session bus", error);
  
  remote_object = dbus_g_proxy_new_for_name (bus,
                         "org.mate.panel.session",
                         "/",
                         "org.mate.panel.session.interface");

  if (!dbus_g_proxy_call (remote_object, "GetSecurityConfigPath", &error,
              G_TYPE_INVALID,
              G_TYPE_STRING, &reply, G_TYPE_INVALID))
    lose_gerror ("Failed to complete HelloWorld", error);

  printf ("reply: %s", reply);
  printf ("\n");


  dbus_g_proxy_add_signal (remote_object, "ReloadSignal", G_TYPE_STRING, G_TYPE_INVALID);

  dbus_g_proxy_connect_signal (remote_object, "ReloadSignal", G_CALLBACK (reload_signal_handler),
                                 NULL, NULL);

  g_main_loop_run (mainloop);

  exit(0);
}
