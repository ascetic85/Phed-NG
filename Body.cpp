#include <QtOpenGL/QtOpenGL>
#include <QDebug>
#include "Body.h"

#ifndef RAD2DEG
#define RAD2DEG 57.2957795
#endif

int Body::m_count = 0;

Body::Body(QObject *parent)
    : Object(parent)
    , m_body(0)
    , m_breakingPoint(0)
{
    setObjectName(tr("object%1").arg(m_count++));
    m_fixtureDef.density = 1.0;
    m_color = QColor(255,255,255);
}

QColor Body::color() const {
    return m_color;
}

void Body::setColor(const QColor &col) {
    if(col != color()) {
        m_color = col;
        emit propertyChanged();
    }
}

b2Body* Body::body() const {
    return m_body;
}

Point Body::position() const {
    if(m_body) return m_body->GetPosition();
    else return m_bodyDef.position;
}

void Body::setPosition(const Point &pos) {
    if(pos != position()) {
        if(m_body) m_body->SetTransform(pos, m_body->GetAngle());
        else m_bodyDef.position = pos;
        emit propertyChanged();
    }
}

void Body::translate(const Point &d) {
    if(m_body) m_body->SetTransform(m_body->GetPosition() + d, m_body->GetAngle());
    else m_bodyDef.position += d;
    emit propertyChanged();
}

void Body::addPolygon(const BPolygon &poly)
{
    QList<BPolygon> parts = poly.ccw().convexPartition();
    if(m_body) {
        foreach(BPolygon p, parts) {
            b2PolygonShape ps = p;
            m_fixtureDef.shape = &ps; // FIXME: m_fixtureDef might not be up to date...
            m_body->CreateFixture(&m_fixtureDef);
        }
    }
    m_polygons += parts;
}

void Body::addFixture(const Fixture &fixture)
{
    m_fixtures.append(fixture);
    b2FixtureDef fd = fixture;
    m_body->CreateFixture(&fd);
    delete fd.shape;
}

qreal Body::angle() const {
    if(m_body) return m_body->GetAngle();
    else return m_bodyDef.angle;

}

void Body::setAngle(qreal ang) {
    if(ang != angle()) {
        if(m_body) m_body->SetTransform(m_body->GetPosition(), ang);
        else m_bodyDef.angle = ang;
        emit propertyChanged();
    }
}

qreal Body::breakingPoint() const {
    return m_breakingPoint;
}

void Body::setBreakingPoint(qreal bp) {
    if(bp != breakingPoint()) {
        m_breakingPoint = bp;
        emit propertyChanged();
    }
}

void Body::setPolygons(const QList<BPolygon> &polygons)
{
    // TODO: add case with m_body not NULL
    m_polygons = polygons;
}

bool Body::isBreakable() const {
    return m_breakingPoint > 0;
}

QList<BPolygon> Body::polygons() const
{
    return m_polygons;
}

int Body::type() const
{
    return m_bodyDef.type;
}

Point Body::linearVelocity() const
{
    if(m_body) return m_body->GetLinearVelocity();
    else return m_bodyDef.linearVelocity;
}

void Body::setLinearVelocity(const Point& vel)
{
    if(vel != linearVelocity()) {
        if(m_body) m_body->SetLinearVelocity(vel);
        else m_bodyDef.linearVelocity = vel;
        emit propertyChanged();
    }
}

qreal Body::angularVelocity() const
{
    if(m_body) return m_body->GetAngularVelocity();
    else return m_bodyDef.angularVelocity;
}

void Body::setAngularVelocity(qreal vel)
{
    if(vel != angularVelocity()) {
        if(m_body) m_body->SetAngularVelocity(vel);
        else m_bodyDef.angularVelocity = vel;
        emit propertyChanged();
    }
}

qreal Body::angularDamping() const
{
    if(m_body) return m_body->GetAngularDamping();
    else return m_bodyDef.angularDamping;
}

void Body::setAngularDamping(qreal damp)
{
    if(damp != angularDamping()) {
        if(m_body) m_body->SetAngularDamping(damp);
        else m_bodyDef.angularDamping = damp;
        emit propertyChanged();
    }
}

qreal Body::linearDamping() const
{
    if(m_body) return m_body->GetLinearDamping();
    else return m_bodyDef.linearDamping;
}

void Body::setLinearDamping(qreal damp)
{
    if(damp != linearDamping()) {
        if(m_body) m_body->SetLinearDamping(damp);
        else m_bodyDef.linearDamping = damp;
        emit propertyChanged();
    }
}

bool Body::isBullet() const
{
    if(m_body) return m_body->IsBullet();
    else return m_bodyDef.bullet;
}

void Body::setBullet(bool flag)
{
    if(flag != isBullet()) {
        if(m_body) m_body->SetBullet(flag);
        else m_bodyDef.bullet = flag;
        emit propertyChanged();
    }
}

bool Body::isAllowedToSleep() const
{
    if(m_body) return m_body->IsSleepingAllowed();
    else return m_bodyDef.allowSleep;
}

