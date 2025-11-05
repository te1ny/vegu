#ifndef INSPECTOR_HPP
#define INSPECTOR_HPP

#include <QWidget>
#include <QVBoxLayout>

#include "../scene/scene_object.hpp"

class Inspector : public QWidget {
    Q_OBJECT

public:
    Inspector(QWidget* parent = nullptr);

public slots:
    void setObject(SceneObject* object);

private:
    void clear();
    void addEditorProperty(const QMetaProperty& property);

    QVBoxLayout* mLayout;
    SceneObject* mCurrentObject;
};

#endif // INSPECTOR_HPP
