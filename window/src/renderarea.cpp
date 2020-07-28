#include <window/src/renderarea.hpp>

RenderArea::RenderArea(QWidget *parent) : QWidget(parent), _xmlPoints(), _scale(10)
{
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
}

RenderArea::~RenderArea() {}

QSize RenderArea::minimumSizeHint() const 
{
    return QSize(100, 100);
}

QSize RenderArea::sizeHint() const 
{
    return QSize(400, 200);
}

void RenderArea::xmlPoints(const QList<QPointF>& data)
{
    _xmlPoints = data;
    update();
}

void RenderArea::binPoints(const QList<QPointF>& data)
{
    //_binPoints = data;
    _binPoints.append(data);

    if (_binPoints.size() > _maxBinPoint) {
        while(_binPoints.size() > _maxBinPoint)
            _binPoints.pop_back();
    }

    update();
}

void RenderArea::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.setPen(Qt::black);

    for (auto& point : _binPoints)
        drawPoint(painter, point);

    painter.setPen(Qt::red);

    for (auto& point : _xmlPoints)
        drawCross(painter, point);
}

void RenderArea::wheelEvent(QWheelEvent *event)
{
    auto delta = event->angleDelta();

    if (delta.y() > 0)
        _scale *= _scaleStep;
    else if (delta.y() < 0)
        _scale /= _scaleStep;
    
    update();
}

void RenderArea::drawCross(QPainter& painter, const QPointF& point)
{
    const float shift = 1.0f;

    qreal x = point.x();
    qreal y = point.y();

    QLineF firstLine(x - shift, y + shift, x + shift, y - shift);
    QLineF secondLine(x + shift, y + shift, x - shift, y - shift);

    drawLine(painter, firstLine);
    drawLine(painter, secondLine);
}

QPointF RenderArea::center() const
{
    qreal x = width() / 2.0;
    qreal y = height() / 2.0;

    return QPointF(x, y);
}

QPointF RenderArea::transform(const QPointF& point)
{
    QPointF c = center();

    qreal x = c.x() + (point.x() * _scale);
    qreal y = c.y() + (point.y() * _scale);

    return QPointF(x, y);
}

void RenderArea::drawPoint(QPainter& painter, const QPointF& point)
{
    painter.drawPoint(transform(point));
}

void RenderArea::drawLine(QPainter& painter, const QLineF& line)
{
    painter.drawLine(QLineF(transform(line.p1()), transform(line.p2())));
}


void RenderArea::updateBinPath(const QString&)
{
    _binPoints.clear();
}