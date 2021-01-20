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

typedef struct SomeObject SomeObject;
typedef struct SomeObjectClass SomeObjectClass;

GType some_object_get_type (void);

struct SomeObject
{
  GObject parent;
};

struct SomeObjectClass
{
  GObjectClass parent;
};

enum
{
  RELOAD_SIGNAL,
};

static guint signals[] = {};

#define SOME_TYPE_OBJECT              (some_object_get_type ())
#define SOME_OBJECT(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), SOME_TYPE_OBJECT, SomeObject))
#define SOME_OBJECT_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), SOME_TYPE_OBJECT, SomeObjectClass))
#define SOME_IS_OBJECT(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), SOME_TYPE_OBJECT))
#define SOME_IS_OBJECT_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), SOME_TYPE_OBJECT))
#define SOME_OBJECT_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), SOME_TYPE_OBJECT, SomeObjectClass))

G_DEFINE_TYPE(SomeObject, some_object, G_TYPE_OBJECT)

gboolean some_object_get_security_config_path (SomeObject *obj, char **ret, GError **error);
gboolean some_object_reload_security_config (SomeObject *obj, GError **error);
gboolean some_object_exit_service (SomeObject *obj, GError **error);

#include "example-service-glue.h"

static void
some_object_init (SomeObject *obj)
{
}

static void
some_object_class_init (SomeObjectClass *klass)
{
    signals[RELOAD_SIGNAL] = g_signal_new ("reload_signal",
                    G_OBJECT_CLASS_TYPE (klass),
                    G_SIGNAL_RUN_LAST | G_SIGNAL_DETAILED,
                    0,
                    NULL, NULL,
                    g_cclosure_marshal_VOID__STRING,
                    G_TYPE_NONE, 1, G_TYPE_STRING);
}
/* GetSecurityConfigPath
 * 对应的接口函数
*/
gboolean
some_object_get_security_config_path (SomeObject *obj, char **ret, GError **error)
{
    char str[512];
    /* 输出配置文件路径，修改成自己的*.json */
    g_sprintf (str, "%s/mate-panel-security-config.json", g_get_user_config_dir());

    *ret = g_strdup(str);

    return TRUE;
}

gboolean
some_object_reload_security_config (SomeObject *obj, GError **error)
{
    g_signal_emit (obj, signals[RELOAD_SIGNAL], 0, "Reload");
    g_sprintf ("some_object_reload_security_config    single");
    return TRUE;
}

gboolean
some_object_exit_service (SomeObject *obj, GError **error)
{
    exit(0);
    return TRUE;
}
/*main in 
* 整个Gdbus写方法的入口
* 
*/
int
main (int argc, char **argv)
{
  DBusGConnection *bus;
  DBusGProxy *bus_proxy;
  GError *error = NULL;
  SomeObject *obj;
  GMainLoop *mainloop;
  guint request_name_result;

  g_type_init ();

  {
    GLogLevelFlags fatal_mask;
    
    fatal_mask = g_log_set_always_fatal (G_LOG_FATAL_MASK);
    fatal_mask |= G_LOG_LEVEL_WARNING | G_LOG_LEVEL_CRITICAL;
    g_log_set_always_fatal (fatal_mask);
  }
  
  dbus_g_object_type_install_info (SOME_TYPE_OBJECT, &dbus_glib_some_object_object_info);

  mainloop = g_main_loop_new (NULL, FALSE);

  bus = dbus_g_bus_get (DBUS_BUS_SESSION, &error);
  if (!bus)
    lose_gerror ("Couldn't connect to session bus", error);

  bus_proxy = dbus_g_proxy_new_for_name (bus, "org.freedesktop.DBus",
					 "/org/freedesktop/DBus",
					 "org.freedesktop.DBus");

  if (!dbus_g_proxy_call (bus_proxy, "RequestName", &error,
              G_TYPE_STRING, "org.mate.panel.session",
			  G_TYPE_UINT, 0,
			  G_TYPE_INVALID,
			  G_TYPE_UINT, &request_name_result,
			  G_TYPE_INVALID))
    lose_gerror ("Failed to acquire org.mate.panel.session", error);

  obj = g_object_new (SOME_TYPE_OBJECT, NULL);

  dbus_g_connection_register_g_object (bus, "/", G_OBJECT (obj));

  printf ("service running\n");

  g_main_loop_run (mainloop);

  exit (0);
}
