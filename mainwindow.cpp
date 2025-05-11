#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "inspirationpopup.h"
#include "inspirationcalendarwidget.h"

#include <QMessageBox>
#include <QDate>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QRandomGenerator>
#include <QDebug>
#include <QCoreApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 创建自定义日历控件
    InspirationCalendarWidget *calendar = new InspirationCalendarWidget(this);
    calendar->setGridVisible(true);
    calendarWidget = calendar; // 存储指针，后续更新用

    // 替换 UI 里的 QCalendarWidget
    QWidget *container = ui->calendarWidget->parentWidget(); // 找到原日历的容器
    QLayout *layout = container->layout();                   // 获取该容器的布局
    if (layout) {
        layout->removeWidget(ui->calendarWidget);
        ui->calendarWidget->hide();  // 隐藏旧控件
        layout->addWidget(calendar);
    }

    // 日期点击切换手账内容
    connect(calendar, &QCalendarWidget::clicked, this, [=](const QDate &date){
        ui->textEdit->setText(notes.value(date));
    });

    // 手账变化自动保存 + 灵感值记录
    connect(ui->textEdit, &QTextEdit::textChanged, [=]() {
        QDate date = calendar->selectedDate();
        notes[date] = ui->textEdit->toPlainText();

        if (inspirationScoreMap.value(date, 0) == 0) {
            inspirationScoreMap[date] = 1;
            calendar->setScoreMap(inspirationScoreMap);
        }
    });

    // 灵感三连按钮
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::onInspirationClicked);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onInspirationClicked() {
    QString basePath = QCoreApplication::applicationDirPath();
    QFile file(basePath + "/inspirations.json");
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "错误", "无法读取 inspirations.json");
        return;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isArray()) {
        QMessageBox::warning(this, "错误", "JSON 格式错误！");
        return;
    }

    QJsonArray array = doc.array();
    if (array.isEmpty()) return;

    int index = QRandomGenerator::global()->bounded(array.size());
    QJsonObject obj = array[index].toObject();

    QString quote = obj["quote"].toString();
    QString question = obj["question"].toString();
    QString image = obj["image"].toString();

    QString fullImagePath = basePath + "/" + image;
    InspirationPopup popup(quote, question, fullImagePath, this);
    popup.exec();

    // 灵感值记录（弹窗也算一次）
    QDate today = QDate::currentDate();
    if (inspirationScoreMap.value(today, 0) == 0) {
        inspirationScoreMap[today] = 1;
        if (calendarWidget)
            calendarWidget->setScoreMap(inspirationScoreMap);
        QMessageBox::information(this, "灵感值 +1", "✨ 你已收获今日灵感！");
    }
}
