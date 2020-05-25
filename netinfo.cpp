
#include <iostream>
#include <QDebug>
#include <math.h>
#include "netinfo.h"
using namespace std;

void NetDaTa::NetDaTaLoad(const QString &nicName, double rx, double tx)
{
    _fi_r=rx-_rx, _fi_t=tx-_tx;

    int rxUnit=0, txUnit=0;//0: byte 1:kB/s 2:MB/s 3:GB/s
    _NIC_name = nicName;
    while (_fi_r >= unitChange) {
        _fi_r/=(double)unitChange;
        rxUnit++;
    }
    while (_fi_t >= unitChange){
        _fi_t/=(double)unitChange;
        txUnit++;
    }
    
    _byteRx = QString::number((double)_fi_r, 'f', 1)+ " " + unit[rxUnit];
    _byteTx = QString::number((double)_fi_t, 'f', 1)+ " " + unit[txUnit];
    
    _fi_r=rx-_rx, _fi_t=tx-_tx;
    _rx = rx, _tx = tx;
    
    dataActive = true;
}

NetInfo::NetInfo(): _maxSupportNetCardNum(8),\
    cmd_getNetData("cat /proc/net/dev |awk  '{print $1 \" \" $2 \" \" $10}' |awk 'NR>2' |sed 's/://g'")

{
    _netDaTa = new NetDaTa [_maxSupportNetCardNum];

    _cmd = new QProcess(nullptr);
    connect(_cmd , SIGNAL(readyReadStandardOutput()) , this , SLOT(onReadoutput()));
    connect(_cmd , SIGNAL(readyReadStandardError()) , this , SLOT(onReaderror()));

    _cmd->start("bash");
    _cmd->waitForStarted();
}

NetInfo::~NetInfo()
{
    if (_netDaTa){
        delete[] _netDaTa;
        _netDaTa = nullptr;
    }
    if(_cmd){
        _cmd->terminate();
        _cmd->waitForFinished();
    }
}

void NetInfo::cmdGetNetData()
{
    _cmd->write(this->cmd_getNetData.toLocal8Bit() + '\n');
}

NetDaTa *NetInfo::netSpeedCompute()
{
    NetDaTa *point = &_netDaTa[0];
    for(int i =0; i<_maxSupportNetCardNum; ++i){
        if(_netDaTa[i].isActive()){
            point = (_netDaTa[i].get_fi_data() > point->get_fi_data()?(&_netDaTa[i]):(point));
        }
    }
    return point;    
}

void NetInfo::onReadoutput()
{
    QString output = _cmd->readAllStandardOutput().data();
    QStringList list = output.split("\n");

    int index = 0;
    for (auto iter = list.begin(); iter != list.end();++iter){
        if (iter->contains("lo") || !iter->length())
            continue;

        _netDaTa[index++].NetDaTaLoad( iter->split(" ").at(0),
           iter->split(" ").at(1).toDouble() , iter->split(" ").at(2).toDouble());
        //cout << iter->toLocal8Bit().data()<<endl;
    }
    NetDaTa *netdata = netSpeedCompute();
    emit onDataUpdata(*netdata);
}

void NetInfo::onReaderror()
{
    qDebug()<< "onReaderror" <<endl;
}

void NetInfo::onExcuseCmd()
{
    this->cmdGetNetData();
}


