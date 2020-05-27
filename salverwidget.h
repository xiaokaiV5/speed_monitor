#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include "netinfo.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void mouseDoubleClickEvent(QMouseEvent *event);

public slots:
    void dataUpdata(NetDaTa &onDataUpdata);

private:
    Ui::Widget *ui;
    NetInfo *_netinfo;
    QTimer *_timer;
};
#endif // WIDGET_H
