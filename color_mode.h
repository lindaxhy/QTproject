#ifndef COLOR_MODE_H
#define COLOR_MODE_H

#include <QWidget>

namespace Ui {
class color_mode;
}

class color_mode : public QWidget
{
    Q_OBJECT

public:
    explicit color_mode(QWidget *parent = nullptr);
    ~color_mode();

private slots:
    void on_btn_confirm_clicked();

    void on_btn_return_clicked();

    //void onStateChanged();

    void on_cbBlack_stateChanged(int arg1);

    void on_cbWhite_stateChanged(int arg1);

private:
    Ui::color_mode *ui;
};

#endif // COLOR_MODE_H
