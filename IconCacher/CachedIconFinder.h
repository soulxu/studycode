#ifndef CACHEDICONFINDER_H
#define CACHEDICONFINDER_H

#include "IconFinder.h"

#include <QHash>

class CachedIconFinder : public IconFinder {
    Q_OBJECT
public:
    CachedIconFinder(const QString &path);
    virtual ~CachedIconFinder();

    virtual QIcon getIcon(const QString &name, int size, const QString &type) const;
private:
    void loadCache(const QString &path);

private:
    int m_fd;
    char *m_addr;
    QList<int> m_sizes;
    QList<QString> m_cates;
    QHash<QString, qint64> m_hash;
};

#endif // CACHEDICONFINDER_H
