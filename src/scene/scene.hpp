#ifndef SCENE_HPP
#define SCENE_HPP

#include <QGraphicsScene>

#include "scene_object.hpp"

class Scene : public QGraphicsScene {
    Q_OBJECT

public:
    void add(SceneObject* object);
    void remove(SceneObject* object);
    QList<SceneObject*> selectedObjects();

    Scene(QObject* parent = nullptr);

signals:
    void sceneChanged();
    void objectSelected(SceneObject* object);
};

#endif // SCENE_HPP
