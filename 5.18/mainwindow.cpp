#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "inspirationpopup.h"
#include "inspirationcalendarwidget.h"

#include <QMessageBox>
#include <QStandardPaths>
#include <QDir>
#include <QDate>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QRandomGenerator>
#include <QDebug>
#include <QCoreApplication>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setStyleSheet(
        "QPushButton {"
        "   background-color: #5F9EA0;"
        "   color: white;"
        "   border-radius: 5px;"
        "   padding: 8px;"
        "   min-width: 120px;"
        "}"
        "QPushButton:hover { background-color: #4682B4; }"
        );
    ui->setupUi(this);

    loadInspirationData();
    // 创建自定义日历控件
    InspirationCalendarWidget *calendar = new InspirationCalendarWidget(this);
    calendar->setGridVisible(true);
    calendarWidget = calendar; // 存储指针，后续更新用

    // 替换 UI 里的 QCalendarWidget
    QWidget *container = ui->calendarWidget->parentWidget(); // 找到原日历的容器
    QLayout *layout = container->layout();                   // 获取该容器的布局
    if (layout) {
        layout->removeWidget(ui->calendarWidget);
        delete ui->calendarWidget;  // 直接释放内存
        ui->calendarWidget = nullptr;  // 避免悬空指针
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
        // 自动保存笔记内容
        saveInspirationData();

        if (date == QDate::currentDate()) {
            if (inspirationScoreMap.value(date, 0) == 0) {
                inspirationScoreMap[date] = 1;
                calendar->setScoreMap(inspirationScoreMap);
                saveInspirationData(); // 灵感值变化时也保存
            }
        }
    });

    // 灵感三连按钮
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::onInspirationClicked);

    connect(ui->btnHistoryEvent, &QPushButton::clicked, this, &MainWindow::onHistoryEventClicked);

    connect(ui->btnExportStarMap, &QPushButton::clicked, this, &MainWindow::onExportStarMapClicked);

    // 设置日历的初始灵感值
    if (calendarWidget) {
        calendarWidget->setScoreMap(inspirationScoreMap);
    }

    // 恢复上次选中的日期内容
    QDate today = QDate::currentDate();
    if (notes.contains(today)) {
        ui->textEdit->setText(notes[today]);
    }

    // 展示天气
    weathermanager = new WeatherManager(this);
    // 连接信号
    connect(weathermanager, &WeatherManager::weatherUpdated, this, &MainWindow::weatherUpdatedUI);
    // 展示
    weatherUpdatedUI();
}


MainWindow::~MainWindow()
{
    saveInspirationData();
    delete ui;
}

QString MainWindow::dataFilePath() const {
    return QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/inspiration_data.json";
}
void MainWindow::loadInspirationData() {
    QFile file(dataFilePath());
    if (!file.open(QIODevice::ReadOnly)) {
        return;
    }
    QByteArray data = file.readAll();
    file.close();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (doc.isObject()) {
        QJsonObject obj = doc.object();
        // 加载笔记数据
        QJsonObject notesObj = obj["notes"].toObject();
        for (auto it = notesObj.begin(); it != notesObj.end(); ++it) {
            notes[QDate::fromString(it.key(), Qt::ISODate)] = it.value().toString();
        }

        // 加载灵感值数据
        QJsonObject scoreObj = obj["scores"].toObject();
        for (auto it = scoreObj.begin(); it != scoreObj.end(); ++it) {
            inspirationScoreMap[QDate::fromString(it.key(), Qt::ISODate)] = it.value().toInt();
        }
    }
}
// 保存数据到文件
void MainWindow::saveInspirationData() {
    QJsonObject notesObj;
    for (auto it = notes.begin(); it != notes.end(); ++it) {
        notesObj[it.key().toString(Qt::ISODate)] = it.value();
    }

    QJsonObject scoreObj;
    for (auto it = inspirationScoreMap.begin(); it != inspirationScoreMap.end(); ++it) {
        scoreObj[it.key().toString(Qt::ISODate)] = it.value();
    }

    QJsonObject mainObj;
    mainObj["notes"] = notesObj;
    mainObj["scores"] = scoreObj;

    // 确保应用数据目录存在
    QDir().mkpath(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation));

    QFile file(dataFilePath());
    if (file.open(QIODevice::WriteOnly)) {
        file.write(QJsonDocument(mainObj).toJson());
        file.close();
    }
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
        saveInspirationData(); // 立即保存
        QMessageBox::information(this, "灵感值 +1", "✨ 你已收获今日灵感！");
    }
}
void MainWindow::onHistoryEventClicked() {
    // 1. 假设用户点击“ESA成立”
    QString eventTitle = "1975年5月30日 ESA成立";

    // 2. 显示三个“平行时空猜想”选项
    QMessageBox box;
    box.setWindowTitle("探索 · 平行时空");
    box.setText(eventTitle + "\n如果ESA从未成立，2025年的太空格局会怎样？\n请选择一个假设方向：");

    QAbstractButton* btn1 = box.addButton("🌍 更强", QMessageBox::YesRole);
    QAbstractButton* btn2 = box.addButton("🌙 更弱", QMessageBox::YesRole);
    QAbstractButton* btn3 = box.addButton("🌐 分化", QMessageBox::YesRole);

    box.exec();

    QString result;
    QString userChoice;

    // 3. 根据选择设定“问题”和AI模拟分析
    if (box.clickedButton() == btn1) {
        userChoice = "会更强";
        result = "各国独立发展反而激发竞争力，法国和德国各自打造太空体系，推进更快。\n"
                 "🚀 导致欧洲出现两套导航系统，国际合作依然存在但分裂严重。";
    } else if (box.clickedButton() == btn2) {
        userChoice = "会更弱";
        result = "分散开发导致重复投入，欧洲整体航天发展缓慢，商业航天被美国与中国主导。\n"
                 "🔧 缺乏统一平台，欧洲错过了火星任务和深空探测窗口。";
    } else if (box.clickedButton() == btn3) {
        userChoice = "会分化";
        result = "法德竞争变为政治较量，英国发展商业发射平台，西班牙集中地球观测，出现技术分层。\n"
                 "🛰 出现多种技术标准，不利于联合探测。";
    }

    // 4. 展示AI分析
    QMessageBox::information(this, "AI 分析", result);

    // 5. 询问是否保存为“灵感卡片”
    auto reply = QMessageBox::question(this, "保存灵感卡片", "是否将本次猜想保存为卡片？");

    if (reply == QMessageBox::Yes) {
        QJsonObject card;
        card["date"] = QDate::currentDate().toString("yyyy-MM-dd");
        card["event"] = eventTitle;
        card["guess"] = userChoice;
        card["result"] = result;

        QFile file("parallel_cards.json");
        if (file.open(QIODevice::Append | QIODevice::Text)) {
            QTextStream out(&file);
            out << QJsonDocument(card).toJson(QJsonDocument::Compact) << "\n";
            file.close();
        }

        QMessageBox::information(this, "保存成功", "🎉 灵感卡片已保存！");
    }
}

