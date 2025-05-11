#include "inspirationcalendar.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    InspirationCalendar w;
    w.show();
    return a.exec();
}
