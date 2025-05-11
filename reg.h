#ifndef REG_H
#define REG_H

#include <QWidget>

namespace Ui {
class reg;
}

class reg : public QWidget
{
    Q_OBJECT

public:
    explicit reg(QWidget *parent = nullptr);
    ~reg();

private slots:
    void on_btn_reg_clicked();

    void on_btn_return_clicked();

private:
    Ui::reg *ui;
};

#endif // REG_H
