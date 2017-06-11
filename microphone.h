#ifndef MICROPHONE_H
#define MICROPHONE_H

#include <QObject>
#include <QIODevice>

class Microphone : public QIODevice
{
    Q_OBJECT
public:
    explicit Microphone(QObject *parent = 0);
    virtual qint64 readData(char *data, qint64 maxlen);
    virtual qint64 writeData(const char *data, qint64 len);

signals:
    void chunkDataOutput(QByteArray chunk);

public slots:

private:
    QByteArray m_buffer;

};

#endif // MICROPHONE_H
