#ifndef VIEWPORT_HPP
#define VIEWPORT_HPP

#include <QGraphicsView>

#include "../scene/scene.hpp"

class Tool;

class Viewport : public QGraphicsView {
public:
    Viewport(Scene* scene, QWidget* parent = nullptr);

protected:
    void wheelEvent(QWheelEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    Tool* mCurrentTool;
};

#endif // VIEWPORT_HPP
