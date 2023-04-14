#ifndef SPELLSDLG_H
#define SPELLSDLG_H

#include <QDialog>

namespace Ui {
class SpellsDlg;
}

class SpellsDlg : public QDialog
{
    Q_OBJECT

public:
    explicit SpellsDlg(QWidget *parent = nullptr);
    ~SpellsDlg();

private:
    Ui::SpellsDlg *ui;
};

#endif // SPELLSDLG_H
