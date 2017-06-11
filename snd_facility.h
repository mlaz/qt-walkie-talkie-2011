#ifndef SND_FACILITY_H
#define SND_FACILITY_H

#include <QObject>
#include <QAudioInput>
#include <QAudioOutput>
#include <microphone.h>
#include <speaker.h>

class Snd_facility : public QObject
{
    Q_OBJECT
public:
    explicit Snd_facility(QObject *parent = 0);

signals:
    void chunk_dataOutput(QByteArray chunk);
    void not_receiving_state();
    void receiving_state();

public slots:
    void recButtonPressed();
    void recButtonReleased();

    void playAudioPacket(QByteArray audio_packet);

private slots:
    void output_state(QAudio::State state);

private:
    QAudioInput* m_audio_input;
    QAudioOutput* m_audio_output;
    Microphone* m_microphone;
    Speaker* speaker;

};

#endif // SND_FACILITY_H
