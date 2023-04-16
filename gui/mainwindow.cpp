#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "spellsdlg.h"

#include <QFileDialog>
#include <QInputDialog>
#include <QDateTime>
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    labelVec = {ui->label1, ui->label2, ui->label3, ui->label4, ui->label5, ui->label6, ui->label7, ui->label8, ui->label9};
    comboVec = {ui->combo1, ui->combo2, ui->combo3, ui->combo4, ui->combo5, ui->combo6, ui->combo7, ui->combo8, ui->combo9};
    spinVec1 = {ui->spin11, ui->spin21, ui->spin31, ui->spin41, ui->spin51, ui->spin61, ui->spin71, ui->spin81, ui->spin91};
    spinVec2 = {ui->spin12, ui->spin22, ui->spin32, ui->spin42, ui->spin52, ui->spin62, ui->spin72, ui->spin82, ui->spin92};
    comboValueVec = {ui->comboValue1, ui->comboValue2, ui->comboValue3, ui->comboValue4, ui->comboValue5, ui->comboValue6, ui->comboValue7, ui->comboValue8, ui->comboValue9};
    itemButtons = {ui->pushBody, ui->pushHead, ui->pushRing1, ui->pushRing2, ui->pushAmulet, ui->pushHand1, ui->pushHand2, ui->pushBelt};
    settings = new QSettings("procopius.magnus", "BelzebubChr");
    loadSettings();
    loadChrFile();
}

MainWindow::~MainWindow()
{
    saveSettings();
    delete settings;
    delete ui;
}

void MainWindow::loadSettings()
{
    restoreGeometry(settings->value("main/geometry").toByteArray());
    fileBackup = settings->value("main/fileBackup", fileBackup).toString();
    fileGame = settings->value("main/fileGame", fileGame).toString();
    ui->labelBackupFile->setText(fileBackup);
    ui->labelGameFile->setText(fileGame);
}

void MainWindow::saveSettings()
{
    settings->setValue("main/geometry", saveGeometry());
    settings->setValue("main/fileBackup", fileBackup);
    settings->setValue("main/fileGame", fileGame);
    settings->sync();
}


void MainWindow::on_pushBackup_clicked()
{
    QFileInfo fileInfo(fileBackup);
    QString newFileName = QFileDialog::getOpenFileName(this, "Open File", fileInfo.absolutePath(), "Saves (*.chr)");
    if (newFileName.isEmpty()) {
        return;
    }
    fileBackup = newFileName;
    ui->labelBackupFile->setText(fileBackup);
    saveSettings();

    loadChrFile();
}


void MainWindow::on_pushGame_clicked()
{
    QFileInfo fileInfo(fileGame);
    QString newFileName = QFileDialog::getOpenFileName(this, "Open File", fileInfo.absolutePath(), "Saves (*.chr)");
    if (newFileName.isEmpty()) {
        return;
    }
    fileGame = newFileName;
    ui->labelGameFile->setText(fileGame);
    saveSettings();
}

void MainWindow::loadChrFile()
{
    ui->pushSpells->setEnabled(false);
    ui->pushBody->setEnabled(false);
    ui->pushHead->setEnabled(false);
    ui->pushRing1->setEnabled(false);
    ui->pushRing2->setEnabled(false);
    ui->pushAmulet->setEnabled(false);
    ui->pushHand1->setEnabled(false);
    ui->pushHand2->setEnabled(false);
    ui->pushBelt->setEnabled(false);
    clearGuiData();

    belzebubChr = BelzebubChr();
    if (!belzebubChr.loadBuffer1(fileBackup.toStdString())) {
        return;
    }

    ui->pushSpells->setEnabled(true);
    ui->pushBody->setEnabled(belzebubChr.isBody());
    ui->pushHead->setEnabled(belzebubChr.isHead());
    ui->pushRing1->setEnabled(belzebubChr.isRing1());
    ui->pushRing2->setEnabled(belzebubChr.isRing2());
    ui->pushAmulet->setEnabled(belzebubChr.isAmulet());
    ui->pushHand1->setEnabled(belzebubChr.isHand1());
    ui->pushHand2->setEnabled(belzebubChr.isHand2());
    ui->pushBelt->setEnabled(belzebubChr.isBelt());

    if (belzebubChr.isHand1()) {
        on_pushHand1_clicked();
    }
    else if (belzebubChr.isHand2()) {
        on_pushHand2_clicked();
    }
    else if (belzebubChr.isBody()) {
        on_pushBody_clicked();
    }
    else if (belzebubChr.isHead()) {
        on_pushHead_clicked();
    }
    else if (belzebubChr.isBelt()) {
        on_pushBelt_clicked();
    }
    else if (belzebubChr.isRing1()) {
        on_pushRing1_clicked();
    }
    else if (belzebubChr.isRing2()) {
        on_pushRing2_clicked();
    }
    else if (belzebubChr.isAmulet()) {
        on_pushAmulet_clicked();
    }
}

