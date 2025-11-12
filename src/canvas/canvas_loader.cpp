#include "canvas_loader.hpp"
#include "canvas.hpp"

#include <QGraphicsScene>
#include <QPen>
#include <QBrush>
#include <fstream>
#include <QTransform>
#include <qgraphicsitem.h>

namespace {

// Вспомогательные функции
void applyCommonProperties(QGraphicsItem* item, const toml::table& table);
QColor colorFromTomlArray(const toml::array* arr);
toml::array colorToTomlArray(const QColor& color);
void applyPenProperties(QPen& pen, const toml::table& table);
void applyBrushProperties(QBrush& brush, const toml::table& table);
void applyTransform(QGraphicsItem* item, const toml::table& table);

// Функции для создания элементов
QGraphicsItem* createRectFromTable(const toml::table& table);
QGraphicsItem* createEllipseFromTable(const toml::table& table);
QGraphicsItem* createLineFromTable(const toml::table& table);

} // namespace

void CanvasLoader::saveToToml(Canvas* canvas, const QString& fileName) {
    toml::table root;
    toml::array itemsArray;

    const QList<QGraphicsItem*> sortedItems = canvas->items(Qt::AscendingOrder);

    for (QGraphicsItem* item : sortedItems) {
        if (!(item->flags() & QGraphicsItem::ItemIsSelectable))
            continue;

        if (auto rectItem = dynamic_cast<QGraphicsRectItem*>(item))
            itemsArray.push_back(rectToTable(rectItem));
        else if (auto ellipseItem = dynamic_cast<QGraphicsEllipseItem*>(item))
            itemsArray.push_back(ellipseToTable(ellipseItem));
        else if (auto lineItem = dynamic_cast<QGraphicsLineItem*>(item))
            itemsArray.push_back(lineToTable(lineItem));
    }

    root.insert("items", itemsArray);
    
    try {
        std::ofstream file(fileName.toStdString());
        file << root;
    } catch (const std::exception& e) {
        qDebug() << "Failed to save file:" << e.what();
    }
}

void CanvasLoader::loadFromToml(Canvas* canvas, const QString& fileName) {
    try {
        toml::table root = toml::parse_file(fileName.toStdString());
        toml::array* itemsArray = root["items"].as_array();

        if (!itemsArray) return;
        
        canvas->clear();
        QList<QGraphicsItem*> loadedItems;

        for (auto& item : *itemsArray) {
            if (toml::table* itemTable = item.as_table()) {
                if (QGraphicsItem* newItem = createItemFromTable(*itemTable)) {
                    canvas->addItem(newItem);
                    loadedItems.append(newItem);
                }
            }
        }

        restoreStackingOrder(loadedItems);

    } catch (const toml::parse_error& e) {
        qDebug() << "TOML parse error:" << e.what();
    } catch (const std::exception& e) {
        qDebug() << "Failed to load file:" << e.what();
    }
}

QGraphicsItem* CanvasLoader::createItemFromTable(const toml::table& table) {
    auto type = table.get("type")->as_string();
    if (!type) return nullptr;

    const std::string_view typeStr = type->get();
    QGraphicsItem* item = nullptr;

    if (typeStr == "rect") {
        item = createRectFromTable(table);
    } else if (typeStr == "ellipse") {
        item = createEllipseFromTable(table);
    } else if (typeStr == "line") {
        item = createLineFromTable(table);
    }

    if (item) {
        applyCommonProperties(item, table);
    }

    return item;
}

void CanvasLoader::restoreStackingOrder(const QList<QGraphicsItem*>& items) {
    for (int i = 1; i < items.size(); ++i) {
        if (items[i]->zValue() == items[i-1]->zValue()) {
            items[i-1]->stackBefore(items[i]);
        }
    }
}

toml::table CanvasLoader::rectToTable(QGraphicsRectItem* item) {
    toml::table table = itemToTable(item);
    table.insert("type", "rect");
    
    const QRectF rect = item->rect();
    table.insert("rect_x", rect.x());
    table.insert("rect_y", rect.y());
    table.insert("rect_width", rect.width());
    table.insert("rect_height", rect.height());
    
    return table;
}

