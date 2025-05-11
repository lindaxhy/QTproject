#ifndef HISTORYEVENT_H
#define HISTORYEVENT_H

#include <Qstring>

class HistoryEvent
{
private:
    QString m_date;
    QString m_title;
public:
    HistoryEvent() = default;
    HistoryEvent(const QString &date, const QString &title);

    QString date() const;
    QString title() const;

};

#endif // HISTORYEVENT_H
