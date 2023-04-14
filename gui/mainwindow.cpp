#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QInputDialog>
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
    fileName = settings->value("main/fileName", fileName).toString();
    fileDir = settings->value("main/fileDir", fileDir).toString();
    fileBackup = settings->value("main/fileBackup", fileBackup).toString();
    ui->checkBackup->setChecked(settings->value("main/fileBackupCheck", true).toBool());
    ui->labelCurrentFile->setText(fileName);
    ui->checkBackup->setText("Backup files to this folder: " + fileBackup);
}

void MainWindow::saveSettings()
{
    settings->setValue("main/geometry", saveGeometry());
    settings->setValue("main/fileName", fileName);
    settings->setValue("main/fileDir", fileDir);
    settings->setValue("main/fileBackup", fileBackup);
    settings->setValue("main/fileBackupCheck", ui->checkBackup->isChecked());
    settings->sync();
}

void MainWindow::on_pushLoad_clicked()
{
    QString newFileName = QFileDialog::getOpenFileName(this, "Open File", fileDir, "Saves (*.chr)");
    if (newFileName.isEmpty()) {
        return;
    }
    ui->labelCurrentFile->setText(newFileName);
    fileName = newFileName;
    QFileInfo fileInfo(fileName);
    fileDir = fileInfo.absolutePath();
    fileBackup = fileDir;
    if (!fileBackup.endsWith('/')) {
        fileBackup += "/";
    }
    fileBackup += "chr_backup/";
    ui->checkBackup->setText("Backup files to this folder: " + fileBackup);
    saveSettings();

    loadChrFile();
}

void MainWindow::loadChrFile()
{
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
    if (!belzebubChr.loadBuffer1(fileName.toStdString())) {
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

void MainWindow::updateItem(const Belzebub::ItemPosition itemPosition)
{
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

    const Belzebub::ItemType &itemType = belzebubChr.getItemType(currentItemPosition);
    ui->labelItemType->setText(QString::number(itemType.number) + "  " + QString::fromStdString(itemType.name));

    if (itemType.type == Belzebub::ItemHelperType::Staff) {
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
        comboBox->clear();
        comboBox->setEditable(true);
        comboBox->lineEdit()->setReadOnly(true);
        comboBox->lineEdit()->setAlignment(Qt::AlignRight);
        if (attributeValue.isUnknown) {
            comboBox->addItem("unknown attribute");
            comboBox->setItemData(comboBox->count() - 1, Qt::AlignLeft, Qt::TextAlignmentRole);
        }
        int selected = -1;
        {
            comboBox->addItem("unused attribute");
            comboBox->setItemData(comboBox->count() - 1, Qt::AlignLeft, Qt::TextAlignmentRole);
            if (attributeValue.isNotUsed) {
                selected = comboBox->count() - 1;
            }
        }
        std::vector<Belzebub::AttributeData> attributes = belzebubChr.getAttributes(attributeMode);
        for (size_t j = 0; j < attributes.size(); ++j) {
            const Belzebub::AttributeData &attributeData = attributes[j];
            comboBox->addItem(QString::fromStdString(attributeData.name));
            comboBox->setItemData(comboBox->count() - 1, Qt::AlignLeft, Qt::TextAlignmentRole);
            if (attributeData.start == attributeValue.attributeData.start) {
                selected = comboBox->count() - 1;
            }
        }
        if (selected != -1) {
            comboBox->setCurrentIndex(selected);
        }
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
