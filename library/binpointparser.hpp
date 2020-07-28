#ifndef LIBRARY_BINPOINTPARSER
#define LIBRARY_BINPOINTPARSER

#include <QObject>
#include <QThread>
#include <QTimer>
#include <QMutex>

class BinPointParserWorker : public QObject
{
    Q_OBJECT

public:
    explicit BinPointParserWorker(QObject* parent = nullptr);
    virtual ~BinPointParserWorker();

signals:
    void points(const QList<QPointF>& data);

public slots:
    void updatePath(const QString& path);
    void timeout();

    void started();
    void finished();

private:
    QString _path;
    QMutex _mutex;
    QTimer *_timer;
    quint32 _readCount;

    const quint32 _maxReadCount = 4000;
    const quint16 _timeout = 100;

private:
    void readPointsSlot();
    void parse(const QByteArray& data);
};


class BinPointParser : public QObject
{
    Q_OBJECT

public:
    explicit BinPointParser(QObject* parent = nullptr);
    virtual ~BinPointParser();

    BinPointParserWorker* worker() const { return _worker; }

private:
    QThread _workerThread;
    BinPointParserWorker *_worker;
};

#endif /* LIBRARY_BINPOINTPARSER */