void MainWindow::on_pushDurability_clicked()
{
    bool ok;
    int durability = QInputDialog::getInt(this, "Durability", "Maximum Durability: ", belzebubChr.getItemDurability(currentItemPosition), 1, 250, 1, &ok);
    if (ok) {
        belzebubChr.setItemDurability(currentItemPosition, durability);
        ui->labelDurability->setText(QString::number(belzebubChr.getItemDurability(currentItemPosition)));
    }
}

void MainWindow::on_pushStaffSpell_clicked()
{
    bool ok;
    QStringList spellItems;
    std::map<std::string, Belzebub::SpellType> stringToIndex;
    int spellIndex = 0;
    for (auto &it : Belzebub::spellNames) {
        stringToIndex[it.second] = it.first;
        spellItems.append(QString::fromStdString(it.second));
        if (belzebubChr.getStaffSpell(currentItemPosition) == it.first) {
            spellIndex = spellItems.count() - 1;
        }
    }
    QString spellStr = QInputDialog::getItem(this, "Staff Spell", "Spell: ", spellItems, spellIndex, false, &ok);
    if (!ok) {
        return;
    }
    int charges = QInputDialog::getInt(this, "Staff Charges", "Maximum Charges: ", belzebubChr.getStaffCharges(currentItemPosition), 1, 32000, 1, &ok);
    if (!ok) {
        return;
    }
    if (stringToIndex[spellStr.toStdString()] == Belzebub::SpellType::NoSpell) {
        charges = 0;
    }
    belzebubChr.setStaffSpell(stringToIndex[spellStr.toStdString()], charges);
    if (belzebubChr.getStaffCharges(currentItemPosition) != 0) {
        ui->labelStaffSpell->setText(QString::fromStdString(Belzebub::spellNames.at(belzebubChr.getStaffSpell(currentItemPosition))) + " (" + QString::number(belzebubChr.getStaffCharges(currentItemPosition)) + ")");
    }
}

void MainWindow::activateButton(QPushButton *pushButton)
{
    QFont font(pushButton->font());
    font.setUnderline(true);
    pushButton->setFont(font);
}

void MainWindow::clearGuiData()
{
    for (size_t i = 0; i < labelVec.size(); ++i) {
        labelVec[i]->hide();
        comboVec[i]->hide();
        spinVec1[i]->hide();
        spinVec2[i]->hide();
        comboValueVec[i]->hide();
    }

    for (QPushButton *pushButton : itemButtons) {
        QFont font(pushButton->font());
        font.setUnderline(false);
        pushButton->setFont(font);
    }

    ui->pushStaffSpell->setEnabled(false);
    ui->labelStaffSpell->clear();

    ui->pushDurability->setEnabled(false);
    ui->labelDurability->clear();
}

