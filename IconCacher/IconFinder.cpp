#include "IconFinder.h"

IconFinder::IconFinder(const QString &path) : m_path(path) {

}

IconFinder::~IconFinder() {

}

QIcon IconFinder::getIcon(const QString &name, int size, const QString &type) const {
    return QIcon();
}

QString IconFinder::getPath() const {
    return m_path;
}


