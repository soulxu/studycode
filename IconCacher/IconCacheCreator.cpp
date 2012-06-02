#include "IconCacheCreator.h"

#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QStringList>
#include <QSet>
#include <QDir>
#include <QDataStream>
#include <QIcon>

#include "IconCache.h"

#include "Debug.h"

#define INDEX_FILE_NAME "index.theme"

IconCacheCreator::IconCacheCreator(const QString &path) : m_path(path) {

}

IconCacheCreator::~IconCacheCreator() {

}

bool IconCacheCreator::createCacheFile(const QString &cachePath, bool force) {
    QFileInfo themePath(m_path);

    if (!(themePath.exists() && themePath.isDir() && themePath.isReadable())) {
        DPRINT("theme path invaild.");
        return false;
    }

    QFile cacheFile(cachePath);

    if (cacheFile.exists()) {
        if (force) {
            cacheFile.remove();
        }
        else {
            DPRINT("cache file existed and can not force.");
            return false;
        }
    }


    if (!cacheFile.open(QIODevice::WriteOnly)) {
        DPRINT("can not open cache file: %s", qPrintable(cachePath));
        return false;
    }

    QFile indexFile(m_path + "/" + INDEX_FILE_NAME);

    if (!indexFile.open(QIODevice::ReadOnly)) {
        DPRINT("the index file of theme can not open.");
        return false;
    }

    QList<DirEntry *> dirEntryList;
    QSet<int> size;
    QSet<QString> cates;

    this->loadIndex(indexFile, dirEntryList, size, cates);

    QHash<QString, qint64> iconList;

    QStringList filters;
    filters.append("*.png");
    filters.append("*.xpm");
    filters.append("*.svg");

    QDataStream out(&cacheFile);
    out.setByteOrder(QDataStream::LittleEndian);
    QString keystr("%1-%2-%3");
    QString key;

    struct IconCache cache;

    out.writeRawData((const char *)&cache, sizeof(struct IconCache));

    cache.sizeHdr.num = size.size();
    cache.sizeHdr.sizes = out.device()->pos();

    this->writeSizeToCache(out, size.toList());

    cache.cateHdr.num = cates.size();
    cache.cateHdr.cates = cacheFile.pos();

    this->writeCatesToCache(out, cates.toList());

    for (int i = 0; i < dirEntryList.size(); i++) {
        if (dirEntryList.at(i) == NULL) {
            continue;
        }

        QDir dir(m_path);

        if (!dir.cd(dirEntryList.at(i)->path)) {
            DWARNING("theme subdir can not enter: %s", qPrintable(dirEntryList.at(i)->path));
            continue;
        }

        DPRINT("Dir in: %s", qPrintable(dir.canonicalPath()));
        QFileInfoList files = dir.entryInfoList(filters);

        for (int j = 0; j < files.size(); j++) {
            QFileInfo f = files.at(j);
            key = keystr.arg(QString::number(dirEntryList.at(i)->size), dirEntryList.at(i)->type, f.fileName());
            qint64 iconOffset = cacheFile.pos();

            if (!this->writeIconToCache(out, f)) {
                continue;
            }

            DPRINT("key: %s,%d", qPrintable(key), iconOffset);
            iconList.insert(key, iconOffset);
        }
    }

    DPRINT("Finished write icon data.");
    DPRINT("iconList: %d", iconList.size());
    cache.hashHdr.num = iconList.size();

    writeHashToCache(out, iconList, &(cache.hashHdr.data));

    DPRINT("Finished write hash data.");

    cacheFile.seek(0);
    DPRINT("%lld", cacheFile.size());
    out.writeRawData((const char *)&cache, sizeof(struct IconCache));
    DPRINT("%lld", cacheFile.size());

    if (out.byteOrder() == QDataStream::BigEndian) {
        DPRINT("big endian");
    }
    cacheFile.close();
    DPRINT("sizeof iconcahce: %d", sizeof(struct IconCache));
    DPRINT("Finished write head.");

    for (int i = 0; i < dirEntryList.size(); i++) {
        delete dirEntryList.at(i);
    }

    return true;
}

