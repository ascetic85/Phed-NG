/* 
 * File:   Shape.h
 * Author: mark
 *
 * Created on October 16, 2009, 5:09 PM
 */

#ifndef _SHAPE_H
#define	_SHAPE_H

#include "Rect.h"

class Shape {
public:
    virtual Rect boundingRect() = 0;
};

#endif	/* _SHAPE_H */

