#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include "qdialog.h"
#include "qobject.h"
#include "qtmetamacros.h"
#include <ui_registerDialog.h>
#include <QPushButton>

class registerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit registerDialog(QWidget* parent = 0);
    ~registerDialog();

private:
    void showErrTip(QString errMsg, bool signal = true);
    void connectSlots();
    
signals:
    void cancelRegister();

private slots:
    void on_getVerifyCodeButton_clicked();

private:
    Ui::registerDialog* ui;
};

#endif  // !REGISTERDIALOG_H
