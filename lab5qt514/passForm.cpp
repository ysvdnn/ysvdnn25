#include "passForm.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QFont>

PassForm::PassForm(PassEntry* person, QWidget* parent) : QDialog(parent) {
    printed = false;
    setWindowTitle("Пропуск");
    setFixedSize(370, 210);

    QHBoxLayout* mainLayout = new QHBoxLayout(this);

    QLabel* photoLabel = new QLabel();
    photoLabel->setFixedSize(110, 130);
    photoLabel->setAlignment(Qt::AlignCenter);
    photoLabel->setStyleSheet(
        "border: 2px solid #555;"
        "background-color: #e8e8e8;"
        "font-size: 50px;"
        );
    photoLabel->setText("\U0001F464");

    QVBoxLayout* rightLayout = new QVBoxLayout();

    QLabel* infoLabel = new QLabel();
    infoLabel->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    infoLabel->setWordWrap(true);

    QFont font = infoLabel->font();
    font.setPointSize(11);
    infoLabel->setFont(font);

    RuP* rup = dynamic_cast<RuP*>(person);
    AmP* amp = dynamic_cast<AmP*>(person);

    if (rup != nullptr) {
        QString pat = (rup->patronymic == "-") ? "" : rup->patronymic;
        QString text =
            "<b>Фамилия:</b> "  + rup->lastName  + "<br>" +
            "<b>Имя:</b> "      + rup->firstName + "<br>" +
            "<b>Отчество:</b> " + pat            + "<br>" +
            "<b>Дата:</b> "     + rup->getDateRu();
        infoLabel->setText(text);
    } else if (amp != nullptr) {
        QString text =
            "<b>Имя:</b> "     + amp->firstName  + "<br>" +
            "<b>Вт. Имя:</b> " + amp->middleName + "<br>" +
            "<b>Фамилия:</b> " + amp->lastName   + "<br>" +
            "<b>Дата:</b> "    + amp->getDateAm();
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

    rightLayout->addWidget(infoLabel);
    rightLayout->addStretch();
    rightLayout->addLayout(btnLayout);

    mainLayout->addWidget(photoLabel);
    mainLayout->addSpacing(10);
    mainLayout->addLayout(rightLayout);

    connect(printBtn,  &QPushButton::clicked, this, &PassForm::onPrintClicked);
    connect(cancelBtn, &QPushButton::clicked, this, &PassForm::onCancelClicked);
}

void PassForm::onPrintClicked() {
    printed = true;
    accept();
}

void PassForm::onCancelClicked() {
    printed = false;
    reject();
}
