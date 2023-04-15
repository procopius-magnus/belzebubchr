#ifndef SPELLSDLG_H
#define SPELLSDLG_H

#include <QDialog>
#include <QLabel>
#include <QSpinBox>

#include <vector>

namespace Ui {
class SpellsDlg;
}

class SpellsDlg : public QDialog
{
    Q_OBJECT

public:
    explicit SpellsDlg(QWidget *parent = nullptr);
    ~SpellsDlg();

    std::vector<QLabel*> labelVec;
    std::vector<QSpinBox*> spinBoxVec;

private:
    Ui::SpellsDlg *ui;

};

#endif // SPELLSDLG_H
