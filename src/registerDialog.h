#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QPushButton>
#include <global.h>
#include <ui_registerDialog.h>
#include <regex>

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
    void SLOT_registFinished(reqID id, QString res_data, errorCodes code);

private:
    Ui::registerDialog* ui;
};

#endif  // !REGISTERDIALOG_H
