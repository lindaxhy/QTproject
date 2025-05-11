#include "cal_login.h"
#include "ui_cal_login.h"
#include "mainwindow.h"
#include "reg.h"
#include <QString>
#include <QMessageBox>
#include <QDebug>
#include <QtSql/QSqlQuery>  //执行sql语句
#include <QtSql/QSqlDatabase>  //数据库驱动

//创建数据库
//遍历数据库
//增删改查
//QSqlDatabase db;
cal_login::cal_login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::cal_login)
{
    ui->setupUi(this);
    this->setWindowTitle("用户登入");
    ui->le_password->setEchoMode(QLineEdit::Password);
    //创建数据库
    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE"); //添加sqlite驱动
    db.setDatabaseName("user.db");

    //bool ok=db.open();  //创建数据库文件
    if(!db.open())
    {
        QMessageBox::about(this,"错误","数据库创建失败");
        return ;
    }
    QSqlQuery query;
    QString sql ="select * from userInfo";
    if(!query.exec(sql))  //查看有没有 userInfo表格
    {
        qDebug()<<"userInfo不存在";
        sql = "create table userInfo(username varchar(20),password varchar(20))";
        query.exec(sql);//创建用户账号密码表，执行sql
        sql = "INSERT INTO userInfo (username,password) VALUES ('zhangsan','123456')";
        query.exec(sql);//设置初始账号密码，执行aql
    }
    else
    {
        qDebug()<<"userInfo存在";
    }
}

cal_login::~cal_login()
{
    //db.close();
    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");
    db.close();
    delete ui;
}
//跳转到注册界面
void cal_login::on_btn_reg_clicked()
{
    reg *w=new reg();
    w->show();
    this->hide();
}

//跳转到主界面
void cal_login::on_btn_login_clicked()
{
    QString str=ui->le_password->text();
    if(str.length()>10)
    {
        QMessageBox ::about(this,"警告","字符个数不符合");
        return;
    }
    //bool ok =db.open(); //不存在就创建

    int open_flag=1; //存在就打开
    QSqlDatabase db = QSqlDatabase::database();
    if(db.isOpen())
    {
        QSqlQuery query("select username,password from userInfo",db); //查找表中账号密码
        while(query.next())
        {
            QString acc =query.value(0).toString();
            QString pass=query.value(1).toString();
            if(ui->le_username->text()==acc && ui->le_password->text()==pass)
            {
                this->hide();
                MainWindow *w=new MainWindow();
                w->show();
                db.close();
                open_flag=0;
                break;

            }
        }
        if(open_flag)
        {
            QMessageBox::about(this,"提示","账号或密码错误");
        }
    }
    else
    {
        qDebug()<<"数据库创建失败";
    }

    /*MainWindow *w=new MainWindow();
    w->show();
    this->hide();*/
}

//离开
void cal_login::on_btn_quit_clicked()
{
    this->close();
}

//显示密码
void cal_login::on_checkBox_clicked(bool checked)
{
    if(checked)
    {
        //显示
        ui->le_password->setEchoMode(QLineEdit::Normal);
    }
    else
    {
        //密文
        ui->le_password->setEchoMode(QLineEdit::Password);
    }
}

