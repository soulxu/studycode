#include "GenericIconFinder.h"

GenericIconFinder::GenericIconFinder(const QString &path) : IconFinder(path) {

}

GenericIconFinder::~GenericIconFinder() {

}

QIcon GenericIconFinder::getIcon(const QString &name, int size, const QString &type) const {
    return QIcon();
}
