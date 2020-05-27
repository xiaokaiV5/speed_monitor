#ifndef ALLINFOWIDGET_H
#define ALLINFOWIDGET_H

#include <QWidget>
#include "ui_hardInfo.h"

QT_BEGIN_NAMESPACE
namespace Ui { class infowidget; }
QT_END_NAMESPACE

class AllInfoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AllInfoWidget(QWidget *parent = nullptr);
    
signals:
    
private:
    Ui::infowidget *ui;
};

#endif // ALLINFOWIDGET_H
