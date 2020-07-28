#ifndef WINDOW_SRC_RENDERAREA
#define WINDOW_SRC_RENDERAREA

#include <QWidget>
#include <QPointF>
#include <QPainter>
#include <QWheelEvent>

class RenderArea : public QWidget
{
    Q_OBJECT

public:
    explicit RenderArea(QWidget* parent = nullptr);
    virtual ~RenderArea();

    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;

public slots:
    void xmlPoints(const QList<QPointF>& data);
    void binPoints(const QList<QPointF>& data);

    void updateBinPath(const QString& path);

protected:
    void paintEvent(QPaintEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

private:
    QList<QPointF> _xmlPoints;
    QList<QPointF> _binPoints;
    qreal _scale;
    const qreal _scaleStep = 1.05;

    const quint16 _maxBinPoint = 16000;

private:
    QPointF center() const;
    QPointF transform(const QPointF& point);
    void drawPoint(QPainter& painter, const QPointF& point);
    void drawLine(QPainter& painter, const QLineF& line);
    void drawCross(QPainter& painter, const QPointF& point);
};

#endif /* WINDOW_SRC_RENDERAREA */