void Body::setAllowedToSleep(bool flag)
{
    if(flag != isAllowedToSleep()) {
        if(m_body) m_body->SetSleepingAllowed(flag);
        else m_bodyDef.allowSleep = flag;
        emit propertyChanged();
    }
}

bool Body::isStatic() const
{
    return m_fixtureDef.density == 0;
}

qreal Body::mass() const
{
    if(m_body) return m_body->GetMass();
    else return 0;
}

qreal Body::inertia() const
{
    if(m_body) return m_body->GetInertia();
    else return 0;
}

bool Body::isSleeping() const
{
    if(m_body) return m_body->IsAwake();
    else return m_bodyDef.awake;
    return true;
}

void Body::setSleeping(bool flag)
{
    if(flag != isSleeping()) {
        if(m_body) {
            m_body->SetAwake(flag);
        } else {
            m_bodyDef.awake = flag;
        }
        emit propertyChanged();
    }
}

bool Body::isSensor() const
{
    if(m_body && m_body->GetFixtureList()) return m_body->GetFixtureList()->IsSensor();
    else return m_fixtureDef.isSensor;
}

void Body::setSensor(bool flag)
{
    if(flag != isSensor()) {
        if(m_body) {
            for(b2Fixture *f = m_body->GetFixtureList(); f; f = f->GetNext()) {
                f->SetSensor(flag);
            }
        } else {
            m_fixtureDef.isSensor = flag;
        }
        emit propertyChanged();
    }
}

qreal Body::density() const
{
    if(m_body && m_body->GetFixtureList()) return m_body->GetFixtureList()->GetDensity();
    else return m_fixtureDef.density;
}

void Body::setDensity(qreal dens)
{
    if(dens != density()) {
        if(dens == 0) setLinearVelocity(b2Vec2(0,0));
        if(m_body && m_body->GetFixtureList()) {
            for(b2Fixture *f = m_body->GetFixtureList(); f; f = f->GetNext()) {
                f->SetDensity(dens);
            }
//            m_body->SetMassFromShapes();
        } else {
            m_fixtureDef.density = dens;
        }
        emit propertyChanged();
    }
}

qreal Body::friction() const
{
    if(m_body && m_body->GetFixtureList()) return m_body->GetFixtureList()->GetFriction();
    else return m_fixtureDef.friction;
}

void Body::setFriction(qreal fric)
{
    if(fric != friction()) {
        if(m_body && m_body->GetFixtureList()) {
            for(b2Fixture *f = m_body->GetFixtureList(); f; f = f->GetNext()) {
                f->SetFriction(fric);
            }
        } else {
            m_fixtureDef.friction = fric;
        }
        emit propertyChanged();
    }
}

qreal Body::restitution() const
{
    if(m_body && m_body->GetFixtureList()) return m_body->GetFixtureList()->GetRestitution();
    else return m_fixtureDef.restitution;
}

void Body::setRestitution(qreal rest)
{
    if(rest != restitution()) {
        if(m_body && m_body->GetFixtureList()) {
            for(b2Fixture *f = m_body->GetFixtureList(); f; f = f->GetNext()) {
                f->SetRestitution(rest);
            }
        } else {
            m_fixtureDef.restitution = rest;
        }
        emit propertyChanged();
    }
}

void Body::paintGL() const
{
    Q_ASSERT(m_body != NULL);
    glPushMatrix();

    const b2Vec2 &pos = m_body->GetPosition();
    glTranslatef(pos.x, pos.y, 0);
    glRotatef(m_body->GetAngle()*RAD2DEG, 0, 0, 1);


    for(b2Fixture *f = m_body->GetFixtureList(); f; f = f->GetNext()) {
        switch(f->GetType()) {
            case b2Shape::e_polygon:
            {
                b2PolygonShape* poly;
                int32 vertexCount;
                poly = static_cast<b2PolygonShape*>(f->GetShape());
                vertexCount = poly->m_vertexCount;

                int alpha = selected() ? sin((m_time.elapsed()%1000)*(M_PI/1000))*255 : 128;
                glColor4ub(m_color.red(), m_color.green(), m_color.blue(), alpha);
                glBegin(GL_POLYGON);
                for(int32 i = 0; i < vertexCount; ++i) {
                    glVertex2f(poly->m_vertices[i].x, poly->m_vertices[i].y);
                }
                glEnd();

                glColor3ub(m_color.red(), m_color.green(), m_color.blue());
                glBegin(GL_LINE_LOOP);
                for(int32 i = 0; i < vertexCount; ++i) {
                    glVertex2f(poly->m_vertices[i].x, poly->m_vertices[i].y);
                }
                glEnd();
                break;
            }
            default:
                Q_ASSERT_X(false, "paintGL", "Unhandled shape type");
                break;
        }
    }

    glPopMatrix();
}

void Body::setType(int type)
{
    if ((type == b2_dynamicBody)
            ||(type == b2_staticBody)
            ||(type == b2_kinematicBody)) {
        if (m_body) {
            m_body->SetType((b2BodyType) type);
        }
        else {
            m_bodyDef.type = (b2BodyType) type;
        }
//        emit propertyChanged();
    }
}
