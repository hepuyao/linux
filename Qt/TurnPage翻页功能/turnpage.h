#ifndef TURNPAGE_H
#define TURNPAGE_H

#include <QWidget>
#include <QMouseEvent>
#include <QToolButton>

QT_BEGIN_NAMESPACE
namespace Ui { class TurnPage; }
QT_END_NAMESPACE


class TurnPageButton : public QToolButton
{
    Q_OBJECT

public:
    TurnPageButton();
    ~TurnPageButton();
//    void mousePressEvent(QMouseEvent *e);

};


class TurnPage : public QWidget
{
    Q_OBJECT

public:
    TurnPage(QWidget *parent = nullptr);
    ~TurnPage();

    void clickToTurnPage();
    void removeLayout();

    TurnPageButton *btn_turn;
    int count;

private:
    Ui::TurnPage *ui;
};


#endif // TURNPAGE_H
