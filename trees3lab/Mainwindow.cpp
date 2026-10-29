#include "MainWindow.h"

#include "TreeWidget.h"

#include <QFile>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>

#include <exception>
#include <sstream>
#include <string>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    setWindowTitle("Лабораторная работа №3. Бинарные деревья (вариант 4)");
    resize(900, 650);

    auto* central = new QWidget(this);
    auto* layout = new QVBoxLayout(central);

    treeWidget_ = new TreeWidget;
    treeWidget_->setTree(&tree_);
    layout->addWidget(treeWidget_, 1);

    traversalLabel_ = new QLabel("Обратный префиксный обход (УПЛ): —");
    traversalLabel_->setWordWrap(true);
    traversalLabel_->setTextInteractionFlags(Qt::TextSelectableByMouse);
    layout->addWidget(traversalLabel_);

    sumLabel_ = new QLabel("Сумма листьев: —");
    layout->addWidget(sumLabel_);

    auto* buttons = new QHBoxLayout;
    auto* openBtn = new QPushButton("Открыть файл...");
    auto* travBtn = new QPushButton("Обратный префиксный обход");
    auto* sumBtn = new QPushButton("Сумма листьев");
    auto* saveBtn = new QPushButton("Сохранить обход в файл...");
    for (auto* b : {openBtn, travBtn, sumBtn, saveBtn}) buttons->addWidget(b);
    layout->addLayout(buttons);

    setCentralWidget(central);

    connect(openBtn, &QPushButton::clicked, this, &MainWindow::openFile);
    connect(travBtn, &QPushButton::clicked, this, &MainWindow::runTraversal);
    connect(sumBtn, &QPushButton::clicked, this, &MainWindow::showLeavesSum);
    connect(saveBtn, &QPushButton::clicked, this, &MainWindow::saveResult);
}

bool MainWindow::ensureTree() {
    if (tree_.empty()) {
        QMessageBox::information(this, "Нет дерева", "Сначала откройте файл с деревом.");
        return false;
    }
    return true;
}

QString MainWindow::traversalText() const {
    QStringList parts;
    for (const Node* n : order_) parts << QString::number(n->value);
    return parts.join(' ');
}

void MainWindow::openFile() {
    const QString path = QFileDialog::getOpenFileName(
        this, "Открыть файл с деревом", QString(), "Текстовые файлы (*.txt);;Все файлы (*)");
    if (path.isEmpty()) return;

    QFile f(path);
    if (!f.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл:\n" + path);
        return;
    }
    const QByteArray data = f.readAll();
    std::istringstream in(std::string(data.constData(), static_cast<size_t>(data.size())));

    try {
        tree_ = BinaryTree::fromStream(in);
    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Ошибка чтения", QString::fromUtf8(e.what()));
        return;
    }

    order_.clear();
    treeWidget_->setTree(&tree_);
    traversalLabel_->setText("Обратный префиксный обход (УПЛ): —");
    sumLabel_->setText("Сумма листьев: —");
    if (tree_.empty()) QMessageBox::information(this, "Пусто", "Файл не содержит узлов.");
}

void MainWindow::runTraversal() {
    if (!ensureTree()) return;
    order_ = tree_.reversePreorderNodes();
    treeWidget_->setVisitOrder(order_);
    traversalLabel_->setText("Обратный префиксный обход (УПЛ): " + traversalText());
}

void MainWindow::showLeavesSum() {
    if (!ensureTree()) return;
    sumLabel_->setText("Сумма листьев: " + QString::number(tree_.leavesSum()));
}

void MainWindow::saveResult() {
    if (!ensureTree()) return;
    if (order_.empty()) runTraversal();

    const QString path = QFileDialog::getSaveFileName(
        this, "Сохранить результат обхода", "result.txt", "Текстовые файлы (*.txt)");
    if (path.isEmpty()) return;

    QFile f(path);
    if (!f.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось записать файл:\n" + path);
        return;
    }
    f.write(traversalText().toUtf8());
    f.write("\n");
}