bool IconCacheCreator::writeHashToCache(QDataStream &out, const QHash<QString, qint64> &hash, qint64 *ret) {
    QList<QString> keys = hash.keys();
    struct HashData *data = new HashData[keys.size()];
    DPRINT("keys size: %d", keys.size());

    for (int i = 0; i < keys.size(); i++) {
        data[i].key = out.device()->pos();
        out.writeRawData(qPrintable(keys.at(i)), keys.at(i).size() + 1);
        data[i].value = hash.value(keys.at(i), -1);
        DPRINT("value: %d", data[i].value);
    }

    *ret = out.device()->pos();

    for (int i = 0; i < keys.size(); i++) {
        DPRINT("hash value: %lld, %lld - %d", data[i].key, data[i].value, i);
        out.writeRawData((const char *)&(data[i].key), sizeof(qint64));
        out.writeRawData((const char *)&(data[i].value), sizeof(qint64));
    }

    delete[] data;
    return true;
}


bool IconCacheCreator::writeCatesToCache(QDataStream &out, const QList<QString> &cates) {
    for (int i = 0; i < cates.size(); i++) {
        //out << qPrintable(cates.at(i));
        out.writeRawData(qPrintable(cates.at(i)), cates.at(i).size() + 1);
    }

    return true;
}

bool IconCacheCreator::writeSizeToCache(QDataStream &out, const QList<int> &sizes) {
    for (int i = 0; i < sizes.size(); i++) {
        //out << sizes.at(i);
        DPRINT("size: %d", out.device()->size());
        out.writeRawData((const char *)&(sizes.at(i)), sizeof(int));
        DPRINT("size: %d", out.device()->size());
    }

    return true;
}

bool IconCacheCreator::writeIconToCache(QDataStream &out, const QFileInfo &fileInfo) {
    QFile in(fileInfo.absoluteFilePath());

    if (!in.open(QIODevice::ReadOnly)) {
        return false;
    }

    char buf[4096];

    QDataStream inStream(&in);

    qint64 size = in.size();
    out.writeRawData((const char *)&size, sizeof(qint64));

    while (!inStream.atEnd()) {
        out.writeRawData(buf, inStream.readRawData(buf, 4096));
    }

    in.close();

    //QPixmap pixmap(f.absoluteFilePath());
    //out << pixmap;
    //out << null;
    //QIcon iconFile(f.absoluteFilePath());
    //out << iconFile;
    //out << null;
    //DPRINT("cache icon: %s", qPrintable(f.absoluteFilePath()));
    return true;
}

void IconCacheCreator::loadIndex(QFile &indexFile, QList<DirEntry *> &iconList, QSet<int> &size, QSet<QString> &cates) {
    QTextStream in(&indexFile);
    struct DirEntry *entry = NULL;

    while (!in.atEnd()) {
        QString line = in.readLine();

        if (line == "[Icon Theme]") {

        }
        else if (line.startsWith('[') and line.endsWith(']')) {
            if (entry != NULL) {
                iconList.append(entry);
            }

            entry = new DirEntry;
            entry->path = line.rightRef(line.size() - 1).toString().leftRef(line.size() - 2).toString();
        }
        else if (line.startsWith("Size", Qt::CaseSensitive)) {
            if (entry == NULL) {
                continue;
            }

            size.insert(line.section('=', 1, 1).toInt());
            entry->size = line.section('=', 1, 1).toInt();
        }
        else if (line.startsWith("Context", Qt::CaseSensitive)) {
            if (entry == NULL) {
                continue;
            }

            cates.insert(line.section('=', 1, 1));
            entry->cate = line.section('=', 1, 1);
        }
        else if (line.startsWith("Type", Qt::CaseInsensitive)) {
            if (entry == NULL) {
                continue;
            }

            entry->type = line.section('=', 1, 1);
        }
    }
}
