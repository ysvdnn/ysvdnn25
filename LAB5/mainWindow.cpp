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
    table->setColumnCount(5);
    table->setHorizontalHeaderLabels({"Имя", "Тип/Стихия", "ХП", "Мана/Урон", "Броня"});
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    table->setColumnWidth(1, 100);
    table->setColumnWidth(2, 60);
    table->setColumnWidth(3, 80);
    table->setColumnWidth(4, 100);

    loadBtn = new QPushButton("Загрузить");
    loadBtn->setMinimumHeight(35);
    loadBtn->setStyleSheet(
        "padding: 8px; font-size: 14px; font-weight: bold;"
        "background-color: #4a90d9; color: white; border-radius: 4px;"
        );

    layout->addWidget(table);
    layout->addWidget(loadBtn);

    setWindowTitle("Лабораторная работа 5 — НПС");
    resize(600, 400);

    connect(loadBtn, &QPushButton::clicked,
            this,    &MainWindow::onLoadClicked);
    connect(table,   &QTableWidget::cellDoubleClicked,
            this,    &MainWindow::onTableDoubleClicked);
}

MainWindow::~MainWindow() {
    for (NPC* n : npcs) delete n;
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
    for (NPC* n : npcs) delete n;
    npcs.clear();

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
        if (parts.size() < 9) continue;

        QString type = parts[0];

        if (type == "M") {
            // M код Имя Стихия Мана ХП Шлем Кираса Сапоги
            MagP* mag    = new MagP();
            mag->name    = parts[2];
            mag->element = parts[3];
            mag->mana    = parts[4].toInt();
            mag->health  = parts[5].toInt();
            mag->armor.helmet = parts[6].toInt();
            mag->armor.chest  = parts[7].toInt();
            mag->armor.boots  = parts[8].toInt();
            npcs.push_back(mag);

        } else if (type == "V") {
            // V код Имя Редкость Урон ХП Шлем Кираса Сапоги
            VragP* vrag   = new VragP();
            vrag->name    = parts[2];
            vrag->rarity  = parts[3];
            vrag->damage  = parts[4].toInt();
            vrag->health  = parts[5].toInt();
            vrag->armor.helmet = parts[6].toInt();
            vrag->armor.chest  = parts[7].toInt();
            vrag->armor.boots  = parts[8].toInt();
            npcs.push_back(vrag);
        }
    }

    file.close();
}

void MainWindow::fillTable() {
    table->setRowCount(0);
    for (int i = 0; i < (int)npcs.size(); i++) {
        table->insertRow(i);
        NPC* n = npcs[i];

        table->setItem(i, 0, new QTableWidgetItem(n->getDisplayName()));
        table->setItem(i, 1, new QTableWidgetItem(n->getTypeName()));
        table->setItem(i, 2, new QTableWidgetItem(n->getSecondStat()));
        table->setItem(i, 3, new QTableWidgetItem(n->getThirdStat()));
        table->setItem(i, 4, new QTableWidgetItem(n->armor.toString()));
    }
}

void MainWindow::onTableDoubleClicked(int row, int col) {
    if (row < 0 || row >= (int)npcs.size()) return;

    NPC* npc = npcs[row];

    bool shouldRemove = npc->Craft(this);

    if (shouldRemove) {
        delete npc;
        npcs.erase(npcs.begin() + row);
        fillTable();
    }
}
