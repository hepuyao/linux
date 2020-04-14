#include "widget.h"
#include "ui_widget.h"

#include <QGSettings/QGSettings>

#include <QDebug>

/* qt会将glib里的signals成员识别为宏，所以取消该宏
 * 后面如果用到signals时，使用Q_SIGNALS代替即可
 **/
#ifdef signals
#undef signals
#endif

extern "C" {
#include <glib.h>
#include <gio/gio.h>
#include <dconf/dconf.h>
}

#define KEYBINDINGS_CUSTOM_SCHEMA "org.ukui.panel.tray"
#define KEYBINDINGS_CUSTOM_DIR "/org/ukui/tray/keybindings/"

#define MAX_CUSTOM_SHORTCUTS 1000

#define ACTION_KEY "action"
#define BINDING_KEY "binding"
#define NAME_KEY "name"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    resize(400, 300);

    connect(ui->listBtn, &QPushButton::clicked, [=](bool checked){
        getValue();
    });

    connect(ui->addBtn, &QPushButton::clicked, [=](bool checked){
        addValue();
    });

    connect(ui->delBtn, &QPushButton::clicked, [=](bool checked){
        delValeu();
    });

    connect(ui->findBtn, &QPushButton::clicked, [=](bool checked){
        qDebug() << "Find Free Path: " << findFreePath();
    });
}

Widget::~Widget()
{
    delete ui;
}

QList<char *> Widget::listExistsPath(){
    char ** childs;
    int len;

    DConfClient * client = dconf_client_new();
    childs = dconf_client_list (client, KEYBINDINGS_CUSTOM_DIR, &len);
    g_object_unref (client);

    QList<char *> vals;

    for (int i = 0; childs[i] != NULL; i++){
        if (dconf_is_rel_dir (childs[i], NULL)){
            char * val = g_strdup (childs[i]);

            vals.append(val);
        }
    }
    g_strfreev (childs);
    return vals;
}

QString Widget::findFreePath(){
    int i = 0;
    char * dir;
    bool found;
    QList<char *> existsdirs;

    existsdirs = listExistsPath();

    for (; i < MAX_CUSTOM_SHORTCUTS; i++){
        found = true;
        dir = QString("custom%1/").arg(i).toLatin1().data();
        for (int j = 0; j < existsdirs.count(); j++)
            if (!g_strcmp0(dir, existsdirs.at(j))){
                found = false;
                break;
            }
        if (found)
            break;
    }

    if (i == MAX_CUSTOM_SHORTCUTS){
        qDebug() << "Keyboard Shortcuts" << "Too many custom shortcuts";
        return "";
    }

    return QString("%1%2").arg(KEYBINDINGS_CUSTOM_DIR).arg(QString(dir));
}

void Widget::addValue(){
    QString availablepath = findFreePath();

    qDebug() << "Add Path" << availablepath;

    const QByteArray id(KEYBINDINGS_CUSTOM_SCHEMA);
    const QByteArray idd(availablepath.toUtf8().data());
    QGSettings * settings = new QGSettings(id, idd);

    settings->set(BINDING_KEY, "disable");
    settings->set(NAME_KEY, "firefox");
    settings->set(ACTION_KEY, "winid");

    delete settings;
}

void Widget::getValue(){

    QList<char *> existsPath = listExistsPath();

    for (char * path : existsPath){

        char * prepath = QString(KEYBINDINGS_CUSTOM_DIR).toLatin1().data();
        char * allpath = strcat(prepath, path);

        const QByteArray ba(KEYBINDINGS_CUSTOM_SCHEMA);
        const QByteArray bba(allpath);
        QGSettings * settings = new QGSettings(ba, bba);

        QString actionStr = settings->get(ACTION_KEY).toString();
        QString bingdingStr = settings->get(BINDING_KEY).toString();
        QString nameStr = settings->get(NAME_KEY).toString();

        g_warning("full path: %s", allpath);
        qDebug() << ACTION_KEY << actionStr << BINDING_KEY << bingdingStr <<NAME_KEY << nameStr;
    }
}

void Widget::delValeu(){
    gboolean ret;
    GError ** error = NULL;
    QList<char *> tmp = listExistsPath();

    char * dir;
    dir = tmp.at(tmp.length() - 1);

    char * prepath = QString(KEYBINDINGS_CUSTOM_DIR).toLatin1().data();
    char * allpath = strcat(prepath, dir);
    g_warning("%s will be del", allpath);
    DConfClient * client = dconf_client_new ();

    ret = dconf_client_write_sync (client, allpath, NULL, NULL, NULL, error);



    g_object_unref (client);
}

