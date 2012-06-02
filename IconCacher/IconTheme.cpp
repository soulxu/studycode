#include "IconTheme.h"

#include <QProcess>
#include <QStringList>
#include <QFile>
#include <QTextStream>

#include "IconFinder.h"
#include "CachedIconFinder.h"
#include "GenericIconFinder.h"

QHash<QString, IconTheme *> IconTheme::themes;

IconTheme::IconTheme(const QString &name, IconFinder *finder) : m_name(name), m_finder(finder) {
    QString themePath = "/usr/share/icons/" + name + "/index.theme";

    QFile index(themePath);

    if (index.open(QIODevice::ReadOnly)) {
        QTextStream in(&index);

        while (!in.atEnd()) {
            QString line = in.readLine();

            if (line.startsWith("Inherits=")) {
                QString s = line.section('=', 1, 1);
                QStringList list = s.split(',');

                for (int i = 0; i < list.size(); i++) {
                    IconTheme *theme = IconTheme::getTheme(list.at(i));

                    if (theme != NULL) {
                        if (!this->m_parent.contains(theme)) {
                            this->m_parent.append(theme);
                        }
                    }
                }
            }
        }

        index.close();
    }

}

IconTheme::~IconTheme() {
    delete this->m_finder;
}


IconTheme *IconTheme::getTheme(const QString &name) {
    IconTheme *ret = NULL;

    if ((ret = IconTheme::themes.value(name, NULL)) != NULL) {
        return ret;
    }

    QString themePath = "/usr/share/icons/" + name;

    if (!QFile::exists(themePath + "/index.theme")) {
        return NULL;
    }

    QStringList envs = QProcess::systemEnvironment();
    QString home;

    for (int i = 0; i < envs.size(); i++) {
        if (envs.at(i).startsWith("HOME=")) {
            home = envs.at(i).section('=', 1, 1);
        }
    }

    IconFinder *finder = NULL;

    if (QFile::exists(home + "/.local/share/icons/" + name + "/icon.cache")) {
        finder = new CachedIconFinder(themePath);
    }
    else {
        finder = new GenericIconFinder(themePath);
    }

    ret = new IconTheme(name, finder);
    themes.insert(name, ret);

    return ret;
}

QIcon IconTheme::getIcon(const QString &name, int size, const QString &type) const {
    QStringList ext;
    ext.append(".png");
    //ext.append(".svg");
    ext.append(".xpm");

    QIcon ret;

    QStringList types;

    if (type != "") {
        types.append(type);
    }
    else {
        types.append("Fixed");
        types.append("Threshold");
        types.append("Scalable");
    }

    for (int j = 0; j < types.size(); j++) {
        QString t = types.at(j);

        for (int i = 0; i < ext.size(); i++) {
            QString n = name + ext.at(i);
            ret = this->getIconHelper(n, size, t);

            if (ret.isNull()) {
                if (!this->m_parent.contains(this->getTheme("hicolor"))) {
                    IconTheme * theme = this->getTheme("hicolor");
                    ret = theme->getIconHelper(n, size, t);
                }
            }

            if (!ret.isNull()) {
                break;
            }
        }

        if (!ret.isNull()) {
            break;
        }
    }

    if (ret.isNull()) {
        ret = this->getIconFromStuff(name, size, type);
    }

    return ret;
}

QIcon IconTheme::getIconFromStuff(const QString &name, int size, const QString &type) const {
    if (QFile::exists(name)) {
        return QIcon(name);
    }

    QStringList ext;
    ext.append("");
    ext.append(".png");
    ext.append(".xpm");

    for (int i = 0; i < ext.size(); i++) {
        QString n = name + ext.at(i);
        QString path = "/usr/share/pixmaps/" + n;

        if (QFile::exists(path)) {
            return QIcon(path);
        }

        path = "/usr/share/icons/" + n;

        if (QFile::exists(path)) {
            return QIcon(path);
        }
    }

    return QIcon();
}

QIcon IconTheme::getIconHelper(const QString &name, int size, const QString &type) const {
    QIcon ret = this->m_finder->getIcon(name, size, type);

    if (!ret.isNull()) {
        return ret;
    }

    for (int i = 0; i < this->m_parent.size(); i++) {
        IconTheme *theme = this->m_parent.at(i);

        ret = theme->getIconHelper(name, size, type);

        if (!ret.isNull()) {
            break;
        }
    }

    return ret;
}
