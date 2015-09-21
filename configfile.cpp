#include "configfile.h"

ConfigFile::ConfigFile() {
}

ConfigFile::ConfigFile(const QString &fname, const QString &title, const QString &msg) {
    m_iconfile = fname;
    m_title = title;
    m_message = msg;
}

QString ConfigFile::iconfile() const {
    return m_iconfile;
}

QString ConfigFile::message() const {
    return m_message;
}

QString ConfigFile::title() const {
    return m_title;
}

void ConfigFile::seticonfile(const QString &fname) {
    m_iconfile = fname;
}

void ConfigFile::setmessage(const QString &msg) {
    m_message = msg;
}

void ConfigFile::settitle(const QString &title) {
    m_title = title;
}

void ConfigFile::read(const QJsonObject &json) {
    m_iconfile = json["iconfile"].toString();
    m_message = json["message"].toString();
    m_title = json["title"].toString();
}

void ConfigFile::write(QJsonObject &json) const {
    json["iconfile"] = m_iconfile;
    json["message"] = m_message;
    json["title"] = m_title;
}

bool ConfigFile::loadFile(QString &fname) {
    QFile loadFile(fname);
    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning() << "Couldn't open status file";
        return false;
    }
    QByteArray contents = loadFile.readAll();
    QJsonParseError *error = NULL;
    QJsonDocument loadDoc(QJsonDocument::fromJson(contents,error));
    if (error) {
        qDebug() << "Error parsing json: " << error->errorString();
        return false;
    } else {
        QJsonObject obj = loadDoc.object();
        if (obj.contains("iconfile") && obj.contains("message") && obj.contains("title")) {
            read(loadDoc.object());
            return true;
        } else {
            qDebug() << "JSON should contain 'iconfile', 'message', and 'title' properties";
            return false;
        }
    }
}

