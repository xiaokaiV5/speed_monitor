#include <QQuickWidget>
#include <QQuickView>
#include "allinfowidget.h"

AllInfoWidget::AllInfoWidget(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::infowidget)
{
    ui->setupUi(this);
    
    QQuickWidget *view = new QQuickWidget;
    view->setSource(QUrl::fromLocalFile(":/gauge_arc.qml"));
    view->show();
}
