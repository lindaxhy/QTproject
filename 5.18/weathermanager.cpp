#include "weathermanager.h"
#include <QTimer>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

WeatherManager::WeatherManager(QObject *parent) : QObject(parent), m_manager(new QNetworkAccessManager(this)) {
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &WeatherManager::fetchWeather);
    timer->start(60 * 60 * 1000); // 一小时

    // 启动时立即请求一次
    fetchWeather();
}

void WeatherManager::fetchWeather() {
    QString location = "101010100";
    QString key = "a785d54dd4fe47f7bb353ed680568096";
    QString url = QString("https://j25b6454p6.re.qweatherapi.com/v7/weather/7d?location=%1&key=%2").arg(location, key);

    QNetworkRequest request((QUrl(url)));
    connect(m_manager, &QNetworkAccessManager::finished,this, &WeatherManager::onReplyFinished);

    m_manager->get(request);
}

void WeatherManager::onReplyFinished(QNetworkReply *reply) {
    if (reply->error() != QNetworkReply::NoError) {
        qWarning() << "天气获取失败：" << reply->errorString();
        reply->deleteLater();
        return;
    }

    QByteArray data = reply->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isObject()) {
        qWarning() << "JSON 解析失败";
        reply->deleteLater();
        return;
    }

    QJsonObject obj = doc.object();
    QJsonArray dailyArray = obj.value("daily").toArray();
    if (dailyArray.isEmpty()) {
        qWarning() << "无有效天气数据";
        reply->deleteLater();
        return;
    }

    QJsonObject today = dailyArray.at(0).toObject();

    QString tempMax = today.value("tempMax").toString();
    QString tempMin = today.value("tempMin").toString();
    QString textDay = today.value("textDay").toString();
    QString humidity = today.value("humidity").toString();
    QString windScale = today.value("windScaleDay").toString();

    m_tempRange = tempMin + "℃ ~ " + tempMax + "℃";
    m_weatherText = textDay;
    m_humidity = "湿度：" + humidity + "%";
    m_windScale = "风力：" + windScale + "级";

    emit weatherUpdated();
    reply->deleteLater();
}

QString WeatherManager::temperatureRange() const { return m_tempRange; }
QString WeatherManager::weatherText() const { return m_weatherText; }
QString WeatherManager::humidity() const { return m_humidity; }
QString WeatherManager::windScale() const { return m_windScale; }
