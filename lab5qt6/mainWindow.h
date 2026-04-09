#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QPushButton>
#include <vector>
#include "passEntry.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void onLoadClicked();
    void onTableDoubleClicked(int row, int col);

private:
    QTableWidget*            table;
    QPushButton*             loadBtn;
    std::vector<PassEntry*>  persons;

    void loadFromFile(QString filename);
    void fillTable();
};

#endif
