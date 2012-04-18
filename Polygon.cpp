/*
 * File:   Polygon.cpp
 * Author: mark
 *
 * Created on August 26, 2009, 1:07 PM
 */

#include <algorithm>
#include <limits>
#include <QLine>
#include <QVarLengthArray>
#include <Box2D/Box2D.h>
#include <qmath.h>

#include "Polygon.h"
#include "Point.h"
#include "Circle.h"

BPolygon::BPolygon(): QPolygonF() {
}

BPolygon::BPolygon(int size): QPolygonF(size) {
}

BPolygon::BPolygon(const QPolygonF & polygon): QPolygonF(polygon) {
    if(size() > 3 && first() == last()) pop_back();
}

BPolygon::BPolygon(const QVector<QPointF> & points): QPolygonF(points) {
    if(size() > 3 && first() == last()) pop_back();
}

BPolygon::BPolygon(const Rect& rect) {
    reserve(4);
    append(rect.topLeft());
    append(rect.topRight());
    append(rect.bottomRight());
    append(rect.bottomLeft());
}

BPolygon::BPolygon(const QPolygon & polygon): QPolygonF(polygon) {
    if(size() > 3 && first() == last()) pop_back();
}

BPolygon::BPolygon(const b2PolygonShape& polygon) {
    reserve(polygon.GetVertexCount());
    for(int i = 0; i < polygon.GetVertexCount(); ++i) {
        append((Point) polygon.GetVertex(i));
    }
}

BPolygon::BPolygon(const Circle& circle, int points) {
    if(points <= 0) points = qRound(circle.radius() * 15);
    if(points < 3) points = 3;
    qreal max = 2 * M_PI;
    qreal inc = max / points;
    reserve(points);
    for(qreal d = 0; d < max; d += inc) {
        prepend(Point(cos(d) * circle.radius() + circle.center().x(),
                sin(d) * circle.radius() + circle.center().y()));
    }
}

const QPointF& BPolygon::at(int i) const {
    const int s = size();
    return(*this)[i < 0 ? s - (-i % s) : i % s];
}

bool BPolygon::isCW() const {
    int br = 0;
    for(int i = 1; i < size(); ++i) {
        if((*this)[i].y() < (*this)[br].y() || ((*this)[i].y() == (*this)[br].y() && (*this)[i].x() > (*this)[br].x())) {
            br = i;
        }
    }
    return right(br);
}

BPolygon BPolygon::ccw() const {
    BPolygon ccw(size());
    if(isCW()) std::reverse_copy(begin(), end(), ccw.begin());
    else std::copy(begin(), end(), ccw.begin());
    return ccw;
}

BPolygon BPolygon::copy(int i, int j) const {
    BPolygon p;
    while(j < i) j += size();
    p.reserve(j - i + 1);
    for(; i <= j; ++i) {
        p.append(at(i));
    }
    return p;
}

bool BPolygon::isConvex() const { // precondition: ccw
    for(int i = 0; i < size(); ++i) {
        if(right(i)) return false;
    }
    return true;
}

QList<BPolygon> BPolygon::convexPartition() const { // precondition: ccw; see mnbayazit.com/406/bayazit for details about how this works
    QList<BPolygon> list;
    qreal d, dist1, dist2;
    QPointF ip, ip1, ip2; // intersection points
    int ind1, ind2;
    BPolygon poly1, poly2;

    for(int i = 0; i < size(); ++i) {
        if(reflex(i)) {
            dist1 = dist2 = std::numeric_limits<qreal>::max();
            for(int j = 0; j < size(); ++j) {
                if(left(at(i - 1), at(i), at(j)) && rightOn(at(i - 1), at(i), at(j - 1))) { // if ray (i-1)->(i) intersects with edge (j, j-1)
                    QLineF(at(i - 1), at(i)).intersect(QLineF(at(j), at(j - 1)), &ip);
                    if(right(at(i + 1), at(i), ip)) { // intersection point isn't caused by backwards ray
                        d = sqdist(at(i), ip);
                        if(d < dist1) { // take the closest intersection so we know it isn't blocked by another edge
                            dist1 = d;
                            ind1 = j;
                            ip1 = ip;
                        }
                    }
                }
                if(left(at(i + 1), at(i), at(j + 1)) && rightOn(at(i + 1), at(i), at(j))) { // if ray (i+1)->(i) intersects with edge (j+1, j)
                    QLineF(at(i + 1), at(i)).intersect(QLineF(at(j), at(j + 1)), &ip);
                    if(left(at(i - 1), at(i), ip)) {
                        d = sqdist(at(i), ip);
                        if(d < dist2) {
                            dist2 = d;
                            ind2 = j;
                            ip2 = ip;
                        }
                    }
                }
            }
            if(ind1 == (ind2 + 1) % size()) { // no vertices in range
                QPointF sp((ip1 + ip2) / 2);
                poly1 = copy(i, ind2);
                poly1.append(sp);
                poly2 = copy(ind1, i);
                poly2.append(sp);
            } else {
                double highestScore = 0, bestIndex = ind1, score;
                while(ind2 < ind1) ind2 += size();
                for(int j = ind1; j <= ind2; ++j) {
                    if(canSee(i, j)) {
                        score = 1 / (sqdist(at(i), at(j)) + 1);
                        if(reflex(j)) {
                            if(rightOn(at(j - 1), at(j), at(i)) && leftOn(at(j + 1), at(j), at(i))) {
                                score += 3;
                            } else {
                                score += 2;
                            }
                        } else {
                            score += 1;
                        }
                        if(score > highestScore) {
                            bestIndex = j;
                            highestScore = score;
                        }
                    }
                }
                poly1 = copy(i, bestIndex);
                poly2 = copy(bestIndex, i);
            }
            list += poly1.convexPartition();
            list += poly2.convexPartition();
            return list;
        }
    }
    // polygon is already convex
    if(size() > b2_maxPolygonVertices) {
        poly1 = copy(0, size() / 2);
        poly2 = copy(size() / 2, 0);
        list += poly1.convexPartition();
        list += poly2.convexPartition();
    } else list.append(*this);
    return list;
}

