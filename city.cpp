#include "city.h"
#include "ui_city.h"
#include "everyday_sentence.h"

QStringList guangdong={"广州市","深圳市","珠海市"};
QStringList zhejiang={"杭州市","宁波市","温州市"};
QStringList shandong={"济南市","青岛市","烟台市"};
QStringList hebei={"石家庄市","保定市","廊坊市"};
QStringList neimeng={"呼和浩特市","鄂尔多斯市","赤峰市"};
QStringList beijing={"北京市"};




city::city(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::city)
{
    ui->setupUi(this);
    this->setWindowTitle("个性化设置");
    //添加省份
    ui->cbo_province->addItem("北京市");
    ui->cbo_province->addItem("广东省");
    ui->cbo_province->addItem("浙江省");
    ui->cbo_province->addItem("山东省");
    ui->cbo_province->addItem("河北省");
    ui->cbo_province->addItem("内蒙古自治区");

    //添加城市
    ui->cbo_city->addItems(guangdong);

    connect(ui->cbo_province,SIGNAL(currentIndexChanged(int)),this,SLOT(on_cbo_province_currentIndexChanged(int)));

}

city::~city()
{
    delete ui;
}

void city::on_btn_confirm_clicked()
{
    everyday_sentence *w=new everyday_sentence();
    w->show();
    this->hide();
}


void city::on_cbo_province_currentIndexChanged(int index)
{
    ui->cbo_city->clear();

    switch(index){
    case 0:
        ui->cbo_city->addItems(beijing);
        break;
    case 1:
        ui->cbo_city->addItems(guangdong);
        break;
    case 2:
        ui->cbo_city->addItems(zhejiang);
        break;
    case 3:
        ui->cbo_city->addItems(shandong);
        break;
    case 4:
        ui->cbo_city->addItems(hebei);
        break;
    case 5:
        ui->cbo_city->addItems(neimeng);
        break;
    }
}

