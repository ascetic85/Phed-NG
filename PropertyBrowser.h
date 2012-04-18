/* 
 * File:   PropertyBrowser.h
 * Author: mark
 *
 * Created on August 23, 2009, 10:29 PM
 */

#ifndef _PROPERTYBROWSER_H
#define	_PROPERTYBROWSER_H

#include <QtPropertyBrowser/QtTreePropertyBrowser>
#include <QtPropertyBrowser/QtVariantPropertyManager>
#include "Object.h"

class PropertyBrowser : public QtTreePropertyBrowser {
    Q_OBJECT
public:
    PropertyBrowser(QWidget *parent = NULL);
    void setSelectedObjects(const QList<Object*> objs);

private slots:
    void valueChanged(QtProperty *property, const QVariant &value);
    void objectUpdated();

private:
    QString humanize(QString str) const;
    QtVariantPropertyManager *m_variantManager;
    QMap<QtProperty*, QByteArray> m_propertyMap;
    QList<Object*> m_selectedObjects;

    QtVariantEditorFactory *m_variantEditorFactory;
    QHash<QByteArray/*class*/, QtVariantPropertyManager*> m_classManager;
    QHash<QByteArray/*class*/, QHash<QByteArray/*propetyName*/, QtProperty*> > m_classProperties;
};

#endif	/* _PROPERTYBROWSER_H */

