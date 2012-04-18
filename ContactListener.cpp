/* 
 * File:   ContactListener.cpp
 * Author: mark
 * 
 * Created on September 12, 2009, 5:29 PM
 */

#include <QObject>
#include "ContactListener.h"

void ContactListener::BeginContact(b2Contact* contact) {
    Q_UNUSED(contact);
}

void ContactListener::EndContact(b2Contact* contact) {
    Q_UNUSED(contact);
}

void ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {
    Q_UNUSED(contact);
    Q_UNUSED(oldManifold);
}

void ContactListener::PostSolve(const b2Contact* contact, const b2ContactImpulse* impulse) {
    Q_UNUSED(contact);
    Q_UNUSED(impulse);
}

