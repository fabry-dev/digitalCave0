#include "tcpsocketserver.h"

tcpSocketServer::tcpSocketServer(QObject *parent) : QObject(parent)
{

    tcpServer = new QTcpServer(this);


    if (!tcpServer->listen())
    {
        qDebug()<<"could not create tcp socket";
        return;
    }
    else
        qDebug()<<"starting tcp server";



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


    qDebug()<<"The server is running on IP:"<<ipAddress<<" port:"<<tcpServer->serverPort();


    connect(tcpServer,SIGNAL(newConnection()),this,SLOT(gotNewConnection()));

}



void tcpSocketServer::gotNewConnection()
{

    qDebug()<<"nu connection!";


}