void MainWindow::onExportStarMapClicked() {
    // 设置画布大小（可以调）
    int width = 800;
    int height = 600;

    //QPixmap pixmap(width, height);
    //pixmap.fill(Qt::black); // 黑色背景
    QString bgPath = "F:/QT/OurProject/InspirationCalendar/build/Desktop_Qt_6_9_0_MinGW_64_bit-Debug/images/star_background.jpg";
    QPixmap background(bgPath);
    QPixmap pixmap(width, height);
    QPainter painter(&pixmap);
    if (!background.isNull()) {
        painter.drawPixmap(0, 0, width, height, background);
    }
    else {
        pixmap.fill(QColor(15, 20, 30));
    }

    painter.setRenderHint(QPainter::Antialiasing);

    // 网格行列（标准月历是 7 列 × 最多 6 行）
    int cols = 7;
    int rows = 6;
    int margin = 20;
    int cellW = (width - 2 * margin) / cols;
    int cellH = (height - 2 * margin) / rows;

    // 获取当前月份的所有天
    QDate today = QDate::currentDate();
    QDate firstDay = QDate(today.year(), today.month(), 1);
    int daysInMonth = firstDay.daysInMonth();
    int startOffset = firstDay.dayOfWeek() % 7; // 周几开始（1~7）
    startOffset = (startOffset + 6) % 7; // 关键调整
    // 绘制日历
    int day = 1;
    //int cellIndex = startOffset;
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            // 跳过起始空白格
            //if (cellIndex++ < startOffset) continue;
            //int day = cellIndex - startOffset;
            if (row == 0 && col < startOffset) continue;
            if (day > daysInMonth) break;
            QRect cellRect {
                margin + col * cellW,
                margin + row * cellH,
                cellW,
                cellH
            };
            // 日期文字
            QFont dayFont("Arial", 30, QFont::Bold);
            painter.setFont(dayFont);
            painter.setPen(QColor(240, 240, 240));
            // 周末特殊标记
            if (col == 0 || col == 6) {  // 周日/周六
                painter.setPen(QColor(255, 150, 150));
            }
            //painter.setPen(Qt::white);
            painter.drawText(cellRect, Qt::AlignCenter, QString::number(day));

            QDate thisDate = QDate(today.year(), today.month(), day);
            int score = inspirationScoreMap.value(thisDate, 0);

            if (score > 0) {
                // 渐变光晕
                QPoint center = cellRect.center();
                QColor glowColor = QColor(255, 200, 100);

                QRadialGradient gradient(center, 15 + score * 3);
                gradient.setColorAt(0, glowColor);
                gradient.setColorAt(1, Qt::transparent);
                painter.setBrush(gradient);
                // 多层绘制增强立体感
                painter.setPen(Qt::NoPen);
                painter.drawEllipse(center, 5 + score, 5 + score);

                // 有灵感 → 画亮点
                /*QPoint center = cellRect.center();
                QColor glowColor = (score == 1) ? QColor(255, 223, 0) : QColor(255, 100, 0);
                painter.setBrush(glowColor);
                painter.setPen(Qt::NoPen);
                painter.drawEllipse(center, 5 + score * 2, 5 + score * 2);*/
            }
            day++;
        }
    }
    painter.end();

    // 保存图片
    QString filename = QString("inspiration_star_map_%1.png").arg(today.toString("yyyyMM"));
    if (pixmap.save(filename)) {
        QMessageBox::information(this, "成功", "🎉 灵感星图已保存为：\n" + filename);
    } else {
        QMessageBox::warning(this, "失败", "❌ 保存星图失败！");
    }
}

void MainWindow::weatherUpdatedUI() {
    // 将数据更新到控件
    ui->labelTemp->setText(weathermanager->temperatureRange());
    ui->labelWeather->setText(weathermanager->weatherText());
    ui->labelHumidity->setText(weathermanager->humidity());
    ui->labelWind->setText(weathermanager->windScale());
}
