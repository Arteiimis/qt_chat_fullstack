#include "loginDialog.h"
#include "mainwindow.h"
#include "registerDialog.h"


MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    sizePolicy().setRetainSizeWhenHidden(true); // 隐藏时保持大小不变
    

    // 初始化登录对话框
    loginDialog = new class loginDialog();
    setCentralWidget(loginDialog);
    loginDialog->show();
    // 同步主窗口与登录对话框大小
    resize(loginDialog->size());
    setFixedSize(loginDialog->size());

    // 初始化注册对话框
    registerDialog = new class registerDialog();
    connect(loginDialog, &loginDialog::switchRegister, this, &MainWindow::switchRegister);
}

// public slots:
void MainWindow::switchRegister() {
    setCentralWidget(registerDialog);
    loginDialog->hide();
    registerDialog->show();
    
    resize(registerDialog->size());
    setFixedSize(registerDialog->size());
}
// public slots end

MainWindow::~MainWindow() {
    delete ui;
    if ( loginDialog ) {
        delete loginDialog;
        loginDialog = nullptr;
    }
    if ( registerDialog ) {
        delete registerDialog;
        registerDialog = nullptr;
    }
}
