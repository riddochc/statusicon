#ifndef STATUSICON_H
#define STATUSICON_H

#include <QSystemTrayIcon>
#include <QDialog>
#include <QAction>
#include <QFileSystemWatcher>
#include <QString>
#include <QMenu>
#include <QMessageBox>
#include <QDir>
#include <QFileInfo>
#include <QTimer>

#include "configfile.h"

class StatusIcon : public QDialog
{
    Q_OBJECT

public:
    StatusIcon(QString* watchFile, QString* watchDir);

private slots:
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void showMessage();
    void messageClicked();
    void setIcon();
    void fileChanged();

private:
    QAction *quitAction;
    QString *statusfile;
    QString *statusdir;
    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
    QFileSystemWatcher *watcher;
    QTimer *timer;
    ConfigFile *config;
    QString *message;
    QString *title;
};

#endif // STATUSICON_H
