#include "spellsdlg.h"
#include "ui_spellsdlg.h"

SpellsDlg::SpellsDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SpellsDlg)
{
    ui->setupUi(this);
}

SpellsDlg::~SpellsDlg()
{
    delete ui;
}
