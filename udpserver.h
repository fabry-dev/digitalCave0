#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <QObject>
#include "QDebug"
#include "QUdpSocket"
#include "QTimer"
#include "qstring.h"
#include "msgdef.h"





class UDPServer : public QObject
{
    Q_OBJECT
public:
    explicit UDPServer(QObject *parent = nullptr);
    ~UDPServer(void);
signals:

public slots:
    void sendData(QByteArray data);

private:
    QUdpSocket *udpSocket;
};

#endif // UDPSERVER_H
