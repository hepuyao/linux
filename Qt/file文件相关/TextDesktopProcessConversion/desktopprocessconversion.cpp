/*
 * @brief
 *
 * desktop文件 汉化相关注意事项
 * 自研应用desktop文件应包含Name，Name[zh_CN]，GenericName，GenericName[zh_CN]等字段。
 * 禁止将Name字段设置为中文;Name[zh_CN]字段应为中文（若程序无法汉化也可以是英文）
 * 禁止将GenericName字段可以设置为中文;GenericName[zh_CN]字段为相关应用程序的通用名称，必须为中文。
 * GenericName字段必须在Name字段后，否则会混淆程序中文名称与该应用程序通用名称。
*/


#include "desktopprocessconversion.h"
#include "ui_desktopprocessconversion.h"
#include "QFile"
#include "QDebug"
#include "QByteArray"
#include "QFileInfo"
#include <QProcess>
#include <QMessageBox>

/*
 * @brief 进程名转化为对应的desktop文件并提取汉化名称
 * ui->lineEdit 供输入进程名，以及点击按钮后显示汉化名称
 * ui->label  提示信息
*/
DesktopProcessConversion::DesktopProcessConversion(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DesktopProcessConversion)
{
    ui->setupUi(this);
}

DesktopProcessConversion::~DesktopProcessConversion()
{
    delete ui;
}


void DesktopProcessConversion::on_pushButton_clicked()
{
    desktopConver(ui->lineEdit->text());
}

/*
 * 将进程名转化为对应的desktop文件，然后通过desktopToName将desktop文件中的Name[zh_CN]字段提取
*/
void DesktopProcessConversion::desktopConver(QString process)
{
    if(isFileExist("/etc/xdg/autostart/"+process+".desktop") || isFileExist("/usr/share/applications/"+process+".desktop")){
        if(isFileExist("/etc/xdg/autostart/"+process+".desktop")){
            desktopToName("/etc/xdg/autostart/"+process+".desktop");
        }else{
            desktopToName("/usr/share/applications/"+process+".desktop");
        }
    }
    else{
        cmd = new QProcess(this);
        connect(cmd , SIGNAL(readyReadStandardOutput()) , this , SLOT(on_readoutput()));
        /*异常处理*/
        //connect(cmd , SIGNAL(readyReadStandardError()) , this , SLOT(on_readerror()));

        cmd->start("bash");             //启动终端(Windows下改为cmd)
        cmd->waitForStarted();          //等待启动完成
        QString input_cmd;
        input_cmd=QString("grep -nr %1 /usr/share/applications/  /etc/xdg/autostart/\n").arg(ui->lineEdit->text());
        cmd->write(input_cmd.toUtf8());               //向终端写入“ls”命令，注意尾部的“\n”不可省略
    }
}

bool DesktopProcessConversion::isFileExist(QString fullFileName)
{
    QFileInfo fileInfo(fullFileName);
    if(fileInfo.isFile())
    {
        return true;
    }
    return false;
}

/*
 * 将desktop文件中Name[zh_CN]字段提取
 * 若Name[zh_CN]字段为英文则提取GenericName[zh_CN]
 * （以fcitx为例，fcitx.desktop的   Name[zh_CN]=fcitx，GenericName[zh_CN]=输入法）
 * 以desktop文件的规范性来讲，其实不应处理此逻辑，GenericName[zh_CN]字段本就不是应用的汉化名称，而是应用的类型通用名称，
 * 在同类型应用较为丰富的情况下，对GenericName[zh_CN]进行处理必然导致歧义
 * 自研托盘应用应尽量遵循desktop文件的规范，Name[zh_CN]字段为中文，GenericName[zh_CN]字段应写此类应用的通用中文名称
*/
QString DesktopProcessConversion::desktopToName(QString desktopfile)
{
    QFile file(desktopfile);
    bool flag=false;
    qDebug()<<"desktop name   :  "<<desktopfile;
    if(!isFileExist(desktopfile)){
        qDebug()<<"Nodesktop file ;No Chinese name";
        return "";
    }
    if (!file.open(QIODevice::ReadOnly)) qDebug() << "Read DesktopFile Failed.";
    while (!file.atEnd()) {
        QByteArray line = file.readLine();
        QString str(line);
        if (str.contains("Name[zh_CN]") && str.contains(QRegExp("[\\x4e00-\\x9fa5]+"))){
            if(!str.contains("GenericName")){
                str=str.remove("Name[zh_CN]=");
            }else{
                str=str.remove("GenericName[zh_CN]=");
            }
            str=str.remove("\n");
            ui->lineEdit->setText(str);
            qDebug()<<"Chinese name: "<<str;
            flag=true;
            return str;
        }
        if(file.atEnd() && !flag){
            qDebug()<<"No Chinese name";
            //可用.isEmpty()判断是否返回值为空；不可用 .isNull();
            return "";
        }
    }
}

/*
 * QString("grep -nr %1 /usr/share/applications/  /etc/xdg/autostart/\n").arg(ui->lineEdit->text());
 * 遍历 /usr/share/applications/  /etc/xdg/autostart/  目录寻找匹配的desktop文件
*/
void DesktopProcessConversion::on_readoutput()
{
    ui->label->setWordWrap(true);
    QFile file("/tmp/desktopprocess.txt");
    QString output=cmd->readAllStandardOutput().data();

    //打开文件，不存在则创建
    file.open(QIODevice::ReadWrite | QIODevice::Text);
    file.write(output.toUtf8());
    file.close();
//    qDebug()<<output.toUtf8();


    file.open(QIODevice::ReadWrite | QIODevice::Text);
    while (!file.atEnd()) {
        QByteArray line = file.readLine();
        QString str(line);
        if(str.contains(".desktop:") && str.contains(":Exec")){
            str=str.section(".desktop",0,0)+".desktop";
            ui->label->setText(str);
            desktopToName(str);
        }
    }
    file.close();
    file.remove();
}

void DesktopProcessConversion::on_readerror()
{
    QMessageBox::information(0, "Error", cmd->readAllStandardError().data());    //弹出信息框提示错误信息
}
