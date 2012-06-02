#ifndef ICONFINDER_H
#define ICONFINDER_H

#include <QObject>
#include <QIcon>

class IconFinder : public QObject {
    Q_OBJECT
public:
    IconFinder(const QString &path);
    virtual ~IconFinder();

    virtual QIcon getIcon(const QString &name, int size, const QString &type) const;

    QString getPath() const;
private:

    QString m_path;
};

#endif // ICONFINDER_H
