#include "inspirationpopup.h"
#include <QPixmap>
#include <QDebug>

InspirationPopup::InspirationPopup(QString quote, QString question, QString imagePath, QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("今日灵感三连");
    setFixedSize(400, 600);

    textLabel = new QLabel("🔹 一句话灵感：\n" + quote, this);
    textLabel->setWordWrap(true);
    textLabel->setAlignment(Qt::AlignCenter);

    imageLabel = new QLabel(this);
    QPixmap img(imagePath);
    qDebug() << "尝试加载图片路径：" << imagePath;

    if (!img.isNull())
        imageLabel->setPixmap(img.scaled(300, 200, Qt::KeepAspectRatio));
    else
        imageLabel->setText("❌ 图片加载失败");

    imageLabel->setAlignment(Qt::AlignCenter);

    questionLabel = new QLabel("🔹 一个问题：\n" + question, this);
    questionLabel->setWordWrap(true);
    questionLabel->setAlignment(Qt::AlignCenter);

    closeButton = new QPushButton("关闭", this);
    connect(closeButton, &QPushButton::clicked, this, &QDialog::accept);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(textLabel);
    layout->addWidget(imageLabel);
    layout->addWidget(questionLabel);
    layout->addWidget(closeButton);
}
