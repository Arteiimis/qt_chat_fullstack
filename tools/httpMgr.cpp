#include "global.h"
#include "httpMgr.h"
#include "qlogging.h"
#include "qnetworkrequest.h"
#include "qobject.h"
#include "qstringview.h"
#include "qurl.h"


httpManager::~httpManager() { }

httpManager::httpManager() {
    connect(this, &httpManager::SIG_HttpFinished, this, &httpManager::SLOT_HttpFinished);
}

void httpManager::postHttpReqest(const QUrl& url, const QJsonObject& json_data, reqID id,
                                 modules module) {
    QByteArray      data = QJsonDocument(json_data).toJson();
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setHeader(QNetworkRequest::ContentLengthHeader, data.size());

    auto           self  = shared_from_this();
    QNetworkReply* reply = _manager.post(request, data);

    connect(reply, &QNetworkReply::finished, [self, reply, id, module]() {
        if ( reply->error() != QNetworkReply::NoError ) {
            qDebug() << reply->errorString();
            // 发送信号通知完成但是失败
            emit self->SIG_HttpFinished(id, "", errorCodes::NETWORK_ERROR, module);
            reply->deleteLater();  // 释放资源
            return;
        }

        QString res_data = QString::fromUtf8(reply->readAll());
        // 发送信号通知完成
        emit self->SIG_HttpFinished(id, res_data, errorCodes::SUCESS, module);
        reply->deleteLater();  // 释放资源
        return;
    });
}

void httpManager::SLOT_HttpFinished(reqID id, QString res_data, errorCodes code, modules module) {
    if ( module == modules::MODULE_REGIST ) {
        emit SIG_registFinished(id, res_data, code);
    }
}