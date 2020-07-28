#include <library/binpointparser.hpp>

#include <QFile>
#include <QFileInfo>
#include <QPointF>

BinPointParserWorker::BinPointParserWorker(QObject* parent) : QObject(parent), _path(), _mutex(), _timer(nullptr)
{
    qRegisterMetaType<QList<QPointF>>("QList<QPointF>");
}

BinPointParserWorker::~BinPointParserWorker() {}


void BinPointParserWorker::started()
{
    if (not _timer) {
        _timer = new QTimer(this);
        connect(_timer, &QTimer::timeout, this, &BinPointParserWorker::timeout);
    }

    _timer->start(_timeout);
}

void BinPointParserWorker::finished()
{
    _timer->stop();
    delete _timer;
}


void BinPointParserWorker::updatePath(const QString& path)
{
    QMutexLocker lock(&_mutex);

    _readCount = 0;
    _path = path;
}

void BinPointParserWorker::timeout()
{
    readPointsSlot();
}

void BinPointParserWorker::readPointsSlot()
{
    QMutexLocker lock(&_mutex);

    auto fileInfo = QFileInfo(_path);

    if (fileInfo.exists() and fileInfo.isFile()) {
        QFile file(fileInfo.filePath());

        if (file.open(QIODevice::ReadOnly)) {
            file.skip(_readCount);
            QByteArray result = file.read(_maxReadCount); 
            _readCount += result.size();
            file.close();

            parse(result);
        }
    }
}

void BinPointParserWorker::parse(const QByteArray& data)
{
    QList<QPointF> result;

    for (int i = 0; i < data.size(); i += 4) {
        qreal x = data[i] << 8 | data[i + 1];
        qreal y = data[i + 2] << 8 | data[i + 3];

        result.push_back(QPointF(x, y));
    }

    [[maybe_unused]] auto size = result.size();

    if (not result.isEmpty())
        points(result);
}

BinPointParser::BinPointParser(QObject* parent) : QObject(parent), _workerThread(), _worker(new BinPointParserWorker())
{
    _worker->moveToThread(&_workerThread);

    connect(&_workerThread, &QThread::finished, _worker, &QObject::deleteLater);
    connect(&_workerThread, &QThread::started, _worker, &BinPointParserWorker::started);
    connect(&_workerThread, &QThread::finished, _worker, &BinPointParserWorker::finished);

    _workerThread.start();
}

BinPointParser::~BinPointParser() 
{
    _workerThread.quit();
    _workerThread.wait();
}

