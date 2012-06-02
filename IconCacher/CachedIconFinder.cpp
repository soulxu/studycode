#include "CachedIconFinder.h"

#include <QDir>
#include <QProcess>
#include <QString>
#include <QStringList>
#include <QFile>

#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#include "IconCache.h"

#include <Debug.h>

CachedIconFinder::CachedIconFinder(const QString &path) : IconFinder(path) {
    QDir dir(path);

    QStringList envs = QProcess::systemEnvironment();
    QString home;

    for (int i = 0; i < envs.size(); i++) {
            if (envs.at(i).section('=', 0, 0) == "HOME") {
                DPRINT("home: %s", qPrintable(envs.at(i)));
                home = envs.at(i).section('=', 1, 1);
            }
    }

    DPRINT("home var: %s", qPrintable(home));
    QString localPath = home + "/.local/share/icons/" + dir.dirName() + "/icon.cache";


    this->loadCache(localPath);
}

CachedIconFinder::~CachedIconFinder() {

}

QIcon CachedIconFinder::getIcon(const QString &name, int size, const QString &type) const {
    QString tmp("%1-%2-%3");
    QString key = tmp.arg(QString::number(size), type, name);

    DPRINT("%s", qPrintable(key));
    if (this->m_hash.contains(key)) {
        QPixmap pixmap;

        if (!pixmap.loadFromData((const uchar *)(this->m_hash.value(key) + m_addr + sizeof(qint64)), *(qint64 *)(this->m_hash.value(key) + m_addr))) {
            DPRINT("can not load pixmap");
            return QIcon();
        }

        DPRINT("get icon.");
        return QIcon(pixmap);
    }

    DPRINT("non-exists");
    return QIcon();
}

void CachedIconFinder::loadCache(const QString &path) {
    DPRINT("cache path: %s", qPrintable(path));

    m_fd = open(qPrintable(path), O_RDONLY);

    if (m_fd < 0) {
        DPRINT("can not open file.");
        return;
    }

    struct stat buf;

    if (fstat(m_fd, &buf) != 0) {
        DPRINT("can not stat file.");
        return;
    }

    m_addr = (char *)mmap(NULL, buf.st_size, PROT_READ, MAP_PRIVATE, m_fd, 0);

    if (m_addr == MAP_FAILED) {
        DPRINT("can not map file to memory.");
        return;
    }

    struct IconCache *cache = (struct IconCache *)m_addr;
    DPRINT("size num: %d, %d", cache->sizeHdr.num, cache->sizeHdr.sizes);

    for (int i = 0; i < cache->sizeHdr.num; i++) {
        int n = ((int *)(m_addr + cache->sizeHdr.sizes))[i];
        m_sizes.append(n);
        DPRINT("size: %d", n);
    }

    char *c = (char *)(m_addr + cache->cateHdr.cates);

    for (int i = 0; i < cache->cateHdr.num; i++) {
        QString str(c);
        m_cates.append(str);
        c += str.size() + 1;
    }


    struct HashData *data = (struct HashData *)(m_addr + cache->hashHdr.data);

    for (int i = 0; i < cache->hashHdr.num; i++) {
        DPRINT("%s, %d", qPrintable(QString(m_addr + data->key)), data->value);
        m_hash.insert(QString(m_addr + data->key), data->value);
        data++;
    }

}
