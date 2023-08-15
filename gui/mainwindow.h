#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>

#include <QComboBox>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>

#include "../belzebubchr.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushBackup_clicked();

    void on_pushGame_clicked();

    void on_pushHand1_clicked();

    void on_pushHand2_clicked();

    void on_pushBody_clicked();

    void on_pushHead_clicked();

    void on_pushBelt_clicked();

    void on_pushRing1_clicked();

    void on_pushRing2_clicked();

    void on_pushAmulet_clicked();

    void on_pushDurability_clicked();

    void on_pushStaffSpell_clicked();

    void on_pushSpells_clicked();

    void on_pushRecipes_clicked();

    void on_combo1_currentIndexChanged(int index);

    void on_combo2_currentIndexChanged(int index);

    void on_combo3_currentIndexChanged(int index);

    void on_combo4_currentIndexChanged(int index);

    void on_combo5_currentIndexChanged(int index);

    void on_combo6_currentIndexChanged(int index);

    void on_combo7_currentIndexChanged(int index);

    void on_combo8_currentIndexChanged(int index);

    void on_combo9_currentIndexChanged(int index);

    void on_pushSave_clicked();

private:
    Ui::MainWindow *ui;
    QSettings *settings;
    QString fileBackup;
    QString fileGame;
    std::vector<QComboBox*> comboVec;
    std::vector<QLabel*> labelVec;
    std::vector<QSpinBox*> spinVec1;
    std::vector<QSpinBox*> spinVec2;
    std::vector<QComboBox*> comboValueVec;
    std::vector<QPushButton*> itemButtons;
    void loadSettings();
    void saveSettings();
    void activateButton(QPushButton *pushButton);
    void clearGuiData();
    void updateGuiLine(const int i, const int value1 = Belzebub::ValueOff, const int value2 = Belzebub::ValueOff);
    void loadChrFile();


    BelzebubChr belzebubChr;
    Belzebub::ItemPosition currentItemPosition;
    void updateItem(const Belzebub::ItemPosition itemPosition);
    void updateItemData();

};
#endif // MAINWINDOW_H
