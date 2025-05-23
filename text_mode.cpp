#include "text_mode.h"
#include "ui_text_mode.h"
#include "mainwindow.h"
#include "color_mode.h"
#include <QFontDatabase>  // 添加头文件
#include <QSettings>

QStringList chineselist={"黑体","楷体","宋体"};
QStringList englishlist={"TimesNewRoman","Calibri","Arial"};

text_mode::text_mode(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::text_mode)
{
    ui->setupUi(this);
    this->setWindowTitle("个性化设置");
    // 清空全局字体列表
    chineselist.clear();
    englishlist.clear();
    // 获取系统中实际安装的字体名称

    QFontDatabase fontDB;
    foreach (QString family, fontDB.families()) {
        QList<QFontDatabase::WritingSystem> systems = fontDB.writingSystems(family);
        if (systems.contains(QFontDatabase::SimplifiedChinese)) {
            chineselist << family;
        } else if (systems.contains(QFontDatabase::Latin)) {
            englishlist << family;
        }
    }
    // 去重和排序
    chineselist.removeDuplicates();
    englishlist.removeDuplicates();
    chineselist.sort();
    englishlist.sort();

    //添加语言
    ui->cbo_language->addItem("中文");
    ui->cbo_language->addItem("Enlish");

    // 初始化字体显示名称映射
    fontDisplayNames["SimSun"] = "宋体";
    fontDisplayNames["SimHei"] = "黑体";
    fontDisplayNames["KaiTi"] = "楷体";
    fontDisplayNames["Times New Roman"] = "Times New Roman";
    fontDisplayNames["Arial"] = "Arial";

    // 初始加载字体
    on_cbo_language_currentIndexChanged(0);

    connect(ui->cbo_language,SIGNAL(currentIndexChanged(int)),this,SLOT(on_cbo_language_currentIndexChanged(int)));
}

text_mode::~text_mode()
{
    delete ui;
}

void text_mode::on_btn_confirm_clicked()
{
    /*// 获取当前选中的字体名称
    QString selectedFont = ui->cbo_text->currentText();
    qDebug() << "用户选择的字体：" << selectedFont;
    // 发送信号传递字体名称
    emit fontSelected(selectedFont);
    MainWindow *w=new MainWindow();
    w->show();
    this->hide();*/
    QString selectedFont = ui->cbo_text->currentData().toString(); // 获取实际字体名称
    qDebug() << "用户选择的字体：" << selectedFont;

    // 保存到配置文件
    QSettings settings;
    settings.setValue("Font", selectedFont);

    // 直接发射信号通知主窗口更新字体
    emit fontSelected(selectedFont);

    // 创建新主窗口并应用字体
    MainWindow *w = new MainWindow();
    w->show();
    this->hide();

}


void text_mode::on_cbo_language_currentIndexChanged(int index)
{
    ui->cbo_text->clear();

    /*switch(index){
    case 0:
        ui->cbo_text->addItems(chineselist);
        break;
    case 1:
        ui->cbo_text->addItems(englishlist);
        break;
    }*/
    const QStringList* list = nullptr;
    switch(index) {
    case 0:
        list = &chineselist;
        break;
    case 1:
        list = &englishlist;
        break;
    default:
        return;
    }

    foreach (const QString& family, *list) {
        QString displayName = fontDisplayNames.value(family, family);
        ui->cbo_text->addItem(displayName, family); // 显示友好名称，保存实际名称
    }
}


void text_mode::on_btn_return_clicked()
{
    color_mode *w=new color_mode();
    w->show();
    this->hide();
}

