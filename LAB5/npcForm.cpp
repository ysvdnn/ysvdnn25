#include "npcForm.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QFont>

NpcForm::NpcForm(NPC* npc, QWidget* parent) : QDialog(parent) {
    printed = false;
    setWindowTitle("Карточка персонажа");
    setFixedSize(300, 320);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    QLabel* imageLabel = new QLabel();
    imageLabel->setFixedSize(100, 130);
    imageLabel->setAlignment(Qt::AlignCenter);
    imageLabel->setStyleSheet(
        "border: 2px solid #555;"
        "background-color: #e8e8e8;"
        "font-size: 40px;"
        );

    QLabel* infoLabel = new QLabel();
    infoLabel->setAlignment(Qt::AlignCenter);
    infoLabel->setWordWrap(true);

    QFont font = infoLabel->font();
    font.setPointSize(11);
    font.setBold(true);
    infoLabel->setFont(font);

    MagP*  mag  = dynamic_cast<MagP*>(npc);
    VragP* vrag = dynamic_cast<VragP*>(npc);

    if (mag != nullptr) {
        imageLabel->setText("🧙");

        // цвет стихии
        QString elemColor = "black";
        if (mag->element == "Огонь") elemColor = "orange";
        if (mag->element == "Вода")  elemColor = "blue";
        if (mag->element == "Земля") elemColor = "brown";

        QString text =
            "<span style='color:black;'>" + mag->name + "</span><br>" +
            "<span style='color:" + elemColor + ";'>" + mag->element + "</span><br>" +
            "<span style='color:green;'>ХП: " + QString::number(mag->health) + "</span> "
            "<span style='color:blue;'>Мана: " + QString::number(mag->mana) + "</span>";
        infoLabel->setText(text);

    } else if (vrag != nullptr) {
        imageLabel->setText("👹");

        // цвет имени по редкости
        QString nameColor = "black";
        if (vrag->rarity == "Редкий")  nameColor = "blue";
        if (vrag->rarity == "Обычный") nameColor = "green";
        if (vrag->rarity == "Легенда") nameColor = "orange";

        QString text =
            "<span style='color:" + nameColor + ";'>" + vrag->name + "</span><br>" +
            "<span style='color:red;'>ХП: " + QString::number(vrag->health) + "</span><br>" +
            "<span style='color:black;'>Броня: " + vrag->armor.toString() + "</span>";
        infoLabel->setText(text);
    }

    QHBoxLayout* btnLayout = new QHBoxLayout();
    QPushButton* printBtn  = new QPushButton("Печать");
    QPushButton* cancelBtn = new QPushButton("Отмена");

    printBtn->setStyleSheet(
        "background-color: #4a90d9; color: white;"
        "padding: 6px 16px; font-size: 13px; border-radius: 4px;"
        );
    cancelBtn->setStyleSheet(
        "background-color: #d94a4a; color: white;"
        "padding: 6px 16px; font-size: 13px; border-radius: 4px;"
        );

    btnLayout->addWidget(printBtn);
    btnLayout->addWidget(cancelBtn);

    mainLayout->addWidget(imageLabel, 0, Qt::AlignCenter);
    mainLayout->addWidget(infoLabel);
    mainLayout->addStretch();
    mainLayout->addLayout(btnLayout);

    connect(printBtn,  &QPushButton::clicked, this, &NpcForm::onPrintClicked);
    connect(cancelBtn, &QPushButton::clicked, this, &NpcForm::onCancelClicked);
}

void NpcForm::onPrintClicked() {
    printed = true;
    accept();
}

void NpcForm::onCancelClicked() {
    printed = false;
    reject();
}
