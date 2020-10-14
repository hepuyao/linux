#include "monitorthemeswitch.h"
#include "ui_monitorthemeswitch.h"
#include <QDebug>

#define ORG_UKUI_STYLE            "org.ukui.style"
#define STYLE_NAME                "styleName"
#define STYLE_NAME_KEY_DARK       "ukui-dark"
#define STYLE_NAME_KEY_DEFAULT    "ukui-default"
#define STYLE_NAME_KEY_BLACK       "ukui-black"
#define STYLE_NAME_KEY_LIGHT       "ukui-light"
#define STYLE_NAME_KEY_WHITE       "ukui-white"


MonitorThemeSwitch::MonitorThemeSwitch(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MonitorThemeSwitch)
{
    ui->setupUi(this);

    const QByteArray style_id(ORG_UKUI_STYLE);
    QStringList stylelist;
    /*
     * ukui-defalt 主题时，应用为黑色模式或白色模式取决于设计稿
     * 例如 ukui-panel,ukui-menu,ukui-sidebar 等应用为黑色模式
    */
    stylelist<<STYLE_NAME_KEY_DARK<<STYLE_NAME_KEY_BLACK<<STYLE_NAME_KEY_DEFAULT;
    if(QGSettings::isSchemaInstalled(style_id)){
        style_settings = new QGSettings(style_id);
        if(stylelist.contains(style_settings->get(STYLE_NAME).toString())){
            //黑色主题下需要进行的处理
            ui->label->setText("黑色主题下需要进行的处理");
        }else{
            //白色主题下需要进行的处理
            ui->label->setText("白色主题下需要进行的处理");
        }
    }
    connect(style_settings, &QGSettings::changed, this, [=] (const QString &key){
        if(key==STYLE_NAME){
            if(stylelist.contains(style_settings->get(STYLE_NAME).toString())){
                //黑色主题下需要进行的处理
                ui->label->setText("黑色主题下需要进行的处理");
            }else{
                //白色主题下需要进行的处理
                ui->label->setText("白色主题下需要进行的处理");
            }
        }
    });

}

MonitorThemeSwitch::~MonitorThemeSwitch()
{
    delete ui;
}

