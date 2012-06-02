#ifndef ICONCACHECREATOR_H
#define ICONCACHECREATOR_H

#include <QObject>
#include <QFile>
#include <QStringList>
#include <QSet>
#include <QFileInfo>
#include <QDataStream>

#define CACHE_FILE_NAME "icons.cache"

struct DirEntry {
    QString path;
    int size;
    QString cate;
    QString type;
};

class IconCacheCreator : public QObject {
    Q_OBJECT
public:
    IconCacheCreator(const QString &path);
    ~IconCacheCreator();

    bool createCacheFile(const QString &cachePath, bool force);

private:
    void loadIndex(QFile &indexFile, QList<DirEntry *> &iconList, QSet<int> &size, QSet<QString> &cates);
    bool writeIconToCache(QDataStream &out, const QFileInfo &fileInfo);
    bool writeSizeToCache(QDataStream &out, const QList<int> &sizes);
    bool writeCatesToCache(QDataStream &out, const QList<QString> &cates);
    bool writeHashToCache(QDataStream &out, const QHash<QString, qint64> &hash, qint64 *ret);

private:
    QString m_path;
};

#endif // ICONCACHECREATOR_H
