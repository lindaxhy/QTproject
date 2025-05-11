#ifndef HISTORYMANAGER_H
#define HISTORYMANAGER_H

#include <QObject>
#include <QStringList>
#include <QList>
#include <QNetworkAccessManager>
#include "historyevent.h"

class HistoryManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList eventTitles READ eventTitles NOTIFY historyUpdated)

public:
    explicit HistoryManager(QObject *parent = nullptr);

    Q_INVOKABLE void fetchHistory();
    Q_INVOKABLE QString eventDetail(int index) const;

signals:
    void historyUpdated();

private slots:
    void onReplyFinished(QNetworkReply *reply);

private:
    QNetworkAccessManager *m_manager;
    QList<HistoryEvent> m_events;
};

#endif // HISTORYMANAGER_H
