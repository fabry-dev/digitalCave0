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





    tcpServer = new QTcpServer(this);

    if (!tcpServer->listen(QHostAddress(ipAddress),60000))
    {
        qDebug()<<"could not create tcp socket";
        return;
    }
    else
        qDebug()<<"starting tcp server";

     qDebug()<<"The server is running on IP:"<<ipAddress<<" port:"<<tcpServer->serverPort();

    connect(tcpServer,SIGNAL(newConnection()),this,SLOT(gotNewConnection()));


}



void tcpSocketServer::gotNewConnection()
{
    // connect(clientConnection, &QAbstractSocket::disconnected,clientConnection, &QObject::deleteLater);

    QTcpSocket *clientConnection = tcpServer->nextPendingConnection();
    qDebug()<<"new connection "<<clientConnection->peerAddress();
    clients.push_back(clientConnection);
    qDebug()<<"connected clients: "<<clients.size();

    connect(clientConnection,SIGNAL(disconnected()),this,SLOT(gotNewDisconnection()));
}



void tcpSocketServer::gotNewDisconnection()
{
  QTcpSocket *clientConnection = (QTcpSocket*)QObject::sender();

  clientConnection->deleteLater();

  for(int i = 0;i<clients.size();i++)
  {
      if(clients[i]==clientConnection)
      {

          clients.erase(clients.begin() + i);
          break;
      }

  }

  qDebug()<<"connected clients: "<<clients.size();
}



void tcpSocketServer::sendData(QString data)
{
    QByteArray block;
    QDataStream out(&block,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_9);
    //out<<QDateTime::currentDateTime().toString("hh:mm:ss.zzz");
    out<<data;
    for(auto client:clients)
        client->write(block);

    qDebug()<<"<< "<<data;
}




void tcpSocketServer::startVideo(void)
{
    sendData("start");
}


void tcpSocketServer::stopVideo(void)
{
    sendData("stop");
}
