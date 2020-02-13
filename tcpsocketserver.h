#ifndef TCPSOCKETSERVER_H
#define TCPSOCKETSERVER_H

#include <QObject>
#include "qtcpserver.h"
#include "qmessagebox.h"
#include "qtcpsocket.h"
#include "qnetworkinterface.h"
#include "qtimer.h"
#include "QDebug"

class tcpSocketServer : public QObject
{
    Q_OBJECT
public:
    explicit tcpSocketServer(QObject *parent = nullptr);

private:
    QTcpServer *tcpServer;
    std::vector<QTcpSocket*> clients;
private slots:
    void gotNewConnection(void);
    void gotNewDisconnection(void);
    void sendData(QString data);
    void startVideo(void);
    void stopVideo(void);

public slots:
};

#endif // TCPSOCKETSERVER_H
