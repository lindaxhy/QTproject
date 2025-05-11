#ifndef INSPIRATIONCALENDARWIDGET_H
#define INSPIRATIONCALENDARWIDGET_H

#include <QCalendarWidget>
#include <QMap>
#include <QDate>

class InspirationCalendarWidget : public QCalendarWidget {
    Q_OBJECT
public:
    explicit InspirationCalendarWidget(QWidget *parent = nullptr);

    // 设置灵感值数据映射
    void setScoreMap(const QMap<QDate, int> &map);

protected:
    // 重绘每个日期单元格（画光点）
    void paintCell(QPainter *painter, const QRect &rect, QDate date) const override;


private:
    QMap<QDate, int> scoreMap; // 灵感值映射（日期 → 分数）
};

#endif // INSPIRATIONCALENDARWIDGET_H