bool BPolygon::canSee(int i, int j) const {
    if(reflex(i)) {
        if(leftOn(at(i), at(i - 1), at(j)) && rightOn(at(i), at(i + 1), at(j))) return false;
    } else {
        if(rightOn(at(i), at(i + 1), at(j)) || leftOn(at(i), at(i - 1), at(j))) return false;
    }
    if(reflex(j)) {
        if(leftOn(at(j), at(j - 1), at(i)) && rightOn(at(j), at(j + 1), at(i))) return false;
    } else {
        if(rightOn(at(j), at(j + 1), at(i)) || leftOn(at(j), at(j - 1), at(i))) return false;
    }
    for(int k = 0; k < size(); ++k) {
        if((k + 1) % size() == i || k == i || (k + 1) % size() == j || k == j) {
            continue; // ignore incident edges
        }
        if(QLineF(at(i), at(j)).intersect(QLineF(at(k), at(k + 1)), NULL) == QLineF::BoundedIntersection) {
            return false;
        }
    }
    return true;
}

bool BPolygon::reflex(int i) const { // precondition: ccw
    return right(i);
}

bool BPolygon::left(int i) const {
    return left(at(i - 1), at(i), at(i + 1));
}

bool BPolygon::leftOn(int i) const {
    return leftOn(at(i - 1), at(i), at(i + 1));
}

bool BPolygon::right(int i) const {
    return right(at(i - 1), at(i), at(i + 1));
}

bool BPolygon::rightOn(int i) const {
    return rightOn(at(i - 1), at(i), at(i + 1));
}

bool BPolygon::collinear(int i) const {
    return collinear(at(i - 1), at(i), at(i + 1));
}

qreal BPolygon::area(const QPointF &a, const QPointF &b, const QPointF &c) {
    return((b.x() - a.x())*(c.y() - a.y()))-((c.x() - a.x())*(b.y() - a.y()));
}

bool BPolygon::left(const QPointF &a, const QPointF &b, const QPointF &c) {
    return area(a, b, c) > 0;
}

bool BPolygon::leftOn(const QPointF &a, const QPointF &b, const QPointF &c) {
    return area(a, b, c) >= 0;
}

bool BPolygon::right(const QPointF &a, const QPointF &b, const QPointF &c) {
    return area(a, b, c) < 0;
}

bool BPolygon::rightOn(const QPointF &a, const QPointF &b, const QPointF &c) {
    return area(a, b, c) <= 0;
}

bool BPolygon::collinear(const QPointF &a, const QPointF &b, const QPointF &c) {
    return area(a, b, c) == 0;
}

qreal BPolygon::sqdist(const QPointF &a, const QPointF &b) {
    qreal dx = b.x() - a.x();
    qreal dy = b.y() - a.y();
    return dx * dx + dy * dy;
}

qreal BPolygon::area() const {
    qreal a = 0;
    int j = size() - 1;
    for(int i = 1; i < j; ++i) {
        a += area((*this)[0], (*this)[i], (*this)[i+1]);
    }
    return a;
}

BPolygon::operator b2PolygonShape() const {
    QVarLengthArray<b2Vec2> arr(size());
    for(int i = 0; i < size(); ++i) {
        arr[i] = (Point) (*this)[i];
    }
    b2PolygonShape ps;
    ps.Set(arr.data(), arr.size());
    return ps;
}

QDataStream &operator<<(QDataStream& ds, const PolygonList& pl) {
    ds << pl.size();
    foreach(BPolygon p, pl) {
        ds << p;
    }
    return ds;
}

QDataStream &operator>>(QDataStream& ds, PolygonList& pl) {
    int s;
    BPolygon p;
    ds >> s;
    for(int i = 0; i < s; ++i) {
        ds >> p;
        pl.append(p);
    }
    return ds;
}
