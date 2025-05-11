#ifndef CITY_H
#define CITY_H

#include <QWidget>

namespace Ui {
class city;
}

class city : public QWidget
{
    Q_OBJECT

public:
    explicit city(QWidget *parent = nullptr);
    ~city();

private slots:
    void on_btn_confirm_clicked();

    void on_cbo_province_currentIndexChanged(int index);



private:
    Ui::city *ui;
};

#endif // CITY_H
