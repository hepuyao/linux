INCLUDES = \
	$(DBUS_CFLAGS)				\
	$(DBUS_GLIB_CFLAGS)			\
	-DDBUS_COMPILATION

LIBS = \
	$(DBUS_LIBS)				\
	$(DBUS_GLIB_LIBS)			\
	-ldbus-glib-1

# example-signal-emitter
bin_PROGRAMS = example-service

example_service_SOURCES = example-service-glue.h example-service.c

BUILT_SOURCES = example-service-glue.h

example-service-glue.h: example-service.xml
	$(LIBTOOL) --mode=execute dbus-binding-tool --prefix=some_object --mode=glib-server --output=example-service-glue.h $(srcdir)/example-service.xml

servicedir = /usr/share/dbus-1/services
service_DATA = org.mate.panel.session.service

CLEANFILES = $(BUILT_SOURCES)

EXTRA_DIST = example-service.xml $(service_DATA)

# example-client
bin_PROGRAMS += example-client
example_client_SOURCES= example-client.c


