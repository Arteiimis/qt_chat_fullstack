#include "loginDialog.h"
#include "qpushbutton.h"

loginDialog::loginDialog(QWidget* parent)
    : QDialog(parent), loginUi(new Ui::loginDialog) {

    loginUi->setupUi(this);
    loginUi->pwdEdit->setEchoMode(QLineEdit::Password);
    setWindowFlag(Qt::WindowContextHelpButtonHint, false);

    connect(loginUi->registButton, &QPushButton::clicked, this, &loginDialog::switchRegister);
}

loginDialog::~loginDialog() {
    delete loginUi;
}
