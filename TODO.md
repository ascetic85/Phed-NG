TODO:
======
Merge [b2djson](http://www.iforce2d.net/b2djson/), save / load data

Bugs:
======

 - Body.cpp:72: // FIXME: m_fixtureDef might not be up to date...
 - PropertyBrowser.cpp:53: // FIXME: this loop takes ~250 ms for 18 properties
 - PropertyBrowser.cpp:77: // FIXME: should be looping over object's properties, not property map
 - World.cpp:94: // FIXME: causes crashes (or leaks without deleting the obj??)
 - World.h:62: // FIXME: should be a list of bodies, or abstracted to general joint
