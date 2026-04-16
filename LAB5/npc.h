#ifndef NPC_H
#define NPC_H

#include <QString>
#include <QWidget>

struct Armor {
    int helmet;
    int chest;
    int boots;

    QString toString() const {
        return QString("%1/%2/%3")
        .arg(helmet)
            .arg(chest)
            .arg(boots);
    }
};

class NPC {
public:
    QString name;
    int health;
    Armor armor;

    virtual ~NPC() {}
    virtual bool Craft(QWidget* parent) = 0;
    virtual QString getDisplayName() = 0;
    virtual QString getTypeName() = 0;
    virtual QString getSecondStat() = 0;
    virtual QString getThirdStat() = 0;
};

class MagP : public NPC {
public:
    QString element;
    int mana;

    bool Craft(QWidget* parent) override;

    QString getDisplayName() override { return name; }
    QString getTypeName()    override { return element; }
    QString getSecondStat()  override { return QString::number(health); }
    QString getThirdStat()   override { return QString::number(mana); }
};

class VragP : public NPC {
public:
    QString rarity;
    int damage;

    bool Craft(QWidget* parent) override;

    QString getDisplayName() override { return name; }
    QString getTypeName()    override { return rarity; }
    QString getSecondStat()  override { return QString::number(health); }
    QString getThirdStat()   override { return QString::number(damage); }
};

#endif
