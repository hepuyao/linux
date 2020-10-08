#include "dragwidget.h"

DragWidget::DragWidget(QWidget *parent)
    : QWidget(parent),m_mouseSrcPos(0,0)
{
}

DragWidget::~DragWidget()
{

}

void DragWidget::addButton(DragButton* btn)
{
    connect(btn,SIGNAL(drag_signal()),this,SLOT(BtnMove_slots()));
    connect(btn,SIGNAL(release_signal()),this,SLOT(BtnRelease_slots()));


    BtnVector.push_back(btn);
    btn->show();
    resetInterface();
}

void DragWidget::resetInterface()
{
    for(int i = 0;i < BtnVector.length();++i)
    {
        BtnVector[i]->setGeometry(i * width()/BtnVector.length(),0,width()/BtnVector.length(),height());
    }
}

void DragWidget::BtnMove_slots()
{
    for(int i = 0;i < BtnVector.length();++i)//找到鼠标所在的按钮
        if(BtnVector[i] == sender())
        {
            int flag = (BtnVector[i]->pos().x() + BtnVector[i]->width()/2)/(width()/BtnVector.length());

            for(int l = 0;l < BtnVector.length();++l)//这里也可以做动画，但这次主要实现拖动的功能
            {
                if(l < i && l <flag)
                    BtnVector[l]->setGeometry(l * width()/BtnVector.length(),0,width()/BtnVector.length(),height());
                else if((l > i && l <= flag)||(l >= flag && l < i))
                    BtnVector[l]->setGeometry((l + ((i-flag)>0?1:-1))* width()/BtnVector.length(),0,width()/BtnVector.length(),height());
                else if(l > flag && l > i)
                    BtnVector[l]->setGeometry(l * width()/BtnVector.length(),0,width()/BtnVector.length(),height());
            }
            //注释部分合为上面的循环
//            if(flag >= i)//往后拖
//                for(int l = 0;l < BtnVector.length();++l)
//                {
//                    if(l < i)
//                        BtnVector[l]->setGeometry(l * width()/BtnVector.length(),0,width()/BtnVector.length(),height());
//                    else if(l > i && l <= flag)
//                        BtnVector[l]->setGeometry((l - 1)* width()/BtnVector.length(),0,width()/BtnVector.length(),height());
//                    else if(l > flag)
//                        BtnVector[l]->setGeometry(l * width()/BtnVector.length(),0,width()/BtnVector.length(),height());
//                }
//            else if(flag < i)//往前拖
//                for(int l = 0;l < BtnVector.length();++l)
//                {
//                    if(l < flag)
//                        BtnVector[l]->setGeometry(l * width()/BtnVector.length(),0,width()/BtnVector.length(),height());
//                    else if(l >= flag && l < i)
//                        BtnVector[l]->setGeometry((l + 1)* width()/BtnVector.length(),0,width()/BtnVector.length(),height());
//                    else if(l > i)
//                        BtnVector[l]->setGeometry(l * width()/BtnVector.length(),0,width()/BtnVector.length(),height());
//                }
            break;
        }
}

void DragWidget::BtnRelease_slots()
{
    for(int i = 0;i < BtnVector.length();++i)//找到鼠标所在的按钮
        if(BtnVector[i] == sender())
        {
            int posX = BtnVector[i]->pos().x();
            if(posX < 0)
                posX = 0;
            else if(posX > width())
                posX = width();

            int flag = (posX+BtnVector[i]->width()/2)/(width()/BtnVector.length());

            DragButton *btn = BtnVector[i];//修改vector顺序
            if(flag >= i)
                for(int l = i;l < flag;++l)
                    BtnVector[l] = BtnVector[l+1];
            else
                for(int l = i;l > flag;--l)
                    BtnVector[l] = BtnVector[l-1];

            BtnVector[flag] = btn;
        }

    resetInterface();//复位
}
