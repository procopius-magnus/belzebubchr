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
    void on_pushLoad_clicked();

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

private:
    Ui::MainWindow *ui;
    QSettings *settings;
    QString fileName;
    QString fileDir;
    QString fileBackup;
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
    void loadChrFile();


    BelzebubChr belzebubChr;
    Belzebub::ItemPosition currentItemPosition;
    void updateItem(const Belzebub::ItemPosition itemPosition);

};
#endif // MAINWINDOW_H
