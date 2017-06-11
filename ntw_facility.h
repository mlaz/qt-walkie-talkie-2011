#ifndef NTW_FACILITY_H
#define NTW_FACILITY_H

#include <QObject>
#include <QUdpSocket>



class Ntw_facility : public QObject
{
  Q_OBJECT
    public:
  explicit Ntw_facility(QObject *parent = 0);
  //    void readBuffer(QByteArray buffer);

 signals:
  void audioPacket(QByteArray audio_packet);

  public slots:

  void chunkAudioOutput_ready(QByteArray chunk);
  //  void restart_receiving();
  //  void stop_receiving();
  void recButton_pressed();
  void recButton_released();

  private slots:
  void incomingPackets();

 private:
  enum state {LISTENING, SENDING};
  state current_state;
  QUdpSocket* socket;
  QHostAddress ipv4Broad;
  QHostAddress ipv4Local;

};

#endif // NTW_FACILITY_H
