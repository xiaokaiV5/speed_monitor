#include <QFile>
#include <QDebug>
#include <iostream>
#include <QString>
#include "linuxHardInfo.h"

using namespace std;

CpuUsage::CpuUsage():_cpufileName("/proc/stat")
{
    
}

int CpuUsage::getCpuUsage()
{
    quint64 idle, total;
    QFile cpufile(_cpufileName);
    bool ok;
    if (cpufile.open(QIODevice::ReadOnly|QIODevice::Text)){
        qDebug() << "Can't open the file!" << _cpufileName << endl;
        return  -1;
    }
    
    QString line = cpufile.readLine().data();
    if (line.contains("cpu")){
        QStringList list = line.split(" ");
        list.removeFirst();//ÒÆ³ýµÚÒ»¸ö×Ö·û´®"cpu"
        idle = list[3].toULongLong(&ok, 10);
        
        auto totalCount = [&list, &ok]()-> quint64 {
                quint64 total=0;
                for(auto iter = list.begin(); iter!=list.end()&&iter->length()>0; ++iter)
                    total += iter->toULongLong(&ok, 10);
                return total;
        };
        total = totalCount();
        
        _cpuUsage = QString::number((double)(100-((double)(idle-_idle)/(double)(total-_total))*100), 'f', 1).toDouble();
        qDebug()<<"cpu usage:%"<<_cpuUsage<<endl;
        _idle = idle;
        _total = total;
    }
    
    return 0;
}




MemInfo::MemInfo():_memfileName("/proc/meminfo")
{
    
}

int MemInfo::getMemUsage()
{
    QFile memfile(_memfileName);
    bool ok;
    if(memfile.open(QIODevice::ReadOnly|QIODevice::Text)){
        qDebug()<<"Can't open the file!"<<_memfileName<<endl;
        return -1;
    }
    while (!memfile.atEnd()) {
        QByteArray line = memfile.readLine();
        QString str(line);
        QStringList list = str.split(" ");
        if (str.contains("MemTotal")){
             qDebug()<< list << endl;
             _memtotal = list[2].toULongLong(&ok, 10);
        }
        else if (str.contains("MemAvailable")){
            qDebug()<< list << endl;
            _memAvailable = list[2].toULongLong(&ok, 10);
        }
    }
    
    return QString::number((double)(_memtotal-_memAvailable)/1024.0/1024.0, 'f', 1).toInt();
}