void MainWindow::updateGuiLine(const int i, const int value1, const int value2)
{
    const int attributeIndex = comboVec[i]->currentData().toInt();
    QComboBox *comboValue = comboValueVec[i];
    QSpinBox *spinBox1 = spinVec1[i];
    QSpinBox *spinBox2 = spinVec2[i];
    comboValue->hide();
    spinBox1->hide();
    spinBox2->hide();
    if (attributeIndex < 0) {
        return;
    }
    const Belzebub::AttributeData &attributeData = Belzebub::attrMap.at((Belzebub::Attribute)attributeIndex);
    if (attributeData.value1Min == Belzebub::ValueMinus1 || attributeData.value1Min == Belzebub::ValuePlus1) {
        return;
    }
    if (attributeData.value1Min != Belzebub::ValueOff && attributeData.value1Min != Belzebub::ValueSpell) {
        spinBox1->show();
        spinBox1->setMinimum(attributeData.value1Min);
        spinBox1->setMaximum(attributeData.value1Max);
        if (value1 != Belzebub::ValueOff) {
            spinBox1->setValue(value1);
        }
    }
    if (attributeData.value2Min != Belzebub::ValueOff && attributeData.value2Min != Belzebub::ValueSpell) {
        spinBox2->show();
        spinBox2->setMinimum(attributeData.value2Min);
        spinBox2->setMaximum(attributeData.value2Max);
        if (value2 != Belzebub::ValueOff) {
            spinBox2->setValue(value2);
        }
    }
    if (attributeData.value1Min == Belzebub::ValueSpell || attributeData.value2Min == Belzebub::ValueSpell) {
        comboValue->show();
        comboValue->clear();
        int selected = -1;
        for (auto &it : Belzebub::spellNames) {
            comboValue->addItem(QString::fromStdString(it.second), (int)it.first);
            const int spellIndex = attributeData.value1Min == Belzebub::ValueSpell ? value1 : value2;
            if (spellIndex == (int)it.first) {
                selected = comboValue->count() - 1;
            }
        }
        if (selected != -1) {
            comboValue->setCurrentIndex(selected);
        }
    }
}

void MainWindow::updateItem(const Belzebub::ItemPosition itemPosition)
{
    updateItemData();
    clearGuiData();

    currentItemPosition = itemPosition;
    QString itemMagicStr;
    const Belzebub::ItemMagic itemMagic = belzebubChr.getItemMagic(currentItemPosition);
    switch (itemMagic) {
        case Belzebub::ItemMagic::Quest: itemMagicStr = "Quest"; break;
        case Belzebub::ItemMagic::Common: itemMagicStr = "Common"; break;
        case Belzebub::ItemMagic::Magic: itemMagicStr = "Magic"; break;
        case Belzebub::ItemMagic::Rare: itemMagicStr = "Rare"; break;
        case Belzebub::ItemMagic::Unique: itemMagicStr = "Unique"; break;
        case Belzebub::ItemMagic::Set: itemMagicStr = "Set"; break;
        case Belzebub::ItemMagic::Crafted: itemMagicStr = "Crafted"; break;
        case Belzebub::ItemMagic::NoItem: break;
    };
    if (itemMagicStr.isEmpty()) {
        return;
    }
    ui->labelItemMagic->setText(itemMagicStr);
    if (itemMagic == Belzebub::ItemMagic::Quest || itemMagic == Belzebub::ItemMagic::Common) {
        return;
    }

    const Belzebub::ItemType &itemType = belzebubChr.getItemType(currentItemPosition);
    ui->labelItemType->setText(QString::number(itemType.number) + "  " + QString::fromStdString(itemType.name));

    if (itemType.type == Belzebub::ItemHelperType::Staff && (itemMagic == Belzebub::ItemMagic::Magic || itemMagic == Belzebub::ItemMagic::Rare || itemMagic == Belzebub::ItemMagic::Crafted)) {
        ui->pushStaffSpell->setEnabled(true);
    }

    if (belzebubChr.isDurability(currentItemPosition)) {
        ui->pushDurability->setEnabled(true);
        ui->labelDurability->setText(QString::number(belzebubChr.getItemDurability(currentItemPosition)));
    }

    if (belzebubChr.getStaffCharges(currentItemPosition) != 0) {
        ui->labelStaffSpell->setText(QString::fromStdString(Belzebub::spellNames.at(belzebubChr.getStaffSpell(currentItemPosition))) + " (" + QString::number(belzebubChr.getStaffCharges(currentItemPosition)) + ")");
    }

    const int attributeCount = Belzebub::attributeCount.at(itemMagic);
    for (int i = 0; i < attributeCount; ++i) {
        labelVec[i]->show();
        comboVec[i]->show();
        spinVec1[i]->show();
        spinVec2[i]->show();
        comboValueVec[i]->show();

    }

    for (int i = 0; i < attributeCount; ++i) {
        const Belzebub::AttributeValue attributeValue = belzebubChr.getItemAttributeValue(currentItemPosition, i);
        const Belzebub::AttributeMode attributeMode = Belzebub::attributeModeMap.at({itemMagic, i});
        QComboBox *comboBox = comboVec[i];
        comboBox->blockSignals(true);
        comboBox->clear();
        comboBox->setEditable(true);
        comboBox->lineEdit()->setReadOnly(true);
        comboBox->lineEdit()->setAlignment(Qt::AlignRight);
        int selected = -1;
        std::vector<Belzebub::AttributeData> attributes = belzebubChr.getAttributes(attributeMode);
        for (size_t j = 0; j < attributes.size(); ++j) {
            const Belzebub::AttributeData &attributeData = attributes[j];
            comboBox->addItem(QString::fromStdString(attributeData.name), (int)attributeData.attribute);
            comboBox->setItemData(comboBox->count() - 1, Qt::AlignLeft, Qt::TextAlignmentRole);
            if (attributeData.attribute != Belzebub::Attribute::NoAttribute && attributeData.start == attributeValue.attributeData.start) {
                selected = comboBox->count() - 1;
            }
        }
        if (selected != -1) {
            comboBox->setCurrentIndex(selected);
        }
        comboBox->blockSignals(false);

        updateGuiLine(i, attributeValue.value1 , attributeValue.value2);
    }
}

