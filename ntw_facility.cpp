#include "ntw_facility.h"
#include <QDebug>
#include <QDataStream>
#include <QNetworkInterface>

Ntw_facility::Ntw_facility(QObject *parent) :
  QObject(parent)
{

  current_state = LISTENING;

  // Instantiating the socket
  socket = new QUdpSocket(this);
  socket->bind(5824,QUdpSocket::ShareAddress);
  connect(socket,SIGNAL(readyRead()),this,SLOT(incomingPackets()));


  QNetworkInterface *inter=new QNetworkInterface();
  QList<QNetworkInterface> listInterNames = inter->allInterfaces();

  // Getting to know which interface is wifi
  int wifNum = 0;
  for (int i = 0; i < listInterNames.size(); ++i)
    {
      if (listInterNames.at(i).name() == "wlan0") {
        wifNum =  i;
      }
    }

  // Wifi interface
  QList<QNetworkAddressEntry> wifiInter = listInterNames.at(wifNum).addressEntries();

  ipv4Broad = wifiInter.at(0).broadcast();
  ipv4Local= wifiInter.at(0).ip();
}
/*
 *This slot is triggered by a signal in the audio module
 *every time a chunk of audio data is recorded from the microphone
 */
void Ntw_facility::chunkAudioOutput_ready(QByteArray chunk)
{
  qDebug() << "NTW_FAC: sending output buffer.";
  socket->writeDatagram(chunk.data(),chunk.size(),ipv4Broad,5824);
}


/*
 *Emits a signal containing data everytime a packet is received */
void Ntw_facility::incomingPackets()
{
  QByteArray datagram;
  do {
    datagram.resize(socket->pendingDatagramSize());
    QHostAddress sender;
    quint16 senderPort;
    socket->readDatagram(datagram.data(), datagram.size(),&sender,&senderPort);

    //processes datagram if sender is not localhost and state is LISTENING
    if ( ( current_state == LISTENING ) &&  (sender != ipv4Local) )
      emit audioPacket(datagram);
    datagram.clear();
  } while (socket->hasPendingDatagrams());
}

/*
 *slot for catching recButton pressed event emited by the UI
 */
void Ntw_facility::recButton_pressed()
{
  current_state = SENDING;
  qDebug() << "state changed to sending"<< current_state;
}

/*
 *slot for catching recButton released event emited by the UI
 */
void Ntw_facility::recButton_released()
{
  current_state = LISTENING;
  qDebug() << "state changed to listening" << current_state;
}
