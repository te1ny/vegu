#include "inspector.hpp"

#include <QMetaObject>
#include <QMetaProperty>
#include <QLabel>
#include <QPushButton>

Inspector::Inspector(QWidget* parent)
    : mCurrentObject(nullptr)
    , mLayout(new QVBoxLayout(this))
{
    setLayout(mLayout);
}

void Inspector::setObject(SceneObject* object) {
    if (!object)
        return;

    clear();
    mCurrentObject = object;

    const QMetaObject* meta = mCurrentObject->metaObject();
    for (auto i = meta->propertyOffset(); i < meta->propertyOffset(); i++) {
        QMetaProperty property = meta->property(i);
        if (property.isWritable())
            addEditorProperty(property);
    }
}

void Inspector::clear() {
    while (mLayout->count() > 0) {
        auto item = mLayout->takeAt(0);
        delete item->widget();
        delete item;
    }
}

void Inspector::addEditorProperty(const QMetaProperty& property) {
    QLabel* label = new QLabel(property.name());
    mLayout->addWidget(label);

    if (property.typeId() == QMetaType::QColor) {
        QPushButton* button = new QPushButton("Choose Color");
        mLayout->addWidget(button);
    } else if (property.typeId() == QMetaType::QPointF) {

    }
}
