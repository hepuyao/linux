#include "dragbutton.h"

DragButton::DragButton(QWidget *parent) :
    QWidget(parent),isPress(0),isHold(0),m_scaling(0.5),m_InitialScaling(0.5),m_mouseSrcPos(0,0)
{
    m_aniTimer = new QTimer(this);
    m_aniTimer->setInterval(7);

    m_holdTimer = new QTimer(this);
    m_holdTimer->setInterval(1000);
    m_holdTimer->setSingleShot(true);
    connect(m_holdTimer,SIGNAL(timeout()),this,SLOT(hold_slot()));
}

void DragButton::setInitialScaling(double scaling)
{
    if(scaling <= 1 && scaling > 0)
    {
        m_InitialScaling = scaling;
        m_scaling = scaling;
    }
}

void DragButton::setPixmap(QString pixmap)
{
    m_pixmap.load(pixmap);
    update();
}

void DragButton::setText(QString str)
{
    m_text = str;
    update();
}

void DragButton::setIsHold(bool flag)
{
    isHold = flag;
    update();
}

void DragButton::paintEvent(QPaintEvent *)
{
    if(m_pixmap.isNull())
        return;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    if(isPress)
    {
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor(0,0,0,130));
        painter.drawRoundedRect(rect(),20,20);
    }

    m_pixmap = m_pixmap.scaled(width(),height() - 20,Qt::KeepAspectRatio,Qt::SmoothTransformation);

    int w = m_pixmap.width()*m_scaling;
    int h = m_pixmap.height()*m_scaling;
    painter.drawPixmap(QRect((width() - w)/2,(height() - h)/2 - 20,w,h),
                       m_pixmap,m_pixmap.rect());

    painter.setPen(QColor(0,0,0));
    painter.drawText(QRect(0,height() - 40,width(),40),Qt::AlignCenter,m_text);
}

void DragButton::enterEvent(QEvent *)
{
    disconnect(m_aniTimer,SIGNAL(timeout()),this,SLOT(zoomOut()));
    connect(m_aniTimer,SIGNAL(timeout()),this,SLOT(zoomIn()));

    m_aniTimer->start();
}

void DragButton::leaveEvent(QEvent *)
{
    disconnect(m_aniTimer,SIGNAL(timeout()),this,SLOT(zoomIn()));
    connect(m_aniTimer,SIGNAL(timeout()),this,SLOT(zoomOut()));

    m_aniTimer->start();
}

void DragButton::mousePressEvent(QMouseEvent *e)
{
    if(!isHold)
        isPress = 1;

    m_holdTimer->start();

    m_mouseSrcPos = e->pos();

    update();
}

void DragButton::mouseReleaseEvent(QMouseEvent *e)
{
    m_holdTimer->stop();

    isPress = 0;
    isHold = 0;

    if(rect().contains(e->pos()))
        emit clicked();

    emit release_signal();

    update();
}

void DragButton::mouseMoveEvent(QMouseEvent *e)
{
    if(isHold)
    {
        move(pos() - m_mouseSrcPos + e->pos());
        emit drag_signal();
    }
    else
        m_mouseSrcPos = e->pos();
}

void DragButton::zoomIn()
{
    m_scaling += 0.01;
    if(m_scaling >= 1)
    {
        m_scaling = 1;
        m_aniTimer->stop();
    }
    update();
}

void DragButton::zoomOut()
{
    m_scaling -= 0.01;
    if(m_scaling <= m_InitialScaling)
    {
        m_scaling = m_InitialScaling;
        m_aniTimer->stop();
    }
    update();
}

void DragButton::hold_slot()
{
    isHold = 1;
    isPress = 0;
    m_aniTimer->stop();
    m_scaling = m_InitialScaling;

    update();
}
