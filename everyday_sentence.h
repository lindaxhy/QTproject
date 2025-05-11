#ifndef EVERYDAY_SENTENCE_H
#define EVERYDAY_SENTENCE_H

#include <QWidget>

namespace Ui {
class everyday_sentence;
}

class everyday_sentence : public QWidget
{
    Q_OBJECT

public:
    explicit everyday_sentence(QWidget *parent = nullptr);
    ~everyday_sentence();

private slots:


    void on_btn_confirm_clicked();

    void on_btn_skip_clicked();

    void onStateChanged();

    void on_cbAll_clicked();

private:
    Ui::everyday_sentence *ui;
};

#endif // EVERYDAY_SENTENCE_H
