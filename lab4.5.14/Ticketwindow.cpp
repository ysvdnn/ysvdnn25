#include "TicketWindow.h"
#include "Ticket.h"

TicketWindow::TicketWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Счастливый билет");
    resize(400, 420);

    numberEdit = new QLineEdit();
    dateEdit   = new QLineEdit();
    prizeEdit  = new QLineEdit();
    nameEdit   = new QLineEdit();

    numberEdit->setPlaceholderText("1-12345");
    dateEdit->setPlaceholderText("11.02.2026");
    prizeEdit->setPlaceholderText("Автомобиль");
    nameEdit->setPlaceholderText("Иван");

    winBtn  = new QRadioButton("Победа");
    loseBtn = new QRadioButton("Поражение");
    winBtn->setChecked(true);

    QHBoxLayout *resultLayout = new QHBoxLayout();
    resultLayout->addWidget(winBtn);
    resultLayout->addWidget(loseBtn);
    resultLayout->addStretch();

    presenceCheck = new QCheckBox("Личное присутствие");
    legalCheck    = new QCheckBox("Только юр. лица");
    giftCheck     = new QCheckBox("Подарок");

    QPushButton *resetButton = new QPushButton("Сброс");
    QPushButton *saveButton  = new QPushButton("Сохранить");
    resetButton->setMinimumHeight(30);
    saveButton->setMinimumHeight(30);
    resetButton->setStyleSheet("background-color: #e74c3c; color: white; font-weight: bold;");
    saveButton->setStyleSheet("background-color: #2ecc71; color: white; font-weight: bold;");

    QHBoxLayout *buttonsLayout = new QHBoxLayout();
    buttonsLayout->addWidget(resetButton);
    buttonsLayout->addWidget(saveButton);

    QFormLayout *formLayout = new QFormLayout();
    formLayout->setSpacing(8);
    formLayout->addRow("№ билета",       numberEdit);
    formLayout->addRow("Дата",           dateEdit);
    formLayout->addRow("Приз",           prizeEdit);
    formLayout->addRow("Имя покупателя", nameEdit);
    formLayout->addRow("Результат",      resultLayout);

    QVBoxLayout *condLayout = new QVBoxLayout();
    condLayout->addWidget(presenceCheck);
    condLayout->addWidget(legalCheck);
    condLayout->addWidget(giftCheck);
    formLayout->addRow("Условия", condLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(10);
    mainLayout->addLayout(formLayout);
    mainLayout->addSpacing(10);
    mainLayout->addLayout(buttonsLayout);

    setLayout(mainLayout);

    connect(resetButton, &QPushButton::clicked, this, &TicketWindow::resetForm);
    connect(saveButton,  &QPushButton::clicked, this, &TicketWindow::saveTicket);
}

QString TicketWindow::validateFields()
{
    // 1. № билета: строго одна цифра, дефис, 5 цифр
    QRegularExpression numberRx("^\\d{1}-\\d{5}$");
    if (numberEdit->text().isEmpty())
        return "Заполните поле '№ билета'";
    if (!numberRx.match(numberEdit->text()).hasMatch())
        return "Поле '№ билета': формат — цифра-дефис-5цифр. Например: 1-12345";

    // 2. Дата: дд.мм.гггг
    QRegularExpression dateRx(
        "^(0[1-9]|[12][0-9]|3[01])\\.(0[1-9]|1[0-2])\\.(\\d{4})$"
        );
    if (dateEdit->text().isEmpty())
        return "Заполните поле 'Дата'";
    if (!dateRx.match(dateEdit->text()).hasMatch())
        return "Поле 'Дата': формат дд.мм.гггг. Например: 11.02.2026";

    // 3. Приз: анг+рус, только первая буква слова капсом
    QRegularExpression prizeRx("^([A-ZА-ЯЁ][a-zA-Zа-яёА-ЯЁ]*)(\\s[A-ZА-ЯЁ][a-zA-Zа-яёА-ЯЁ]*)*$");
    if (prizeEdit->text().isEmpty())
        return "Заполните поле 'Приз'";
    if (!prizeRx.match(prizeEdit->text()).hasMatch())
        return "Поле 'Приз': каждое слово с заглавной буквы (рус/англ). Например: Автомобиль";

    // 4. Имя покупателя: только рус, первая буква слова капсом
    QRegularExpression nameRx("^([А-ЯЁ][а-яё]+)(\\s[А-ЯЁ][а-яё]+)*$");
    if (nameEdit->text().isEmpty())
        return "Заполните поле 'Имя покупателя'";
    if (!nameRx.match(nameEdit->text()).hasMatch())
        return "Поле 'Имя покупателя': только русские буквы, каждое слово с заглавной. Например: Иван";

    return "";
}

void TicketWindow::resetForm()
{
    numberEdit->clear();
    dateEdit->clear();
    prizeEdit->clear();
    nameEdit->clear();
    winBtn->setChecked(true);
    presenceCheck->setChecked(false);
    legalCheck->setChecked(false);
    giftCheck->setChecked(false);
    numberEdit->setFocus();
}

void TicketWindow::saveTicket()
{
    QString error = validateFields();
    if (!error.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", error);
        return;
    }

    Ticket ticket(
        numberEdit->text(),
        dateEdit->text(),
        prizeEdit->text(),
        nameEdit->text(),
        winBtn->isChecked(),
        presenceCheck->isChecked(),
        legalCheck->isChecked(),
        giftCheck->isChecked()
        );

    ticket.saveToFile();
    QMessageBox::information(this, "Успех", "Данные сохранены в result.txt");
    resetForm();
}