void MainWindow::updateItemData()
{
    static bool isFirst = true;
    if (isFirst) {
        isFirst = false;
        return;
    }
    const Belzebub::ItemMagic itemMagic = belzebubChr.getItemMagic(currentItemPosition);
    const int attributeCount = Belzebub::attributeCount.at(itemMagic);
    for (int i = 0; i < attributeCount; ++i) {
        QComboBox *comboBox = comboVec[i];
        QComboBox *comboValue = comboValueVec[i];
        QSpinBox *spinBox1 = spinVec1[i];
        QSpinBox *spinBox2 = spinVec2[i];
        int value1 = 0;
        int value2 = 0;
        Belzebub::Attribute attributeType = (Belzebub::Attribute)comboBox->currentData().toInt();
        if (attributeType != Belzebub::Attribute::NoAttribute) {
            const Belzebub::AttributeData &attributeData = Belzebub::attrMap.at(attributeType);
            //attributeType = attributeData.start;
            if (attributeData.value1Min != Belzebub::ValueOff && attributeData.value1Min != Belzebub::ValueSpell) {
                value1 = spinBox1->value();
            }
            if (attributeData.value2Min != Belzebub::ValueOff && attributeData.value2Min != Belzebub::ValueSpell) {
                value2 = spinBox2->value();
            }
            if (attributeData.value1Min == Belzebub::ValueSpell) {
                value1 = comboValue->currentData().toInt();
                if (value1 == (int)Belzebub::SpellType::NoSpell) {
                    attributeType = Belzebub::Attribute::NoAttribute;
                }
            }
            else if (attributeData.value2Min == Belzebub::ValueSpell) {
                value2 = comboValue->currentData().toInt();
                if (value2 == (int)Belzebub::SpellType::NoSpell) {
                    attributeType = Belzebub::Attribute::NoAttribute;
                }
            }
        }
        //qDebug() << i << comboBox->currentData().toInt() << attributeType << value1 << value2;
        belzebubChr.setItemAttribute(currentItemPosition, i, attributeType, value1, value2);
    }
}

void MainWindow::on_pushHand1_clicked()
{
    updateItem(Belzebub::ItemPosition::Hand1);
    activateButton(ui->pushHand1);
}

void MainWindow::on_pushHand2_clicked()
{
    updateItem(Belzebub::ItemPosition::Hand2);
    activateButton(ui->pushHand2);
}

