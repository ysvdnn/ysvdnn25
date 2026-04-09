#include "mainWindow.h"
#include <QVBoxLayout>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QHeaderView>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    QWidget* central = new QWidget(this);
    setCentralWidget(central);

    QVBoxLayout* layout = new QVBoxLayout(central);

    table = new QTableWidget();
    table->setColumnCount(3);
    table->setHorizontalHeaderLabels({"ФИО", "Дата рождения", "Тип"});
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    table->setColumnWidth(1, 130);
    table->setColumnWidth(2, 60);

    loadBtn = new QPushButton("Загрузить");
    loadBtn->setStyleSheet(
        "padding: 8px; font-size: 14px; font-weight: bold;"
        "background-color: #555; color: white; border-radius: 4px;"
        );

    layout->addWidget(table);
    layout->addWidget(loadBtn);

    setWindowTitle("Лабораторная работа 5 — Пропуска");
    resize(560, 400);

    connect(loadBtn, &QPushButton::clicked,
            this,    &MainWindow::onLoadClicked);
    connect(table,   &QTableWidget::cellDoubleClicked,
            this,    &MainWindow::onTableDoubleClicked);
}

MainWindow::~MainWindow() {
    for (PassEntry* p : persons) delete p;
}

void MainWindow::onLoadClicked() {
    QString filename = QFileDialog::getOpenFileName(
        this, "Открыть файл с данными", "", "Text files (*.txt);;All files (*)"
        );
    if (filename.isEmpty()) return;
    loadFromFile(filename);
    fillTable();
}

void MainWindow::loadFromFile(QString filename) {
    for (PassEntry* p : persons) delete p;
    persons.clear();

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл!");
        return;
    }

    QTextStream in(&file);
    in.setEncoding(QStringConverter::Utf8);

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;

        QStringList parts = line.split(" ", Qt::SkipEmptyParts);
        if (parts.size() < 6) continue;

        QString type = parts[0];

        if (type == "R" && parts.size() >= 7) {
            // R Фамилия Имя Отчество(или -) день месяц год
            RuP* person        = new RuP();
            person->lastName   = parts[1];
            person->firstName  = parts[2];
            person->patronymic = parts[3];
            person->birthDate.day   = parts[4].toInt();
            person->birthDate.month = parts[5].toInt();
            person->birthDate.year  = parts[6].toInt();
            persons.push_back(person);

        } else if (type == "A" && parts.size() >= 7) {
            // A Имя ВтороеИмя Фамилия день месяц год
            AmP* person        = new AmP();
            person->firstName  = parts[1];
            person->middleName = parts[2];
            person->lastName   = parts[3];
            person->birthDate.day   = parts[4].toInt();
            person->birthDate.month = parts[5].toInt();
            person->birthDate.year  = parts[6].toInt();
            persons.push_back(person);
        }
    }

    file.close();
}

void MainWindow::fillTable() {
    table->setRowCount(0);
    for (int i = 0; i < (int)persons.size(); i++) {
        table->insertRow(i);
        PassEntry* p = persons[i];

        table->setItem(i, 0, new QTableWidgetItem(p->getFullName()));
        table->setItem(i, 1, new QTableWidgetItem(p->getDateRu()));

        RuP* rup = dynamic_cast<RuP*>(p);
        QString typeName = (rup != nullptr) ? "RuP" : "AmP";
        table->setItem(i, 2, new QTableWidgetItem(typeName));
    }
}

void MainWindow::onTableDoubleClicked(int row, int col) {
    if (row < 0 || row >= (int)persons.size()) return;

    bool shouldRemove = persons[row]->Craft(this);

    if (shouldRemove) {
        delete persons[row];
        persons.erase(persons.begin() + row);
        fillTable();
    }
}
