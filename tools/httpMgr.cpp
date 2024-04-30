#include "global.h"
#include "httpMgr.h"
#include "qnetworkrequest.h"
#include "qobject.h"
#include "qstringview.h"
#include "qurl.h"
#include "spdlog/spdlog.h"



httpManager::~httpManager() { }

httpManager::httpManager() {
    connect(this, &httpManager::SIG_HttpFinished, this, &httpManager::SLOT_HttpFinished);
}

/**
 * @brief 发送HTTP POST请求。
 *
 * 使用提供的JSON数据向指定URL发送HTTP POST请求。
 *
 * @param url 要发送请求的URL。
 * @param json_data 要包含在请求主体中的JSON数据。
 * @param id 请求ID，用于标识请求。
 * @param module 与请求关联的模块。
 */
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
            spdlog::error("HTTP request failed: {}", reply->errorString().toStdString());
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

/**
 * @brief 处理HTTP请求完成的槽函数。
 *
 * @param id 请求ID。
 * @param res_data 请求返回的数据。
 * @param code 错误码。
 * @param module 与请求关联的模块。
 */
void httpManager::SLOT_HttpFinished(reqID id, QString res_data, errorCodes code, modules module) {
    if ( module == modules::MODULE_REGIST ) {
        emit SIG_registFinished(id, res_data, code);
    }
}
