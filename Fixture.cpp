/* 
 * File:   Fixture.cpp
 * Author: mark
 * 
 * Created on September 21, 2009, 12:42 PM
 */

#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include "Fixture.h"


Fixture::Fixture(QObject *parent) : Object(parent) {
    m_polygon       = BPolygon();
    m_friction      = 0.20;
    m_restitution   = 0.10;
    m_density       = 1.00;
    m_isSensor      = false;
}

Fixture::Fixture(const Fixture& f) : 
        Object(this), m_polygon(f.m_polygon), m_friction(f.m_friction),
        m_restitution(f.m_restitution), m_density(f.m_density),
        m_isSensor(f.m_isSensor)
{}

Fixture& Fixture::operator=(const Fixture &f) {
    m_polygon       = f.m_polygon;
    m_friction      = f.m_friction;
    m_restitution   = f.m_restitution;
    m_density       = f.m_density;
    m_isSensor      = f.m_isSensor;
    return *this;
}

// READ
BPolygon Fixture::polygon() const {
    return m_polygon;
}
qreal Fixture::friction() const {
    return m_friction;
}
qreal Fixture::restitution() const {
    return m_restitution;
}
qreal Fixture::density() const {
    return m_density;
}
bool Fixture::isSensor() const {
    return m_isSensor;
}

// WRITE
void Fixture::setPolygon(const BPolygon& val) {
    m_polygon = val;
}
void Fixture::setFriction(qreal val) {
    m_friction = val;
}
void Fixture::setRestitution(qreal val) {
    m_restitution = val;
}
void Fixture::setDensity(qreal val) {
    m_density = val;
}
void Fixture::setSensor(bool val) {
    m_isSensor = val;
}

Fixture::operator b2FixtureDef() const {
    b2FixtureDef fd;
    fd.density = m_density;
    fd.friction = m_friction;
    fd.isSensor = m_isSensor;
    fd.restitution = m_restitution;
    fd.shape = new b2PolygonShape(m_polygon);
    return fd;
}
