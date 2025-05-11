#include "everyday_sentence.h"
#include "ui_everyday_sentence.h"
#include "color_mode.h"
#include <QMessageBox>
#include <QString>
everyday_sentence::everyday_sentence(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::everyday_sentence)
{
    ui->setupUi(this);
    this->setWindowTitle("个性化设置");

    connect(ui->cbEmotion,&QCheckBox::stateChanged,this,&everyday_sentence::onStateChanged);
    connect(ui->cbMovie,&QCheckBox::stateChanged,this,&everyday_sentence::onStateChanged);
    connect(ui->cbSaying,&QCheckBox::stateChanged,this,&everyday_sentence::onStateChanged);
    connect(ui->cbInspire,&QCheckBox::stateChanged,this,&everyday_sentence::onStateChanged);
}

everyday_sentence::~everyday_sentence()
{
    delete ui;
}




void everyday_sentence::on_btn_confirm_clicked()
{
    int allChecked=ui->cbAll->isChecked();

    if(allChecked)
    {
        color_mode *w=new color_mode();
        w->show();
        this->hide();
    }
    else
    {
        QMessageBox::about(this,"提示","请选择句子类型偏好");
    }

}


void everyday_sentence::on_btn_skip_clicked()
{
    color_mode *w=new color_mode();
    w->show();
    this->hide();
}

void everyday_sentence::onStateChanged(){
    QString s;

    int emotionChecked=ui->cbEmotion->isChecked();
    int movieChecked=ui->cbMovie->isChecked();
    int sayingChecked=ui->cbSaying->isChecked();
    int inspireChecked=ui->cbInspire->isChecked();

    if(emotionChecked && movieChecked && sayingChecked && inspireChecked){
        //全部选中
        ui->cbAll->setCheckState(Qt::Checked);
    }
    else if(!(emotionChecked || movieChecked || sayingChecked || inspireChecked))
    {
        //全都没选
        ui->cbAll->setCheckState(Qt::Unchecked);
    }
    else
    {
        ui->cbAll->setCheckState(Qt::PartiallyChecked);
    }
}


void everyday_sentence::on_cbAll_clicked()
{
    //手动点击时不能出现半选
    ui->cbAll->setTristate(false);
    int state = ui->cbAll->checkState();
    if(state==Qt::Checked){
        ui->cbEmotion->setChecked(true);
        ui->cbMovie->setChecked(true);
        ui->cbSaying->setChecked(true);
        ui->cbInspire->setChecked(true);

    }
    else if(state==Qt::Unchecked)
    {
        ui->cbEmotion->setChecked(false);
        ui->cbMovie->setChecked(false);
        ui->cbSaying->setChecked(false);
        ui->cbInspire->setChecked(false);
    }
}

