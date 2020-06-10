#include "salverwidget.h"
#include "ui_salverwidget.h"
#include <QDesktopWidget>
#include <QDebug>
#include <QMetaType>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->pngUp->setPixmap(QPixmap(QString::fromUtf8(":/png/up.png")).scaled\
        (ui->label_Tx->width()/4, ui->label_Tx->height()-5, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    ui->pngDown->setPixmap(QPixmap(QString::fromUtf8(":/png/down.png")).scaled\
        (ui->label_Rx->width()/4, ui->label_Rx->height()-5, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    this->setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏
    QDesktopWidget* desktop = QApplication::desktop();
    this->setGeometry(QRect(desktop->width()-80, desktop->height()-100, 50, 30));//可设置窗口显示的方位与大
#if 1
    _netinfo = new NetInfo;
    qRegisterMetaType<NetDaTa>("NetDaTa");
    connect(_netinfo, &NetInfo::onDataUpdata, this, &Widget::dataUpdata);
    //timer excuse cmd to updata.
    _timer = new QTimer(this);
    connect(_timer, &QTimer::timeout, _netinfo, &NetInfo::onExcuseCmd);
    _timer->start(1000);
#endif
    
}

Widget::~Widget()
{
    delete ui;
    if(_netinfo){
        delete  _netinfo;
        _netinfo = nullptr;
    }
    if(_timer){
        delete _timer;
        _timer=nullptr;
    }
}

void Widget::mouseDoubleClickEvent(QMouseEvent *event)
{
    static int count=0;
    qDebug()<<"mouseDoubleClickEvent: "<<count++<<endl;
}

void Widget::dataUpdata(NetDaTa &onDataUpdata)
{
    qDebug()<<"RX:"<<onDataUpdata._byteRx <<"TX:"<<onDataUpdata._byteTx<<endl;
    ui->label_Tx->setText(onDataUpdata._byteTx);
    ui->label_Rx->setText(onDataUpdata._byteRx);
}

