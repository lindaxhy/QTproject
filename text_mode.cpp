#include "text_mode.h"
#include "ui_text_mode.h"
#include "mainwindow.h"
#include "color_mode.h"

QStringList chineselist={"黑体","楷体","宋体"};
QStringList englishlist={"TimesNewRoman","Calibri","Arial"};

text_mode::text_mode(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::text_mode)
{
    ui->setupUi(this);
    this->setWindowTitle("个性化设置");

    //添加语言
    ui->cbo_language->addItem("中文");
    ui->cbo_language->addItem("Enlish");

    connect(ui->cbo_language,SIGNAL(currentIndexChanged(int)),this,SLOT(on_cbo_language_currentIndexChanged(int)));
}

text_mode::~text_mode()
{
    delete ui;
}

void text_mode::on_btn_confirm_clicked()
{
    MainWindow *w=new MainWindow();
    w->show();
    this->hide();
}


void text_mode::on_cbo_language_currentIndexChanged(int index)
{
    ui->cbo_text->clear();

    switch(index){
    case 0:
        ui->cbo_text->addItems(chineselist);
        break;
    case 1:
        ui->cbo_text->addItems(englishlist);
        break;
    }
}


void text_mode::on_btn_return_clicked()
{
    color_mode *w=new color_mode();
    w->show();
    this->hide();
}