void MainWindow::on_pushBody_clicked()
{
    updateItem(Belzebub::ItemPosition::Body);
    activateButton(ui->pushBody);
}

void MainWindow::on_pushHead_clicked()
{
    updateItem(Belzebub::ItemPosition::Head);
    activateButton(ui->pushHead);
}

void MainWindow::on_pushBelt_clicked()
{
    updateItem(Belzebub::ItemPosition::Belt);
    activateButton(ui->pushBelt);
}

void MainWindow::on_pushRing1_clicked()
{
    updateItem(Belzebub::ItemPosition::Ring1);
    activateButton(ui->pushRing1);
}

void MainWindow::on_pushRing2_clicked()
{
    updateItem(Belzebub::ItemPosition::Ring2);
    activateButton(ui->pushRing2);
}

void MainWindow::on_pushAmulet_clicked()
{
    updateItem(Belzebub::ItemPosition::Amulet);
    activateButton(ui->pushAmulet);
}

void MainWindow::on_pushSpells_clicked()
{
    SpellsDlg spellsDlg;
    for (int i = 0; i < 6 * 7; ++i) {
        const Belzebub::SpellType spellType = (Belzebub::SpellType)i;
        if (spellType == Belzebub::SpellType::empty1 || spellType == Belzebub::SpellType::empty2 || spellType == Belzebub::SpellType::empty3 || spellType == Belzebub::SpellType::empty4) {
            spellsDlg.labelVec[i]->hide();
            spellsDlg.spinBoxVec[i]->hide();
            continue;
        }
        spellsDlg.labelVec[i]->setText(QString::fromStdString(Belzebub::spellNames.at(spellType)));
        spellsDlg.spinBoxVec[i]->setValue(belzebubChr.getSpellLevel(spellType));
    }
    if (spellsDlg.exec() == QDialog::Accepted) {
        for (int i = 0; i < 6 * 7; ++i) {
            const Belzebub::SpellType spellType = (Belzebub::SpellType)i;
            if (spellType == Belzebub::SpellType::empty1 || spellType == Belzebub::SpellType::empty2 || spellType == Belzebub::SpellType::empty3 || spellType == Belzebub::SpellType::empty4) {
                continue;
            }
            belzebubChr.setSpellLevel(spellType, spellsDlg.spinBoxVec[i]->value());
        }
    }
}


void MainWindow::on_combo1_currentIndexChanged(int)
{
    updateItemData();
    updateGuiLine(0);
}
void MainWindow::on_combo2_currentIndexChanged(int)
{
    updateItemData();
    updateGuiLine(1);
}
void MainWindow::on_combo3_currentIndexChanged(int)
{
    updateItemData();
    updateGuiLine(2);
}
void MainWindow::on_combo4_currentIndexChanged(int)
{
    updateItemData();
    updateGuiLine(3);
}
void MainWindow::on_combo5_currentIndexChanged(int)
{
    updateItemData();
    updateGuiLine(4);
}
void MainWindow::on_combo6_currentIndexChanged(int)
{
    updateItemData();
    updateGuiLine(5);
}
void MainWindow::on_combo7_currentIndexChanged(int)
{
    updateItemData();
    updateGuiLine(6);
}
void MainWindow::on_combo8_currentIndexChanged(int)
{
    updateItemData();
    updateGuiLine(7);
}
void MainWindow::on_combo9_currentIndexChanged(int)
{
    updateItemData();
    updateGuiLine(8);
}

void MainWindow::on_pushSave_clicked()
{
    updateItemData();
    if (fileBackup.isEmpty() || fileGame.isEmpty() || fileBackup == fileGame) {
        QMessageBox::critical(this, "File Problem", "Backup or game file not set or equal: " + fileBackup + " : " + fileGame);
        return;
    }
    if (belzebubChr.isOk) {
        belzebubChr.saveBuffer(fileGame.toStdString());
        QMessageBox::information(this, "Save File", "Saved.");
    }
    else {
        QMessageBox::information(this, "Save File", "Not saved.");
    }
}
