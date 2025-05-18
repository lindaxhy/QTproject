#ifndef INSPIRATIONPOPUP_H
#define INSPIRATIONPOPUP_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

class InspirationPopup : public QDialog
{
    Q_OBJECT
public:
    InspirationPopup(QString quote, QString question, QString imagePath, QWidget *parent = nullptr);


private:
    QLabel *textLabel;
    QLabel *imageLabel;
    QLabel *questionLabel;
    QPushButton *closeButton;
};

#endif // INSPIRATIONPOPUP_H
