#include <QtGui>
#include "statusicon.h"
#include "configfile.h"

StatusIcon::StatusIcon(const QString& watchfile, const QString& watchdir):
        statusfile(watchfile),
        statusdir(watchdir)
{
 //   ConfigFile config;

    watcher = new QFileSystemWatcher(this);
    watcher->addPath(statusfile);
    watcher->addPath(statusdir);

    quitAction = new QAction(tr("&Quit"), this);

    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(quitAction);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);

    timer = new QTimer(this);

    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(watcher, SIGNAL(fileChanged(const QString &)), this, SLOT(fileChanged()));
    connect(watcher, SIGNAL(directoryChanged(const QString &)), this, SLOT(fileChanged()));
    connect(trayIcon, SIGNAL(messageClicked()), this, SLOT(messageClicked()));
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
    connect(timer, SIGNAL(timeout()), this, SLOT(setIcon()));

    setIcon();

    trayIcon->show();
}

void StatusIcon::setIcon() {
    timer->stop();
    if (config.loadFile(statusfile)) {
        QIcon icon = QIcon(config.geticonfile());
        trayIcon->setIcon(icon);
        setWindowIcon(icon);
        message = config.getmessage();
        title = config.gettitle();
        trayIcon->setToolTip(message);
        showMessage();
    }
}

void StatusIcon::iconActivated(QSystemTrayIcon::ActivationReason reason) {
    if (reason == QSystemTrayIcon::MiddleClick || reason == QSystemTrayIcon::Trigger) {
        showMessage();
    }
}

void StatusIcon::showMessage() {
    QSystemTrayIcon::MessageIcon msgicon = QSystemTrayIcon::MessageIcon(QSystemTrayIcon::Information);
    trayIcon->showMessage(title, message, msgicon, 2500);
}

void StatusIcon::messageClicked() {
    QMessageBox::information(0, tr("StatusIcon"), tr("Huh?"));
}

void StatusIcon::fileChanged() {
    if (timer->remainingTime() == -1) { // not already set?
        timer->start(250);
    }
}
