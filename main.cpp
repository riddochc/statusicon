#include "statusicon.h"
#include <QApplication>
#include <QMessageBox>
#include <QCommandLineParser>
#include <stdio.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
       QMessageBox::critical(0, QObject::tr("Systray"), QObject::tr("No system tray detected on this system"));
       return 1;
    }

    QApplication::setQuitOnLastWindowClosed(false);
    QApplication::setApplicationName("statusicon");
    QApplication::setApplicationVersion("0.1");
    QCommandLineParser parser;
    parser.setApplicationDescription("A status icon in the system tray, watching a file which indicates the status");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("statusfile", QCoreApplication::translate("main", "File containing status information"));
    parser.process(a);
    const QStringList args = parser.positionalArguments();
    if (args.length() < 1) {
        fputs("Requires a filename to locate status information\n", stderr);
        return 1;
    }
    QString fname = args.at(0);
    QFileInfo fi(fname);
    if (!fi.isFile()) {
        fputs("Can't read status file, doesn't exist yet?", stderr);
        return 1;
    }
    QString statusfile = fi.canonicalFilePath();
    QString statusdir = fi.dir().path();

    StatusIcon w(&statusfile, &statusdir);
    // w.show();
    return a.exec();
}