toml::table CanvasLoader::ellipseToTable(QGraphicsEllipseItem* item) {
    toml::table table = itemToTable(item);
    table.insert("type", "ellipse");
    
    const QRectF rect = item->rect();
    table.insert("rect_x", rect.x());
    table.insert("rect_y", rect.y());
    table.insert("rect_width", rect.width());
    table.insert("rect_height", rect.height());
    
    return table;
}

toml::table CanvasLoader::lineToTable(QGraphicsLineItem* item) {
    toml::table table = itemToTable(item);
    table.insert("type", "line");
    
    const QLineF line = item->line();
    table.insert("line_x1", line.x1());
    table.insert("line_y1", line.y1());
    table.insert("line_x2", line.x2());
    table.insert("line_y2", line.y2());
    
    return table;
}

toml::table CanvasLoader::itemToTable(QGraphicsItem* item) {
    toml::table table;
    
    // Базовые свойства
    table.insert("pos_x", item->pos().x());
    table.insert("pos_y", item->pos().y());
    table.insert("z_value", item->zValue());
    table.insert("flags", static_cast<int>(item->flags()));
    
    // Трансформация
    const QTransform transform = item->transform();
    table.insert("transform_m11", transform.m11());
    table.insert("transform_m12", transform.m12());
    table.insert("transform_m13", transform.m13());
    table.insert("transform_m21", transform.m21());
    table.insert("transform_m22", transform.m22());
    table.insert("transform_m23", transform.m23());
    table.insert("transform_m31", transform.m31());
    table.insert("transform_m32", transform.m32());
    table.insert("transform_m33", transform.m33());
    
    // Свойства пера и кисти
    if (auto shapeItem = dynamic_cast<QAbstractGraphicsShapeItem*>(item)) {
        saveShapeProperties(shapeItem, table);
    } else if (auto lineItem = dynamic_cast<QGraphicsLineItem*>(item)) {
        saveLineProperties(lineItem, table);
    }

    return table;
}

void CanvasLoader::saveShapeProperties(QAbstractGraphicsShapeItem* item, toml::table& table) {
    // Сохраняем стиль кисти
    table.insert("brush_style", static_cast<int>(item->brush().style()));
    
    // Сохраняем цвет кисти, если стиль не NoBrush
    if (item->brush().style() != Qt::NoBrush) {
        table.insert("fill_color", colorToTomlArray(item->brush().color()));
    }

    // Перо
    savePenProperties(item->pen(), table);
}

void CanvasLoader::saveLineProperties(QGraphicsLineItem* item, toml::table& table) {
    savePenProperties(item->pen(), table);
}

void CanvasLoader::savePenProperties(const QPen& pen, toml::table& table) {
    table.insert("pen_color", colorToTomlArray(pen.color()));
    table.insert("pen_width", pen.widthF());
    table.insert("pen_style", static_cast<int>(pen.style()));
    table.insert("pen_cap_style", static_cast<int>(pen.capStyle()));
    table.insert("pen_join_style", static_cast<int>(pen.joinStyle()));
}

