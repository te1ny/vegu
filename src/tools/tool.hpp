#ifndef TOOL_HPP
#define TOOL_HPP

#include <QObject>
#include <QMouseEvent>

#include "../scene/scene.hpp"

class Viewport;

class Tool : public QObject {
public:
    virtual void activate() {}
    virtual void deactivate() {}

    virtual void mousePressEvent(QMouseEvent* event) {}
    virtual void mouseMoveEvent(QMouseEvent* event) {}
    virtual void mouseReleaseEvent(QMouseEvent* event) {}

    Tool(Viewport* viewport);
    virtual ~Tool() = default;

protected:
    Viewport* mViewport;
    Scene* mScene;
};

#endif // TOOL_HPP
