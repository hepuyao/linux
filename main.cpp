#include "ukuipanelapplication.h"
#include "config/configpluginswidget.h"
int main (int argc, char *argv[])
{
	UkuiPanelApplication app(argc, argv);
//    ConfigPluginsWidget v;
//    v.show();
	return app.exec();		
}
