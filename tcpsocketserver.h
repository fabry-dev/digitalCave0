#ifndef TCPSOCKETSERVER_H
#define TCPSOCKETSERVER_H

#include <QObject>
#include "qtcpserver.h"
#include "qmessagebox.h"
#include "qnetworkinterface.h"
class tcpSocketServer : public QObject
{
    Q_OBJECT
public:
    explicit tcpSocketServer(QObject *parent = nullptr);

private:
    QTcpServer *tcpServer;
private slots:
    void gotNewConnection(void);

public slots:
};

#endif // TCPSOCKETSERVER_H
