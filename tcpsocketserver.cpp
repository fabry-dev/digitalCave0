#include "tcpsocketserver.h"
#include "qdatetime.h"

tcpSocketServer::tcpSocketServer(QObject *parent) : QObject(parent)
{
/*

*/


    QString ipAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // use the first non-localhost IPv4 address
    for (int i = 0; i < ipAddressesList.size(); ++i)
    {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost && ipAddressesList.at(i).toIPv4Address())
        {
            ipAddress = ipAddressesList.at(i).toString();

            break;
        }
    }



    // if we did not find one, use IPv4 localhost
    if (ipAddress.isEmpty())
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();


    qDebug()<<"The server is running on IP:"<<ipAddress<<" port:";//<<tcpServer->serverPort();


    tcpServer = new QTcpServer(this);

    if (!tcpServer->listen(QHostAddress(ipAddress),60000))
    {
        qDebug()<<"could not create tcp socket";
        return;
    }
    else
        qDebug()<<"starting tcp server";


    connect(tcpServer,SIGNAL(newConnection()),this,SLOT(gotNewConnection()));


    QTimer *t0 = new QTimer(this);
    connect(t0,SIGNAL(timeout()),this,SLOT(sendData()));
    t0->start(5000);


}



void tcpSocketServer::gotNewConnection()
{

    qDebug()<<"nu connection!";


   // connect(clientConnection, &QAbstractSocket::disconnected,clientConnection, &QObject::deleteLater);




    QTcpSocket *clientConnection = tcpServer->nextPendingConnection();





    clients.push_back(clientConnection);
}


void tcpSocketServer::sendData()
{
    qDebug()<<"sending";

    QByteArray block;
    QDataStream out(&block,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_9);
    out<<QDateTime::currentDateTime().toString("hh:mm:ss.zzz");

    for(auto client:clients)
    {

    client->write(block);

    }


}
