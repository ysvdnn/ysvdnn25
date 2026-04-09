#include "passEntry.h"
#include "passForm.h"

bool RuP::Craft(QWidget* parent) {
    PassForm form(this, parent);
    form.exec();
    return form.printed;
}

bool AmP::Craft(QWidget* parent) {
    PassForm form(this, parent);
    form.exec();
    return form.printed;
}
