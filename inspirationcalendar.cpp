#include "inspirationcalendar.h"
#include "ui_inspirationcalendar.h"

InspirationCalendar::InspirationCalendar(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::InspirationCalendar)
{
    ui->setupUi(this);
}

InspirationCalendar::~InspirationCalendar()
{
    delete ui;
}
