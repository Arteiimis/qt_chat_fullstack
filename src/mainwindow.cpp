#include "loginDialog.h"
#include "mainwindow.h"
#include "qnamespace.h"
#include "registerDialog.h"


MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    sizePolicy().setRetainSizeWhenHidden(true);  // 隐藏时保持大小不变

    // 初始化登录对话框
    loginDialog = new class loginDialog(this);
    loginDialog->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    setCentralWidget(loginDialog);

    // 同步主窗口与登录对话框大小
    resize(loginDialog->size());
    setFixedSize(loginDialog->size());

    // 初始化注册对话框
    registerDialog = new class registerDialog(this);
    registerDialog->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    registerDialog->hide();

    connect(loginDialog, &loginDialog::switchRegister, this, &MainWindow::switchRegister);
    connect(registerDialog, &registerDialog::cancelRegister, this, &MainWindow::cancelRegister);
}

// public slots:
void MainWindow::switchRegister() {
    setCentralWidget(registerDialog);
    loginDialog->hide();
    registerDialog->show();

    resize(registerDialog->size());
    setFixedSize(registerDialog->size());
}

void MainWindow::cancelRegister() {
    setCentralWidget(loginDialog);
    registerDialog->hide();
    loginDialog->show();

    resize(loginDialog->size());
    setFixedSize(loginDialog->size());
}
// public slots end

MainWindow::~MainWindow() {
    delete ui;
}
