#ifndef TICKET_H
#define TICKET_H

#include <QTextCodec>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDir>

struct Ticket {
    QString number;
    QString date;
    QString prize;
    QString buyerName;
    bool isWin;
    bool hasPresence;
    bool isLegalOnly;
    bool hasGift;

    Ticket(QString num, QString dt, QString pr, QString name,
           bool win, bool presence, bool legal, bool gift)
        : number(num), date(dt), prize(pr), buyerName(name),
        isWin(win), hasPresence(presence), isLegalOnly(legal), hasGift(gift) {}

    void saveToFile() {
        QFile file(QDir::homePath() + "/Documents/result.txt");
        if (file.open(QIODevice::Append | QIODevice::Text)) {
            QTextStream out(&file);
            out.setCodec("UTF-8");
            out << "Билет:\n";
            out << "№ билета: "       << number    << "\n";
            out << "Дата: "           << date      << "\n";
            out << "Приз: "           << prize     << "\n";
            out << "Имя покупателя: " << buyerName << "\n";
            out << "Результат: "      << (isWin ? "Победа" : "Поражение") << "\n";
            out << "Условия: ";
            if (!hasPresence && !isLegalOnly && !hasGift) {
                out << "нет";
            } else {
                if (hasPresence) out << "Личное присутствие ";
                if (isLegalOnly) out << "Только юр. лица ";
                if (hasGift)     out << "Подарок";
            }
            out << "\n------------------------\n";
            file.close();
        }
    }
};

#endif
