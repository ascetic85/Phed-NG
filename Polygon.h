#ifndef POLYGON_H
#define POLYGON_H

#include <QPolygonF>
#include <QMetaType>

#include "Circle.h"
#include "Rect.h"

class BPolygon : public QPolygonF {
public:
    BPolygon();
    BPolygon(int size);
    BPolygon(const QPolygonF & polygon);
    BPolygon(const QVector<QPointF> & points);
    BPolygon(const Rect & rect);
    BPolygon(const QPolygon & polygon);
    BPolygon(const b2PolygonShape & polygon);
    BPolygon(const Circle &circle, int points = 0);
    const QPointF& at(int i) const;
    BPolygon ccw() const;
    BPolygon copy(int i, int j) const;
    bool isCW() const;
    bool canSee(int i, int j) const;
    bool isConvex() const;
    bool left(int i) const;
    bool leftOn(int i) const;
    bool right(int i) const;
    bool rightOn(int i) const;
    bool collinear(int i) const;
    bool reflex(int i) const;
    qreal area() const;
    QList<BPolygon> convexPartition() const;
    static bool left(const QPointF &a, const QPointF &b, const QPointF &c);
    static bool leftOn(const QPointF &a, const QPointF &b, const QPointF &c);
    static bool right(const QPointF &a, const QPointF &b, const QPointF &c);
    static bool rightOn(const QPointF &a, const QPointF &b, const QPointF &c);
    static bool collinear(const QPointF &a, const QPointF &b, const QPointF &c);
    static qreal area(const QPointF &a, const QPointF &b, const QPointF &c);
    static qreal sqdist(const QPointF &a, const QPointF &b);
    operator b2PolygonShape() const;
};

typedef QList<BPolygon> PolygonList;

QDataStream &operator<<(QDataStream&, const PolygonList&);
QDataStream &operator>>(QDataStream&, PolygonList&);

Q_DECLARE_METATYPE(BPolygon)
Q_DECLARE_METATYPE(PolygonList)

#endif // POLYGON_H
