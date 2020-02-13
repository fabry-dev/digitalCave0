#include "udpserver.h"

UDPServer::UDPServer(QObject *parent) : QObject(parent)
{
    udpSocket = new QUdpSocket(this);
    QTimer *t0 = new QTimer(this);
}




void UDPServer::sendData(QByteArray data)
{
    QByteArray datagram = data;
    udpSocket->writeDatagram(datagram, QHostAddress::Broadcast, 45454);
}





UDPServer::~UDPServer(void)
{

}
