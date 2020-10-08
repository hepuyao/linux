#include "dragbutton.h"

class DragWidget : public QWidget
{
    Q_OBJECT

public:
    DragWidget(QWidget *parent = 0);
    ~DragWidget();

    void addButton(DragButton*);

protected:
    QVector<DragButton*> BtnVector;
    QPoint m_mouseSrcPos;//记录坐标点

    void resetInterface();//复位

signals:

public slots:
    void BtnMove_slots();
    void BtnRelease_slots();
};

//#endif // DRAGWIDGET_H
