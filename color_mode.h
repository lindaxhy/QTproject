#ifndef COLOR_MODE_H
#define COLOR_MODE_H

#include <QWidget>
#include "mainwindow.h"

namespace Ui {
class color_mode;
}

class color_mode : public QWidget
{
    Q_OBJECT

public:
    explicit color_mode(QWidget *parent = nullptr);
    ~color_mode();
signals:
    void colorModeChanged(bool isDarkMode); // 新增信号：颜色模式变化时触发

private slots:
    void on_btn_confirm_clicked();

    void on_btn_return_clicked();

    //void onStateChanged();

    void on_cbBlack_stateChanged(int arg1);

    void on_cbWhite_stateChanged(int arg1);

private:
    Ui::color_mode *ui;
    MainWindow *mainWindow; // 新增成员变量
};

#endif // COLOR_MODE_H
