#ifndef ICONCACHE_H
#define ICONCACHE_H

#include <QtGlobal>

struct SizeHdr {
    int num;
    qint64 sizes;
};

struct CateHdr {
    int num;
    qint64 cates;
};

struct IconData {
    int size;
    qint64 data;
};

struct HashData {
    qint64 key;
    qint64 value;
};

struct HashHdr {
    int num;
    qint64 data;
};



struct IconCache {
    struct SizeHdr sizeHdr;
    struct CateHdr cateHdr;
    struct HashHdr hashHdr;
};

#endif // ICONCACHE_H
