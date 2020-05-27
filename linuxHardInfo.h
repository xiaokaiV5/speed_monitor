#ifndef LINUXHARDINFO_H
#define LINUXHARDINFO_H
#include <QObject>


class CpuUsage : public QObject
{
    Q_OBJECT
public:
    CpuUsage();
    virtual ~CpuUsage() {};
    /* Get cpu usage. */
    int getCpuUsage();
private:
    const QString _cpufileName;
    quint64 _total;
    quint64 _idle;
    double _cpuUsage;
};


class MemInfo : public QObject
{
    Q_OBJECT
public:
    MemInfo();
    virtual ~MemInfo() {};
    
    /* Get memory usage. */
    int getMemUsage();
    
private:
    const QString _memfileName;
    quint64 _memtotal;
    quint64 _memAvailable;
};


class HardUsage :public CpuUsage, public MemInfo
{
public:
    HardUsage();
    ~HardUsage();
    
private:
    
};

#endif
