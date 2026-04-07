#ifndef TICKETWINDOW_H
#define TICKETWINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QRadioButton>
#include <QCheckBox>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QMessageBox>
#include <QRegularExpression>

class TicketWindow : public QWidget
{
    Q_OBJECT
public:
    explicit TicketWindow(QWidget *parent = nullptr);

private slots:
    void resetForm();
    void saveTicket();

private:
    QLineEdit    *numberEdit;
    QLineEdit    *dateEdit;
    QLineEdit    *prizeEdit;
    QLineEdit    *nameEdit;

    QRadioButton *winBtn;
    QRadioButton *loseBtn;

    QCheckBox    *presenceCheck;
    QCheckBox    *legalCheck;
    QCheckBox    *giftCheck;

    QString validateFields();
};

#endif
