#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include "qdialog.h"
#include <ui_registerDialog.h>

class registerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit registerDialog(QWidget* parent = 0);
    ~registerDialog();

private:
    Ui::registerDialog* ui;
};

#endif  // !REGISTERDIALOG_H
