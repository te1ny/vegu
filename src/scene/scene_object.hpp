#ifndef SCENE_OBJECT_HPP
#define SCENE_OBJECT_HPP

#include <QGraphicsObject>
#include <QPen>
#include <QBrush>
#include <qpoint.h>

class SceneObject : public QGraphicsObject {
    Q_OBJECT

    Q_PROPERTY(QPointF Position READ position WRITE setPosition MEMBER mPosition)
    Q_PROPERTY(qreal Rotation READ rotation WRITE setRotation MEMBER mRotation)
    Q_PROPERTY(qreal Scale READ scale WRITE setScale MEMBER mScale)
    Q_PROPERTY(QColor FillColor READ fillColor WRITE setFillColor)
    Q_PROPERTY(QColor StrokeColor READ strokeColor WRITE setStrokeColor)
    Q_PROPERTY(qreal Layer READ layer WRITE setLayer MEMBER mLayer)

public:
    QPointF position() const;
    void setPosition(QPointF position);

    qreal rotation() const;
    void setRotation(qreal rotation);

    qreal scale() const;
    void setScale(qreal scale);

    QColor fillColor() const;
    void setFillColor(const QColor& color);

    QColor strokeColor() const;
    void setStrokeColor(const QColor& color);

    qreal layer() const;
    void setLayer(qreal layer);

    virtual QRectF boundingRect() const = 0;
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) = 0;

    SceneObject(QGraphicsItem* parent = nullptr);
    virtual ~SceneObject() = default;

protected:
    QPen mPen;
    QBrush mBrush;

private:
    QPointF mPosition;
    qreal mRotation;
    qreal mScale;
    qreal mLayer;
};

#endif // SCENE_OBJECT_HPP
