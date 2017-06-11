#include "microphone.h"
#include <QDebug>

Microphone::Microphone(QObject *parent) :
    QIODevice(parent)
{
}

/**
 * This function is called when playing the recorded data
 * from the speaker
 */
qint64 Microphone::readData(char *data, qint64 maxlen)
{
//  int read = qMin(maxlen, (qint64)m_buffer.size());

//  memcpy(data, m_buffer.data(), read);

//  qDebug() << "read data" << read;

//  m_buffer = m_buffer.mid(read);

//  return read;
    return 0;
}

/**
 * This function is called when recording data from the
 * microphone
 */
qint64 Microphone::writeData(const char *data, qint64 len)
{
    m_buffer.append(data, len);
    emit chunkDataOutput(m_buffer);
    qDebug() << "MIC: writing data: " << len <<" bytes.";
    m_buffer.clear(); //this tweak makes the lowest delay
    return len;
}
