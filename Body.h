#ifndef BODY_H
#define BODY_H

#include <QObject>
#include <QGraphicsItem>
#include <QTime>
#include <Box2D/Box2D.h>

#include "Object.h"
#include "Polygon.h"
#include "point.h"
#include "Fixture.h"

class World;

class Body : public Object
{
    Q_OBJECT
    Q_PROPERTY(qreal    mass                READ mass               STORED false);
    Q_PROPERTY(qreal    inertia             READ inertia            STORED false);
    Q_PROPERTY(bool     isStatic            READ isStatic           STORED false);
    Q_PROPERTY(bool     isBreakable         READ isBreakable        STORED false);
    Q_PROPERTY(QPointF  position            READ position           WRITE setPosition);
    Q_PROPERTY(QPointF  linearVelocity      READ linearVelocity     WRITE setLinearVelocity);
    Q_PROPERTY(qreal    angle               READ angle              WRITE setAngle);
    Q_PROPERTY(qreal    angularVelocity     READ angularVelocity    WRITE setAngularVelocity);
    Q_PROPERTY(qreal    linearDamping       READ linearDamping      WRITE setLinearDamping);
    Q_PROPERTY(qreal    angularDamping      READ angularDamping     WRITE setAngularDamping);
    Q_PROPERTY(qreal    density             READ density            WRITE setDensity);
    Q_PROPERTY(qreal    friction            READ friction           WRITE setFriction);
    Q_PROPERTY(qreal    restitution         READ restitution        WRITE setRestitution);
    Q_PROPERTY(qreal    breakingPoint       READ breakingPoint      WRITE setBreakingPoint);
    Q_PROPERTY(bool     isBullet            READ isBullet           WRITE setBullet);
    Q_PROPERTY(bool     isAllowedToSleep    READ isAllowedToSleep   WRITE setAllowedToSleep);
    Q_PROPERTY(bool     isSleeping          READ isSleeping         WRITE setSleeping);
    Q_PROPERTY(bool     isSensor            READ isSensor           WRITE setSensor);
    Q_PROPERTY(QColor   color               READ color              WRITE setColor);
    Q_PROPERTY(PolygonList polygons         READ polygons           WRITE setPolygons           DESIGNABLE false);

    friend class World;
public:
    explicit Body(QObject *parent = 0);
    
    // read
    Point position() const;
    qreal angle() const;
    Point linearVelocity() const;
    qreal angularVelocity() const;
    qreal mass() const;
    qreal inertia() const;
    qreal linearDamping() const;
    qreal angularDamping() const;
    bool isBullet() const;
    bool isAllowedToSleep() const;
    bool isSleeping() const;
    bool isStatic() const;
    qreal density() const;
    bool isSensor() const;
    qreal friction() const;
    qreal restitution() const;
    QColor color() const;
    qreal breakingPoint() const;
    bool isBreakable() const;
    QList<BPolygon> polygons() const;

    // write
    void setPosition(const Point &pos);
    void setAngle(qreal angle);
    void setLinearVelocity(const Point &vel);
    void setAngularVelocity(qreal vel);
    void setLinearDamping(qreal damp);
    void setAngularDamping(qreal damp);
    void setBullet(bool flag);
    void setAllowedToSleep(bool flag);
    void setSleeping(bool flag);
    void setDensity(qreal density);
    void setSensor(bool flag);
    void setFriction(qreal fric);
    void setRestitution(qreal rest);
    void setColor(const QColor &poly);
    void setBreakingPoint(qreal bp);
    void setPolygons(const QList<BPolygon> &polygons);
    void clearFixtures();

    // misc
    void paintGL() const;
    void translate(const Point &amount);
    void addPolygon(const BPolygon &poly);
    void addFixture(const Fixture &fixture);

signals:
//    void propertyChanged();

protected:
    b2Body *body() const;

public:
    b2Body *m_body;
    QColor m_color;
    static int m_count;
    qreal m_breakingPoint;
    QTime m_time;
    PolygonList m_polygons;
    QList<Fixture> m_fixtures;

    b2BodyDef m_bodyDef;
    b2FixtureDef m_fixtureDef; // TODO: just make this a QList and scrap m_polygons...
};

#endif // BODY_H
