#ifndef DESKTOPPROCESSCONVERSION_H
#define DESKTOPPROCESSCONVERSION_H
#include <QString>
#include <QMainWindow>
#include <QProcess>

QT_BEGIN_NAMESPACE
namespace Ui { class DesktopProcessConversion; }
QT_END_NAMESPACE

class DesktopProcessConversion : public QMainWindow
{
    Q_OBJECT

public:
    DesktopProcessConversion(QWidget *parent = nullptr);
    ~DesktopProcessConversion();

private slots:
    void on_pushButton_clicked();

    void desktopConver(QString);
    void on_readoutput();
    void on_readerror();

private:
    Ui::DesktopProcessConversion *ui;
    bool isFileExist(QString);
    QString desktopToName(QString);

    QProcess *cmd;
};
#endif // DESKTOPPROCESSCONVERSION_H
