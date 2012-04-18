/* 
 * File:   Object.h
 * Author: mark
 *
 * Created on September 20, 2009, 1:56 PM
 */

#ifndef _OBJECT_H
#define	_OBJECT_H

#include <QObject>

class Object : public QObject {
    Q_OBJECT
    friend QDataStream &operator<<(QDataStream&, const Object&);
    friend QDataStream &operator>>(QDataStream&, Object&);
    
public:
    Object(QObject *parent = NULL);
    void touch() const;
    bool selected() const;
    void setSelected(bool);

signals:
    void propertyChanged() const;

private:
    bool m_selected;
};

#endif	/* _OBJECT_H */
