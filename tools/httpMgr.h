#ifndef HTTPMGR_H
#define HTTPMGR_H

#include "global.h"
#include "singleton.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QString>
#include <QUrl>
#include <memory>


// CRTP：Curiously Recurring Template Pattern
class httpManager: public QObject,
                   public singleton<httpManager>,
                   public std::enable_shared_from_this<httpManager>
{
    Q_OBJECT

public:
    ~httpManager();

private:
    httpManager();
    void postHttpReqest(const QUrl& url, const QJsonObject& json_data, reqID id, modules module);

private slots:
    void SLOT_HttpFinished(reqID id, QString res_data, errorCodes code, modules module);

signals:
    void SIG_HttpFinished(reqID id, QString res_data, errorCodes code, modules module);
    void SIG_registFinished(reqID id, QString res_data, errorCodes code);
    void SIG_loginFinished(reqID id, QString res_data, errorCodes code);

private:
    friend class singleton<httpManager>;  // 使得基类可以访问派生类的私有成员
    QNetworkAccessManager _manager;
};

#endif  // !HTTPMGR_H
