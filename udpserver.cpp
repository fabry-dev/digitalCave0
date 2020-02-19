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




void UDPServer::startIntro(void)
{
    sendData("start");
}

void UDPServer::stopIntro(void)
{

    sendData("stop");
}


UDPServer::~UDPServer(void)
{

}
