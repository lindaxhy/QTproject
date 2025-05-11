#include "historymanager.h"
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>

HistoryManager::HistoryManager(QObject *parent) : QObject(parent), m_manager(new QNetworkAccessManager(this)) {}

void HistoryManager::fetchHistory() {
    QUrl url("https://api.oick.cn/lishi/api.php?format=json");
    QNetworkRequest request(url);

    connect(m_manager, &QNetworkAccessManager::finished,this, &HistoryManager::onReplyFinished);

    m_manager->get(request);
}

void HistoryManager::onReplyFinished(QNetworkReply *reply) {
    if (reply->error() != QNetworkReply::NoError) {
        qWarning() << "获取失败：" << reply->errorString();
        reply->deleteLater();
        return;
    }

    QByteArray responseData = reply->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(responseData);

    if (!doc.isObject()) {
        qWarning() << "返回格式异常";
        reply->deleteLater();
        return;
    }

    QJsonArray resultArray = doc.object().value("result").toArray();
    m_events.clear();

    for (const QJsonValue &val : resultArray) {
        QJsonObject obj = val.toObject();
        QString date = obj.value("date").toString();
        QString title = obj.value("title").toString();

        m_events.append(HistoryEvent(date, title));
    }

    emit historyUpdated();
    reply->deleteLater();
}

QString HistoryManager::eventDetail(int index) const {
    if (index < 0 || index >= m_events.size())
        return QStringLiteral("无效索引");

    const HistoryEvent &event = m_events[index];
    return QString("%1:%2").arg(event.date(), event.title());
}

