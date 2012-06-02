#ifndef ICONTHEME_H
#define ICONTHEME_H

#include <QObject>
#include <QIcon>
#include <QHash>

class IconFinder;

class IconTheme : public QObject {
    Q_OBJECT
public:
    static IconTheme *getTheme(const QString &name);

    QIcon getIcon(const QString &name, int size, const QString &type) const;

    virtual ~IconTheme();

protected:
    IconTheme(const QString &name, IconFinder *finder);

private:
    QIcon getIconHelper(const QString &name, int size, const QString &type) const;
    QIcon getIconFromStuff(const QString &name, int size, const QString &type) const;

private:
    static QHash<QString, IconTheme *> themes;

    QString m_name;
    QList<IconTheme *> m_parent;
    IconFinder *m_finder;
};

#endif // ICONTHEME_H
