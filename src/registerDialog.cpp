#include "global.h"
#include "httpMgr.h"
#include "qdialog.h"
#include "qobject.h"
#include "qpushbutton.h"
#include "registerDialog.h"


registerDialog::registerDialog(QWidget* parent)
    : QDialog(parent), ui(new Ui::registerDialog) {
    ui->setupUi(this);
    setWindowFlag(Qt::WindowContextHelpButtonHint, false);
    ui->pwdEdit->setEchoMode(QLineEdit::Password);
    ui->confirmEdit->setEchoMode(QLineEdit::Password);
    ui->errorHint->setProperty("state", "normal");
    refreshStyle(ui->errorHint);
    // 禁用按下 esc 退出

    connectSlots();
}

registerDialog::~registerDialog() {
    delete ui;
}

void registerDialog::showErrTip(QString msg, bool signal) {
    ui->errorHint->setText(msg);
    if ( signal ) {
        ui->errorHint->setProperty("state", "normal");
    } else {
        ui->errorHint->setProperty("state", "error");
    }
    refreshStyle(ui->errorHint);
}

void registerDialog::connectSlots() {
    // 注册按钮
    connect(ui->cancelBtn, &QPushButton::clicked, this, &registerDialog::cancelRegister);

    // 获取验证码按钮
    connect(ui->getValidCodeBtn,
            &QPushButton::clicked,
            this,
            &registerDialog::on_getVerifyCodeButton_clicked);
    // 注册成功
    connect(httpManager::getInstence().get(),
            &httpManager::SIG_registFinished,
            this,
            &registerDialog::SLOT_registFinished);
}

void registerDialog::on_getVerifyCodeButton_clicked() {
    auto       email = ui->emailEdit->text();
    std::regex emailPattern(
        R"(/^(([^<>()[\]\\.,;:\s@"]+(\.[^<>()[\]\\.,;:\s@"]+)*)|(".+"))@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\])|(([a-zA-Z\-0-9]+\.)+[a-zA-Z]{2,}))$/)");
    bool match = std::regex_match(email.toStdString(), emailPattern);
    if ( match ) {
        // TODO: 发送 HTTP 验证码请求
    } else {
        showErrTip("邮箱格式错误", false);
    }
}

void registerDialog::SLOT_registFinished(reqID id, QString res_data, errorCodes code) {
    if ( code != errorCodes::SUCESS ) {
        showErrTip("网络错误", false);
        return;
    }

    // 解析 JSON 字符串， res 转化为 QByteArray
    QJsonDocument json_doc = QJsonDocument::fromJson(res_data.toUtf8());
    if ( json_doc.isNull() ) {
        showErrTip(tr("json解析失败"), false);
        return;
    }

    // 解析 JSON 对象失败处理：
    if ( !json_doc.isObject() ) {
        showErrTip(tr("json解析失败"), false);
        return;
    }

    json_doc.object();
    // TODO: 解析 JSON 对象

    return;
}
