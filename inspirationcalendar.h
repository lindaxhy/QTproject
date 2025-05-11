#ifndef INSPIRATIONCALENDAR_H
#define INSPIRATIONCALENDAR_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class InspirationCalendar;
}
QT_END_NAMESPACE

class InspirationCalendar : public QMainWindow
{
    Q_OBJECT

public:
    InspirationCalendar(QWidget *parent = nullptr);
    ~InspirationCalendar();

private:
    Ui::InspirationCalendar *ui;
};
#endif // INSPIRATIONCALENDAR_H
