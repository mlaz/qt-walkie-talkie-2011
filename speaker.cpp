#include "speaker.h"
#include <QDebug>

Speaker::Speaker(QObject *parent) :
    QIODevice(parent)
{
}



/**
 * This function is called when playing the recorded data
 * from the speaker
 */
qint64 Speaker::readData(char *data, qint64 maxlen)
{

    int read = qMin(maxlen, (qint64)m_buffer.size());

    memcpy(data, m_buffer.data(), read);

    //    qDebug() << "read data" << read;

    qDebug() << "SPEAKER: reading data: " << read <<" bytes.";
    m_buffer.clear(); //this tweak makes the lowest delay

    return read;
}

/**
 * This function is called when recording data from the
 * microphone
 */
qint64 Speaker::writeData(const char *data, qint64 len)
{
    m_buffer.append(data, len);
    qDebug() << "SPEAKER: writing data: " << len <<" bytes.";
    return len;
}

void Speaker::clear_buffer()
{
    m_buffer.clear();
}
