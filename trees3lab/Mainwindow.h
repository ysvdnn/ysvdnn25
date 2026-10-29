#pragma once

#include "BinaryTree.h"

#include <QMainWindow>

#include <vector>

class QLabel;
class TreeWidget;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);

private slots:
    void openFile();
    void runTraversal();
    void showLeavesSum();
    void saveResult();

private:
    bool ensureTree();
    QString traversalText() const;

    BinaryTree tree_;
    std::vector<const Node*> order_;

    TreeWidget* treeWidget_;
    QLabel* traversalLabel_;
    QLabel* sumLabel_;
};
