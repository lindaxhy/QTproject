#include "color_mode.h"
#include "ui_color_mode.h"
#include "text_mode.h"
#include "everyday_sentence.h"
#include <QMessageBox>
color_mode::color_mode(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::color_mode)
    , mainWindow(qobject_cast<MainWindow*>(parent)) // 保存父窗口指针
{
    ui->setupUi(this);
    this->setWindowTitle("个性化设置");

    /*connect(ui->cbBlack,&QCheckBox::stateChanged,this,&color_mode::onStateChanged);
    connect(ui->cbWhite,&QCheckBox::stateChanged,this,&color_mode::onStateChanged);*/
}

color_mode::~color_mode()
{
    delete ui;
}

void color_mode::on_btn_confirm_clicked()
{
    /*int blackChecked=ui->cbBlack->isChecked();
    int whiteChecked=ui->cbWhite->isChecked();
    if(blackChecked || whiteChecked)
    {
        text_mode *w=new text_mode();
        //w->setColorMode(blackChecked); // 传递颜色模式
        w->show();
        this->hide();
    }
    else
    {
        QMessageBox::about(this,"提示","请选择颜色模式");
    }*/
    bool isDarkMode = ui->cbBlack->isChecked();
    emit colorModeChanged(isDarkMode); // 发射信号
    text_mode *w=new text_mode();
    //w->setColorMode(blackChecked); // 传递颜色模式
    w->show();
    this->hide(); // 隐藏颜色设置窗口

}


void color_mode::on_btn_return_clicked()
{
    everyday_sentence *w=new everyday_sentence();
    w->show();
    this->hide();
}

/*void color_mode::onStateChanged()
{
    int blackChecked=ui->cbBlack->isChecked();
    int whiteChecked=ui->cbBlack->isChecked();
    if(blackChecked) ui->cbWhite->setCheckState(Qt::Unchecked);
    if(whiteChecked) ui->cbBlack->setCheckState(Qt::Unchecked);

}*/

void color_mode::on_cbBlack_stateChanged(int arg1)
{
    //ui->cbWhite->setCheckState(Qt::Unchecked);
    //ui->cbBlack->setCheckState(Qt::Checked);
    if (arg1 == Qt::Checked)
        ui->cbWhite->setChecked(false);
}


void color_mode::on_cbWhite_stateChanged(int arg1)
{
    //ui->cbBlack->setCheckState(Qt::Unchecked);
    //ui->cbWhite->setCheckState(Qt::Checked);
    if (arg1 == Qt::Checked)
        ui->cbBlack->setChecked(false);
}


