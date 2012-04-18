/* 
 * File:   Circle.cpp
 * Author: mark
 * 
 * Created on September 13, 2009, 5:16 PM
 */

#include "Circle.h"

Circle::Circle(Point p, qreal r) : m_center(p), m_radius(r) {}
Circle::Circle(const b2CircleShape& circleShape) : m_center(circleShape.m_p), m_radius(circleShape.m_radius) {}

Point Circle::center() const {
    return m_center;
}

qreal Circle::radius() const {
    return m_radius;
}

void Circle::setCenter(const Point& p) {
    m_center = p;
}

void Circle::setRadius(qreal r) {
    m_radius = r;
}

Circle::operator b2CircleShape() const {
    b2CircleShape cs;
    cs.m_p = m_center;
    cs.m_radius = m_radius;
    return cs;
}