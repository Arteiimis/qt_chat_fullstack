#include "qobject.h"
#include "registerDialog.h"
#include <global.h>
#include <regex>


registerDialog::registerDialog(QWidget* parent)
    : QDialog(parent), ui(new Ui::registerDialog) {
    ui->setupUi(this);
    setWindowFlag(Qt::WindowContextHelpButtonHint, false);
    ui->pwdEdit->setEchoMode(QLineEdit::Password);
    ui->confirmEdit->setEchoMode(QLineEdit::Password);
    ui->errorHint->setProperty("state", "normal");
    refreshStyle(ui->errorHint);
    // 禁用按下 esc 退出

    connect(ui->cancelBtn, &QPushButton::clicked, this, &registerDialog::cancelRegister);
}

registerDialog::~registerDialog() {
    delete ui;
}

void registerDialog::on_getVerifyCodeButton_clicked() {
    auto       email = ui->emailEdit->text();
    std::regex emailPattern(
        R"(/^(([^<>()[\]\\.,;:\s@"]+(\.[^<>()[\]\\.,;:\s@"]+)*)|(".+"))@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\])|(([a-zA-Z\-0-9]+\.)+[a-zA-Z]{2,}))$/)");
    bool match = std::regex_match(email.toStdString(), emailPattern);
    if ( match ) {
        // TODO: 发送 HTTP 验证码请求
    } else {
        // TODO: 显示错误提示
        // showTips(tr("邮箱格式错误"), ui->errorHint);
    }
}
