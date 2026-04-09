#ifndef PASSENTRY_H
#define PASSENTRY_H

#include <QString>
#include <QWidget>

struct BirthDate {
    int day;
    int month;
    int year;
};

class PassEntry {
public:
    QString lastName;
    QString firstName;
    BirthDate birthDate;

    virtual ~PassEntry() {}
    virtual bool Craft(QWidget* parent) = 0;
    virtual QString getFullName() = 0;

    QString getDateRu() {
        return QString("%1.%2.%3")
        .arg(birthDate.day,   2, 10, QChar('0'))
            .arg(birthDate.month, 2, 10, QChar('0'))
            .arg(birthDate.year,  4, 10, QChar('0'));
    }
};

class RuP : public PassEntry {
public:
    QString patronymic;

    bool Craft(QWidget* parent) override;

    QString getFullName() override {
        QString pat = (patronymic == "-") ? "-" : patronymic;
        return lastName + "  " + firstName + "  " + pat;
    }
};

class AmP : public PassEntry {
public:
    QString middleName;

    bool Craft(QWidget* parent) override;

    QString getFullName() override {
        return firstName + " " + middleName + " " + lastName;
    }

    QString getDateAm() {
        return QString("%1-%2-%3")
        .arg(birthDate.month, 2, 10, QChar('0'))
            .arg(birthDate.day,   2, 10, QChar('0'))
            .arg(birthDate.year,  4, 10, QChar('0'));
    }
};

#endif
