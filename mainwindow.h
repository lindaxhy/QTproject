#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QPushButton>
#include <QMap>
#include <QDate>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class InspirationCalendarWidget;  // 前向声明（拼写修正）

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //void setColorMode(bool isDarkMode);

public slots:
    void setColorMode(bool isDarkMode); // 新增公有槽函数

private slots:
    //void onDateClicked(const QDate &date);
    void onInspirationClicked();
    void onHistoryEventClicked();
    void onExportStarMapClicked();
    void setApplicationFont(const QString& fontName); // 新增槽函数
    //void setColorMode(bool isDarkMode);
    void onOpenColorMode(); // 打开颜色设置窗口的槽函数
private:
    Ui::MainWindow *ui;

    QMap<QDate, QString> notes;                // 保存每一天的灵感手账
    QMap<QDate, int> inspirationScoreMap;      // 灵感值记录
    InspirationCalendarWidget *calendarWidget; // 自定义日历控件
    void loadInspirationData();
    void saveInspirationData();
    QString dataFilePath() const;
};

#endif // MAINWINDOW_H
