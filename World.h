/*
 * 
 * File:   Object.cpp
 * Author: mark
 * 
 * Created on August 19, 2009, 7:10 PM
 *
 *
 * Copyright (c) 2012 ascetic85 
 */

#ifndef WORLD_H
#define WORLD_H

#include <QSet>
#include <QTimer>
#include <Box2D/Box2D.h>

#include "Object.h"
#include "point.h"
#include "Polygon.h"

class Body;

struct Contact {
    Point lp; // local point
    Point wp; // world point
    Point n; // normal
    b2Fixture *f; // fixture
    qreal I; // impulse magnitude
    Point lv; // linear velocity
    qreal av; // angular velocity
};

class World : public Object, b2QueryCallback, b2ContactListener
{
    Q_OBJECT
    Q_PROPERTY(QPointF gravity  READ gravity    WRITE setGravity);

public:
    World(const QPointF &gravity = QPointF(0, -9.80665), bool doSleep = true, QObject *parent = 0);

    // read
    QPointF gravity() const;
    bool simulating();
    b2MouseJoint *mouseJoint();

    // write
    void setGravity(const QPointF&);
    void setSimulating(bool);

    // misc
    void addBody(Body*);
    void removeObject(Body*);
    const QList<Body*>& bodies() const;
    const QList<Object*>& selectedObjects() const;
    void setSelectedObjects(const QSet<Body*>&);
    const QSet<Body*>& query(const Point& point, int maxResults = 1);
    const QSet<Body*>& query(const BPolygon& poly, int maxResults = 0);
    b2Body* groundBody() const;

    void addMouseJoint(Body*, const Point &p); // FIXME: should be a list of bodies, or abstracted to general joint
    void destroyMouseJoint();
    void updateMouseJoint(const Point &p);

    void reset();

protected:
    bool ReportFixture(b2Fixture *f);
    void BeginContact(b2Contact *contact);
    void EndContact(b2Contact *contact);
    void PreSolve(b2Contact *contact, const b2Manifold *oldManifold);
    void PostSolve(const b2Contact *contact, const b2ContactImpulse *impulse);


signals:
    void objectsSelected(const QList<Object*>&);

protected slots:
    void simStep();

private:
    b2World m_world;
    b2Body *m_groundBody;
    QList<Body*> m_bodies;
    QList<Object*> m_selectedObjects;
    QSet<Body*> m_queryResult;
    QTimer m_physTimer;
    int m_physFPS;
    int m_queryResultsLimit;
    BPolygon m_queryPoly;
    b2MouseJoint *m_mouseJoint;

    int m_manifoldPointCount;
    b2Fixture *m_fixtureA;
    b2Fixture *m_fixtureB;
    Body *m_objA;
    Body *m_objB;
    QList<Contact> m_contacts;
    b2Vec2 m_lv1, m_lv2;
    qreal m_av1, m_av2;
};

#endif // WORLD_H
