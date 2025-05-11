#ifndef CAL_LOGIN_H
#define CAL_LOGIN_H

#include <QWidget>

namespace Ui {
class cal_login;
}

class cal_login : public QWidget
{
    Q_OBJECT

public:
    explicit cal_login(QWidget *parent = nullptr);
    ~cal_login();

private slots:
    void on_btn_reg_clicked();

    void on_btn_login_clicked();

    void on_btn_quit_clicked();

    void on_checkBox_clicked(bool checked);

private:
    Ui::cal_login *ui;
};

#endif // CAL_LOGIN_H
