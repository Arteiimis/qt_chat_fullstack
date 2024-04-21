#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H


#include "qtmetamacros.h"
#include <ui_loginDialog.h>

class loginDialog: public QDialog
{
    Q_OBJECT

public:
    explicit loginDialog(QWidget* parent = 0);
    ~loginDialog();

private:
    Ui::loginDialog* loginUi;

signals:
    void switchRegister();
    void loginSuccess();
};

#endif  // !LOGINDIALOG_H
