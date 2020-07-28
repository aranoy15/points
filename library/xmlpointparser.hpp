#ifndef LIBRARY_XMLPOINTERPARSER
#define LIBRARY_XMLPOINTERPARSER

#include <qobject.h>

class XmlPointParser : public QObject
{
    Q_OBJECT

public:
    explicit XmlPointParser(QObject* parent = nullptr);
    virtual ~XmlPointParser();

public slots:
    void updatePoints(const QByteArray& data);

signals:
    void points(const QList<QPointF>& data);
};

#endif /* LIBRARY_XMLPOINTERPARSER */
