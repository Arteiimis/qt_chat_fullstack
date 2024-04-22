#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include "qjsonobject.h"
#include "qmap.h"
#include <QPushButton>
#include <functional>
#include <global.h>
#include <regex>
#include <ui_registerDialog.h>


class registerDialog: public QDialog
{
    Q_OBJECT

public:
    explicit registerDialog(QWidget* parent = 0);
    ~registerDialog();

private:
    void showErrTip(QString errMsg, bool signal = true);
    void initHttpHandlers();  // 初始化 HTTP 请求处理函数
    void connectSlots();      // 连接信号槽

signals:
    void cancelRegister();

private slots:
    void on_getVerifyCodeButton_clicked();
    void SLOT_registFinished(reqID id, QString res_data, errorCodes code);

private:
    Ui::registerDialog*                                  ui;
    QMap<reqID, std::function<void(const QJsonObject&)>> _handlers;
};

#endif  // !REGISTERDIALOG_H
