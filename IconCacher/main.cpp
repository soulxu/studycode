#include "IconCacheCreator.h"
#include "CachedIconFinder.h"

#include <QApplication>
#include <QListWidget>
#include <QDir>
#include <QTextStream>
#include <QPushButton>

#include "IconTheme.h"

int main(int argc, char **argv) {
    QApplication app(argc, argv);
/*
    IconCacheCreator creator("/usr/share/icons/Humanity");

    if (!creator.createCacheFile("/home/xuhejie/.local/share/icons/Humanity/icon.cache", true)) {
        qDebug("can not create cache file.");
    }
    else {
        qDebug("create cache file.");
    }
*/
    IconTheme *theme = IconTheme::getTheme("Humanity");

    if (theme == NULL) {
        qDebug("can not get theme");
        return -1;
    }

    //QPushButton b;
    //b.setIcon(finder.getIcon("gnome-panel.png", 16, "Applications"));
    //b.show();


    QListWidget lw;

    QDir desktops("/usr/share/applications/");
    QStringList filter;
    filter.append("*.desktop");
    QFileInfoList infoList = desktops.entryInfoList(filter);

    for (int i = 0; i < infoList.size(); i++) {
        QFile f(infoList.at(i).absoluteFilePath());
        f.open(QIODevice::ReadOnly);
        QTextStream in(&f);
        while (!in.atEnd()) {
            QString line = in.readLine();
            if (line.startsWith("Icon=")) {
                QString icon = line.section('=', 1, 1);
                QListWidgetItem *item = new QListWidgetItem();
                qDebug("find icon: %s\n", qPrintable(icon));
                item->setIcon(theme->getIcon(icon, 48, ""));
                item->setText(icon);
                lw.addItem(item);
            }
        }
        f.close();
    }

    lw.show();
    return app.exec();
}
