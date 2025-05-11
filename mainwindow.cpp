#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cal_login.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("主界面");
}

MainWindow::~MainWindow()
{
    delete ui;
}
//跳转到登录界面
void MainWindow::on_btn_return_clicked()
{
    cal_login *w=new cal_login();
    w->show();
    this->hide();
}

