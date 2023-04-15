#include "spellsdlg.h"
#include "ui_spellsdlg.h"

SpellsDlg::SpellsDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SpellsDlg)
{
    ui->setupUi(this);

    labelVec = {ui->label1, ui->label2, ui->label3, ui->label4, ui->label5, ui->label6, ui->label7,
                ui->label8, ui->label9, ui->label10, ui->label11, ui->label12, ui->label13, ui->label14,
                ui->label15, ui->label16, ui->label17, ui->label18, ui->label19, ui->label20, ui->label21,
                ui->label22, ui->label23, ui->label24, ui->label25, ui->label26, ui->label27, ui->label28,
                ui->label29, ui->label30, ui->label31, ui->label32, ui->label33, ui->label34, ui->label35,
                ui->label36, ui->label37, ui->label38, ui->label39, ui->label40, ui->label41, ui->label42};

    spinBoxVec = {ui->spinBox1, ui->spinBox2, ui->spinBox3, ui->spinBox4, ui->spinBox5, ui->spinBox6, ui->spinBox7,
                ui->spinBox8, ui->spinBox9, ui->spinBox10, ui->spinBox11, ui->spinBox12, ui->spinBox13, ui->spinBox14,
                ui->spinBox15, ui->spinBox16, ui->spinBox17, ui->spinBox18, ui->spinBox19, ui->spinBox20, ui->spinBox21,
                ui->spinBox22, ui->spinBox23, ui->spinBox24, ui->spinBox25, ui->spinBox26, ui->spinBox27, ui->spinBox28,
                ui->spinBox29, ui->spinBox30, ui->spinBox31, ui->spinBox32, ui->spinBox33, ui->spinBox34, ui->spinBox35,
                ui->spinBox36, ui->spinBox37, ui->spinBox38, ui->spinBox39, ui->spinBox40, ui->spinBox41, ui->spinBox42};
    ui->buttonBox->setFocus();
}

SpellsDlg::~SpellsDlg()
{
    delete ui;
}
