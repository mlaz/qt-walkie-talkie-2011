#ifndef SPEAKER_H
#define SPEAKER_H

#include <QObject>
#include <QIODevice>

class Speaker :  public QIODevice
{
    Q_OBJECT
public:
    explicit Speaker(QObject *parent = 0);
    virtual qint64 readData(char *data, qint64 maxlen);
    virtual qint64 writeData(const char *data, qint64 len);
    void clear_buffer();

signals:

public slots:

private:
    QByteArray m_buffer;

};


#endif // SPEAKER_H
