#ifndef CANVAS_LOADER_HPP
#define CANVAS_LOADER_HPP

#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QString>
#include <QList>

#include <toml++/toml.hpp>

class Canvas;

class CanvasLoader {
public:
    static void saveToToml(Canvas* canvas, const QString& fileName);
    static void loadFromToml(Canvas* canvas, const QString& fileName);

private:
    // Функции преобразования элементов в TOML таблицы
    static toml::table rectToTable(QGraphicsRectItem* item);
    static toml::table ellipseToTable(QGraphicsEllipseItem* item);
    static toml::table lineToTable(QGraphicsLineItem* item);
    static toml::table itemToTable(QGraphicsItem* item);

    static void saveShapeProperties(QAbstractGraphicsShapeItem* item, toml::table& table);
    static void saveLineProperties(QGraphicsLineItem* item, toml::table& table);
    static void savePenProperties(const QPen& pen, toml::table& table);

    static QGraphicsItem* createItemFromTable(const toml::table& table);
    static void restoreStackingOrder(const QList<QGraphicsItem*>& items);
};

#endif // CANVAS_LOADER_HPP
