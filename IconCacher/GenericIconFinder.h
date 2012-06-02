#ifndef GENERICICONFINDER_H
#define GENERICICONFINDER_H

#include <QObject>

#include "IconFinder.h"

class GenericIconFinder : public IconFinder {
    Q_OBJECT
public:
    GenericIconFinder(const QString &path);
    ~GenericIconFinder();

    virtual QIcon getIcon(const QString &name, int size, const QString &type) const;
private:

};


#endif // GENERICICONFINDER_H
