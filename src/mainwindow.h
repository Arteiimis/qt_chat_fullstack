#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "loginDialog.h"
#include "ui_mainwindow.h"
#include <QMainWindow>
#include "registerDialog.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

public slots:
    void switchRegister();

private:
    Ui::MainWindow* ui;
    loginDialog*    loginDialog;
    registerDialog* registerDialog;
};

#endif  // MAINWINDOW_H
