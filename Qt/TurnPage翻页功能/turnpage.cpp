#include "turnpage.h"
#include "ui_turnpage.h"
#include <QToolButton>
#include <QDebug>
#include <QList>

TurnPage::TurnPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TurnPage)
{
    ui->setupUi(this);

    ui->horizontalLayoutWidget->setStyleSheet(
                "QWidget{"
                "background-color:rgba(100,225,100,80%);"//背景色（也可以设置图片）
                "}"
                );

//    btn_turn=new TurnPageButton;
//    btn_turn->setIcon(QIcon::fromTheme("pan-end-symbolic"));
//    ui->horizontalLayout->addWidget(btn_turn);
//
//    connect(btn_turn,&TurnPageButton::clicked,[this] { clickToTurnPage();});

    ui->toolButton->setIcon(QIcon::fromTheme("pan-end-symbolic"));
    connect(ui->toolButton,&QToolButton::clicked,[this] { clickToTurnPage();});
}

TurnPage::~TurnPage()
{
    delete ui;
}

void TurnPage::clickToTurnPage()
{
    qDebug()<<"&&&&&&&&&&&&&&&"<<count;
    QToolButton *btn[60];
    switch (count)
    {
    case 0:
    {
        removeLayout();
//        ui->horizontalLayout->addWidget(btn_turn);
        for(int i=0;i<5;i++)
        {
            btn[i]=new QToolButton;
            btn[i]->setIcon(QIcon::fromTheme("firefox"));
            btn[i]->setIconSize(QSize(64,64));

            ui->horizontalLayout->addWidget(btn[i]);
        }
        count =1;
        break;
    }

    case 1:
    {
        /*
        //以下方法均无法删除布局中的全部按钮，原因是获取到的btns1.size()为０
        QList<QToolButton*> btns1 = ui->horizontalLayout->findChildren<QToolButton*>();//获取布局中所有按钮
        qDebug()<<"获取到的btns1的数量"<<btns1.size();
        foreach (QToolButton *bt1, btns1) {
            qDebug()<<"delete  bt1**********"<<bt1;
            delete bt1;    //析构所有按钮
        }
                for(QToolButton *bt1:qAsConst(btns1))
                {
                    qDebug()<<"bt1************:"<<bt1;
                    delete bt1;
                }
                for(int i=0;i<btns1.size();i++)
                {
                    qDebug()<<"case 1中的删除控件操作"<<btns1[i];
                    delete btns1[i];
                }
          */
        removeLayout();
        for(int i=0;i<5;i++)
        {

            btn[i]=new QToolButton;
            btn[i]->setIcon(QIcon::fromTheme("vim"));
            btn[i]->setIconSize(QSize(64,64));

            ui->horizontalLayout->addWidget(btn[i]);
        }
        count=2;
        break;
    }

    case 2:
    {
        removeLayout();
        for(int i=0;i<5;i++)
        {
            btn[i]=new QToolButton;
            btn[i]->setIcon(QIcon::fromTheme("pluma"));
            btn[i]->setIconSize(QSize(64,64));

            ui->horizontalLayout->addWidget(btn[i]);
        }
        count=3;
        break;
    }

    case 3:
    {
        removeLayout();

        for(int i=0;i<5;i++)
        {
            btn[i]=new QToolButton;
            btn[i]->setIcon(QIcon::fromTheme("blueman"));
            btn[i]->setIconSize(QSize(64,64));

            ui->horizontalLayout->addWidget(btn[i]);
        }
        count=4;
        break;
    }
    case 4:
    {
        removeLayout();
        for(int i=0;i<5;i++)
        {
            btn[i]=new QToolButton;
            btn[i]->setIcon(QIcon::fromTheme("goog"));
            btn[i]->setIconSize(QSize(64,64));

            ui->horizontalLayout->addWidget(btn[i]);
        }
        count=0;
        break;
    }

    default:
        count=0;
        break;

    }
}

void TurnPage::removeLayout()
{
    while (ui->horizontalLayout->count() > 0)
    {
        QWidget *w = ui->horizontalLayout->itemAt(0)->widget();
        ui->horizontalLayout->removeWidget(w);
        delete w;

        qDebug()<<"start";
        //ui->horizontalLayout->addWidget(btn_turn);
        qDebug()<<"end";
    }
}

TurnPageButton::TurnPageButton()
{

}

TurnPageButton::~TurnPageButton()
{

}

//void TurnPageButton::mousePressEvent(QMouseEvent *e)
//{
//    qDebug()<<"**************";
//}
