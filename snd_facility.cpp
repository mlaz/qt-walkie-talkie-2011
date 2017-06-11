#include "snd_facility.h"
#include <QDebug>

Snd_facility::Snd_facility(QObject *parent) :
    QObject(parent)
{
    // Audio initialization
    QAudioFormat format;
    format.setFrequency(8000);
    format.setChannels(1);
    format.setSampleSize(16);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::SignedInt);
    QAudioDeviceInfo info = QAudioDeviceInfo::defaultInputDevice();

    if (!info.isFormatSupported(format)) {
        qDebug()<<"default format not supported try to use nearest";
        format = info.nearestFormat(format);
    }

    m_audio_input = new QAudioInput(format, this);
    m_audio_output = new QAudioOutput(format, this);


    connect(m_audio_output, SIGNAL(stateChanged(QAudio::State)),this, SLOT(output_state(QAudio::State)));

    //create mic
    m_microphone = new Microphone(this);
    m_microphone->open(QIODevice::ReadWrite);

    //this signal is emitted by the mic toward the network module
    //it contains the chunk audio data and the lenght of the chunk
    connect(m_microphone,SIGNAL(chunkDataOutput(QByteArray)),this,SIGNAL(chunk_dataOutput(QByteArray)));

    //create speaker
    speaker = new Speaker(this);
    speaker->open(QIODevice::ReadWrite);
}


//this slot is triggered by a signal emitted in the GUI when
//the user press the rec button
//it emits a signal to the network module that will stop the
//reception of packets
void Snd_facility::recButtonPressed()
{
    if(m_audio_input->state() != QAudio::StoppedState)
    {
        qDebug() << "Unexpected audio state";
        return;
    }

    emit not_receiving_state();
    m_audio_input->start(m_microphone);

}

//this slot is triggered by a signal emitted in the GUI when
//the user release the rec button
//it emits a signal to the network module that will restart the
//reception of packets
void Snd_facility::recButtonReleased()
{
  //    qDebug() << "STATE = " << m_audio_input->state();
    emit receiving_state();
    m_audio_input->stop();
//    qDebug() << "STATE = " << m_audio_input->state();
}


//this slot is triggered by a signal emitted in the network module
//every time an audio packet is received
void Snd_facility::playAudioPacket(QByteArray audio_packet)
{
    qDebug() << "IN playAudioPacket: QAudioOutput->state()  =  "<< m_audio_output->state();
    if(m_audio_output->state() == QAudio::StoppedState)
    {
        m_audio_output->start(speaker);
        qDebug() << "SND_FAC: turning on speaker.";
    }
    speaker->writeData(audio_packet.data(),audio_packet.size());

}



void Snd_facility::output_state(QAudio::State state)
{
    if(m_audio_output->error() != QAudio::NoError)
        {


            qDebug() << "Output Audio error" << m_audio_output->error();
        }

    if(state == QAudio::IdleState)
    {
        qDebug() << "Stopping output";

        // No more data to play
        speaker->clear_buffer();
        m_audio_output->stop();



    }
}
