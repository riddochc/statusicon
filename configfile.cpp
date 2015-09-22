#include "configfile.h"

ConfigFile::ConfigFile() {}

ConfigFile::ConfigFile(const QString &fname, const QString &title, const QString &msg):
    iconfile(fname),
    title(title),
    message(msg)
{}

QString ConfigFile::geticonfile() const {
    return iconfile;
}

QString ConfigFile::getmessage() const {
    return message;
}

QString ConfigFile::gettitle() const {
    return title;
}

void ConfigFile::seticonfile(const QString &fname) {
    this->iconfile = fname;
}

void ConfigFile::setmessage(const QString &msg) {
    this->message = msg;
}

void ConfigFile::settitle(const QString &title) {
    this->title = title;
}

void ConfigFile::read(const QJsonObject &json) {
    iconfile = json["iconfile"].toString();
    message = json["message"].toString();
    title = json["title"].toString();
}

void ConfigFile::write(QJsonObject &json) const {
    json["iconfile"] = iconfile;
    json["message"] = message;
    json["title"] = title;
}

bool ConfigFile::loadFile(QString &fname) {
    QFile loadFile(fname);
    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning() << "Couldn't open status file";
        return false;
    }
    QByteArray contents = loadFile.readAll();
    QJsonParseError error;
    QJsonDocument configDoc = QJsonDocument::fromJson(contents, &error);
    if (error.error != QJsonParseError::NoError) {
        qDebug() << "Error parsing json: " << error.errorString();
        return false;
    } else {
        QJsonObject conf = configDoc.object();
        if (conf.contains("iconfile") && conf.contains("message") && conf.contains("title")) {
            read(configDoc.object());
            return true;
        } else {
            qDebug() << "JSON should contain 'iconfile', 'message', and 'title' properties";
            return false;
        }
    }
}

