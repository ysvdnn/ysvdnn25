#ifndef PASSFORM_H
#define PASSFORM_H

#include <QDialog>
#include "passEntry.h"

class PassForm : public QDialog {
    Q_OBJECT

public:
    bool printed;

    explicit PassForm(PassEntry* person, QWidget* parent = nullptr);

private slots:
    void onPrintClicked();
    void onCancelClicked();
};

#endif
