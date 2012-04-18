/* 
 * File:   ContactListener.h
 * Author: mark
 *
 * Created on September 12, 2009, 5:29 PM
 */

#ifndef _CONTACTLISTENER_H
#define	_CONTACTLISTENER_H

#include <Box2D/Box2D.h>

class ContactListener : public b2ContactListener {
    void BeginContact(b2Contact *contact);
    void EndContact(b2Contact *contact);
    void PreSolve(b2Contact *contact, const b2Manifold *oldManifold);
    void PostSolve(const b2Contact *contact, const b2ContactImpulse *impulse);
};

#endif	/* _CONTACTLISTENER_H */

