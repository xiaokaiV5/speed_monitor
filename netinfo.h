#ifndef NETINFO_H
#define NETINFO_H
#include <QObject>
#include <QString>
#include <QProcess>
#include <QtCore/qmath.h>
static const  quint32 unitChange=qPow(2,10);
static const char unit[4][8]={"B/s", "KB/s", "MB/s","GB/s"};

//network card data
class NetDaTa{
public:
    NetDaTa(){_tx=_rx=0;};
    NetDaTa(QString &nicName){_NIC_name = nicName;_tx=_rx=0;};
    void setNIC(QString &nicName){_NIC_name = nicName;};

    void NetDaTaLoad(const QString &nicName, double rx, double tx);
    quint64 get_fi_data(){return (_rx +_tx);};
    //quint64
    bool isActive(){return  dataActive;};
public:
    QString _byteRx;
    QString _byteTx;
private:
    QString _NIC_name;

    double _rx;    //Statistics of data received by the network card.
    double _tx;    //Statistics of data sent by network card.
    double _fi_r;  // The difference in received data between the two tests.
    double _fi_t;  // Difference in transmitted data between two tests
    bool dataActive;
};

//network card function
class NetInfo :public QObject
{
    Q_OBJECT
public:
    NetInfo();
    ~NetInfo();
    void cmdGetNetData();
    NetDaTa *netSpeedCompute();
public slots:
    void onReadoutput();
    void onReaderror();
    void onExcuseCmd();

Q_SIGNALS:
    void onDataUpdata(NetDaTa &netdata);
private:
    QProcess *_cmd;
    NetDaTa *_netDaTa; //Support up to 8 network cards.
    const int _maxSupportNetCardNum;
    const QString cmd_getNetData ;
};

#endif // NETINFO_H
