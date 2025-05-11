#include "historyevent.h"

HistoryEvent::HistoryEvent(const QString &date, const QString &title) : m_date(date), m_title(title) {}

QString HistoryEvent::date() const {return m_date;}

QString HistoryEvent::title() const {return m_title;}
