#ifndef CONFIGFILE_H
#define CONFIGFILE_H

#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QDebug>

class ConfigFile
{
    public:
        ConfigFile();
        ConfigFile(const QString &fname, const QString &title, const QString &msg);

        QString geticonfile() const;
        QString getmessage() const;
        QString gettitle() const;

        void seticonfile(const QString &fname);
        void setmessage(const QString &msg);
        void settitle(const QString &title);

        void read(const QJsonObject &json);
        void write(QJsonObject &json) const;
        bool loadFile(QString &fname);

    private:
        QString iconfile;
        QString title;
        QString message;
};

#endif