namespace {

// Реализации вспомогательных функций

void applyCommonProperties(QGraphicsItem* item, const toml::table& table) {
    // Позиция
    if (auto pos_x = table.get("pos_x")) {
        if (auto pos_y = table.get("pos_y")) {
            item->setPos(pos_x->as_floating_point()->get(), 
                        pos_y->as_floating_point()->get());
        }
    }
    
    // Z-value
    if (auto z_value = table.get("z_value")) {
        item->setZValue(z_value->as_floating_point()->get());
    }
    
    // Трансформация
    applyTransform(item, table);
    
    // Флаги
    if (auto flags = table.get("flags")) {
        item->setFlags(static_cast<QGraphicsItem::GraphicsItemFlags>(
            static_cast<int>(flags->as_integer()->get())));
    }

    // Свойства пера и кисти
    if (auto shapeItem = dynamic_cast<QAbstractGraphicsShapeItem*>(item)) {
        QBrush brush = shapeItem->brush();
        applyBrushProperties(brush, table);
        shapeItem->setBrush(brush);  // Важно: устанавливаем кисть обратно!
        
        QPen pen = shapeItem->pen();
        applyPenProperties(pen, table);
        shapeItem->setPen(pen);
    } else if (auto lineItem = dynamic_cast<QGraphicsLineItem*>(item)) {
        QPen pen = lineItem->pen();
        applyPenProperties(pen, table);
        lineItem->setPen(pen);
    }
}

void applyTransform(QGraphicsItem* item, const toml::table& table) {
    if (table.contains("transform_m11")) {
        QTransform transform(
            table.get("transform_m11")->as_floating_point()->get(),
            table.get("transform_m12")->as_floating_point()->get(),
            table.get("transform_m13")->as_floating_point()->get(),
            table.get("transform_m21")->as_floating_point()->get(),
            table.get("transform_m22")->as_floating_point()->get(),
            table.get("transform_m23")->as_floating_point()->get(),
            table.get("transform_m31")->as_floating_point()->get(),
            table.get("transform_m32")->as_floating_point()->get(),
            table.get("transform_m33")->as_floating_point()->get()
        );
        item->setTransform(transform);
    }
}

void applyPenProperties(QPen& pen, const toml::table& table) {
    if (table.contains("pen_color")) {
        if (auto penColor = table.get("pen_color")) {
            if (auto arr = penColor->as_array()) {
                pen.setColor(colorFromTomlArray(arr));
            }
        }
    }
    
    if (auto pen_width = table.get("pen_width")) {
        pen.setWidthF(pen_width->as_floating_point()->get());
    }
    if (auto pen_style = table.get("pen_style")) {
        pen.setStyle(static_cast<Qt::PenStyle>(pen_style->as_integer()->get()));
    }
    if (auto pen_cap_style = table.get("pen_cap_style")) {
        pen.setCapStyle(static_cast<Qt::PenCapStyle>(pen_cap_style->as_integer()->get()));
    }
    if (auto pen_join_style = table.get("pen_join_style")) {
        pen.setJoinStyle(static_cast<Qt::PenJoinStyle>(pen_join_style->as_integer()->get()));
    }
}

void applyBrushProperties(QBrush& brush, const toml::table& table) {
    // Восстанавливаем стиль кисти
    if (auto brush_style = table.get("brush_style")) {
        brush.setStyle(static_cast<Qt::BrushStyle>(brush_style->as_integer()->get()));
    }
    
    // Восстанавливаем цвет кисти, если он есть
    if (auto fillColor = table.get("fill_color")) {
        if (auto arr = fillColor->as_array()) {
            brush.setColor(colorFromTomlArray(arr));
        }
    }
}

QColor colorFromTomlArray(const toml::array* arr) {
    if (arr && arr->size() >= 4) {
        return QColor(
            static_cast<int>(arr->get(0)->as_integer()->get()),
            static_cast<int>(arr->get(1)->as_integer()->get()),
            static_cast<int>(arr->get(2)->as_integer()->get()),
            static_cast<int>(arr->get(3)->as_integer()->get())
        );
    }
    return Qt::black;
}

toml::array colorToTomlArray(const QColor& color) {
    toml::array result;
    result.push_back(color.red());
    result.push_back(color.green());
    result.push_back(color.blue());
    result.push_back(color.alpha());
    return result;
}

QGraphicsItem* createRectFromTable(const toml::table& table) {
    QRectF rect(
        table.get("rect_x")->as_floating_point()->get(),
        table.get("rect_y")->as_floating_point()->get(),
        table.get("rect_width")->as_floating_point()->get(),
        table.get("rect_height")->as_floating_point()->get()
    );
    return new QGraphicsRectItem(rect);
}

QGraphicsItem* createEllipseFromTable(const toml::table& table) {
    QRectF rect(
        table.get("rect_x")->as_floating_point()->get(),
        table.get("rect_y")->as_floating_point()->get(),
        table.get("rect_width")->as_floating_point()->get(),
        table.get("rect_height")->as_floating_point()->get()
    );
    return new QGraphicsEllipseItem(rect);
}

QGraphicsItem* createLineFromTable(const toml::table& table) {
    QLineF line(
        table.get("line_x1")->as_floating_point()->get(),
        table.get("line_y1")->as_floating_point()->get(),
        table.get("line_x2")->as_floating_point()->get(),
        table.get("line_y2")->as_floating_point()->get()
    );
    return new QGraphicsLineItem(line);
}

} // namespace
