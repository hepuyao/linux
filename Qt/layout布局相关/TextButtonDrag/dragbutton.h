#ifndef DRAGBUTTON_H
#define DRAGBUTTON_H

#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <QImage>
#include <QMouseEvent>
#include <QVector>

class DragButton : public QWidget
{
    Q_OBJECT
public:
    DragButton(QWidget *parent = 0);

    void setInitialScaling(double scaling);
    void setPixmap(QString pixmap);
    void setText(QString str);
    void setIsHold(bool flag);
protected:
    int isPress;
    int isHold;

    QTimer *m_aniTimer;
    QTimer *m_holdTimer;

    double m_scaling;
    double m_InitialScaling;//当前缩放比例
    QPoint m_mouseSrcPos;//最小缩放比例

    QPixmap m_pixmap;
    QString m_text;

    void paintEvent(QPaintEvent *);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);

signals:
    void release_signal();
    void drag_signal();//拖动时发出信号
    void clicked();
public slots:
    void zoomIn();//放大
    void zoomOut();//缩小
    void hold_slot();
};

#endif // DRAGBUTTON_H
