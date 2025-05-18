#ifndef WEATHERMANAGER_H
#define WEATHERMANAGER_H

#include <QObject>
#include <QString>
#include <QNetworkAccessManager>

class WeatherManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString temperatureRange READ temperatureRange NOTIFY weatherUpdated)
    Q_PROPERTY(QString weatherText READ weatherText NOTIFY weatherUpdated)
    Q_PROPERTY(QString humidity READ humidity NOTIFY weatherUpdated)
    Q_PROPERTY(QString windScale READ windScale NOTIFY weatherUpdated)

public:
    explicit WeatherManager(QObject *parent = nullptr);

    Q_INVOKABLE void fetchWeather();

    QString temperatureRange() const; // 15℃ ~ 26℃
    QString weatherText() const;      // 晴
    QString humidity() const;         // 湿度：48%
    QString windScale() const;        // 风力：3-4级

signals:
    void weatherUpdated();

private slots:
    void onReplyFinished(QNetworkReply *reply);

private:
    QNetworkAccessManager *m_manager;
    QString m_tempRange;
    QString m_weatherText;
    QString m_humidity;
    QString m_windScale;
};

#endif // WEATHERMANAGER_H
