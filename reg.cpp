#include "reg.h"
#include "ui_reg.h"
#include "cal_login.h"
#include "city.h"
#include <QMessageBox>
#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlRecord>
reg::reg(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::reg)
{
    ui->setupUi(this);
    this->setWindowTitle("用户注册");
    ui->le_password->setEchoMode(QLineEdit::Password);
    ui->le_confirm->setEchoMode(QLineEdit::Password);
}

reg::~reg()
{
    QSqlDatabase db = QSqlDatabase::database();
    db.close();
    delete ui;
}
//跳转到城市界面
void reg::on_btn_reg_clicked()
{

    QString str1=ui->le_password->text();
    if(str1.length()>10)
    {
        QMessageBox ::about(this,"警告","字符个数不符合");
        return;
    }
    if(str1.length()==0)
    {
        QMessageBox::about(this,"警告","请输入密码");
        return ;
    }
    QString str2=ui->le_confirm->text();
    int i=QString::compare(str1,str2,Qt::CaseInsensitive);//区分大小写
    if(i)
    {
        QMessageBox ::about(this,"警告","两次输入不同");
        return;
    }

    QSqlDatabase db = QSqlDatabase::database();
    //db.setDatabaseName("user.db");

    int flag=1;//注册标志：为1，注册；为0，不注册
    bool ok=db.open();

    if(ok)
    {
        QSqlQuery query("select username from userInfo",db);
        while(query.next())
        {
            if(ui->le_username->text()==query.value(0).toString())
            {
                flag=0;
                break;
            }
        }
        if(flag)
        {
            QSqlQuery query;
            query.prepare("INSERT INTO userInfo (username,password) VALUES (:username, :password)");
            query.bindValue(":username",ui->le_username->text());
            query.bindValue(":password",ui->le_confirm->text());

            query.exec();

            QMessageBox::about(this,"提示","用户注册成功！");
            this->hide();
            city *w=new city();
            w->show();
        }
        else QMessageBox::about(this,"提示","用户已存在！");
        /*else
        {
            qDebug()<<"数据库创建失败";
            exit(-1);
            QMessageBox::about(this,"提示","用户已存在！");
        }*/
    }
    else
    {
        qDebug()<<"数据库创建失败";
        exit(-1);
    }


    /*city *w=new city();
    w->show();
    this->hide();*/
}

//跳转到登录界面
void reg::on_btn_return_clicked()
{
    cal_login *w=new cal_login();
    w->show();
    this->hide();
}

