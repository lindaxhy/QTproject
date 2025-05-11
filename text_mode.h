#ifndef TEXT_MODE_H
#define TEXT_MODE_H

#include <QWidget>

namespace Ui {
class text_mode;
}

class text_mode : public QWidget
{
    Q_OBJECT

public:
    explicit text_mode(QWidget *parent = nullptr);
    ~text_mode();

private slots:
    void on_btn_confirm_clicked();

    void on_cbo_language_currentIndexChanged(int index);

    void on_btn_return_clicked();

private:
    Ui::text_mode *ui;
};

#endif // TEXT_MODE_H
