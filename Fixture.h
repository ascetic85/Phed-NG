/* 
 * File:   Fixture.h
 * Author: mark
 *
 * Created on September 21, 2009, 12:42 PM
 */

#ifndef _FIXTURE_H
#define	_FIXTURE_H

#include <Box2D/Dynamics/b2Fixture.h>
#include "Object.h"
#include "Polygon.h"


class Fixture : public Object {
    Q_OBJECT
    Q_PROPERTY(BPolygon polygon READ polygon WRITE setPolygon)
    Q_PROPERTY(qreal friction READ friction WRITE setFriction)
    Q_PROPERTY(qreal restitution READ restitution WRITE setRestitution)
    Q_PROPERTY(qreal density READ density WRITE setDensity)
    Q_PROPERTY(bool isSensor READ isSensor WRITE setSensor)

public:
    Fixture(QObject *parent = NULL);
    Fixture(const Fixture&);
    Fixture& operator=(const Fixture&);
    operator b2FixtureDef() const;

    // READ
    BPolygon polygon() const;
    qreal friction() const;
    qreal restitution() const;
    qreal density() const;
    bool isSensor() const;

    // WRITE
    void setPolygon(const BPolygon&);
    void setFriction(qreal);
    void setRestitution(qreal);
    void setDensity(qreal);
    void setSensor(bool);

private:
    BPolygon m_polygon;
    qreal m_friction;
    qreal m_restitution;
    qreal m_density;
    bool m_isSensor;
};

Q_DECLARE_METATYPE(Fixture)




#endif	/* _FIXTURE_H */

