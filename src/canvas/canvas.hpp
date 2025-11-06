#ifndef CANVAS_HPP
#define CANVAS_HPP

#include <QGraphicsScene>

class Canvas : public QGraphicsScene {
    Q_OBJECT

public:
    Canvas(QObject* parent = nullptr);
};

#endif // CANVAS_HPP
