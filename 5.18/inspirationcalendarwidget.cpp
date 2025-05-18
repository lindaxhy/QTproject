#include "inspirationcalendarwidget.h"
#include <QPainter>

InspirationCalendarWidget::InspirationCalendarWidget(QWidget *parent)
    : QCalendarWidget(parent) {}

void InspirationCalendarWidget::setScoreMap(const QMap<QDate, int> &map) {
    scoreMap = map;
    update(); // 触发界面重绘
}

void InspirationCalendarWidget::paintCell(QPainter *painter, const QRect &rect, QDate date) const {
    QCalendarWidget::paintCell(painter, rect, date);

    if (scoreMap.contains(date)) {
        int score = scoreMap.value(date);
        QColor glowColor = (score == 1) ? QColor(255, 223, 0, 160) : QColor(255, 100, 0, 200);
        painter->setBrush(glowColor);
        painter->setPen(Qt::NoPen);
        QPoint center = rect.center();
        painter->drawEllipse(center, 4 + score, 4 + score);
    }
}
