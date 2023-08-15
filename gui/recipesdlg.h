#ifndef RECIPESDLG_H
#define RECIPESDLG_H

#include <QDialog>

#include <vector>
#include <QList>

namespace Ui {
class RecipesDlg;
}

class RecipesDlg : public QDialog
{
    Q_OBJECT

public:
    explicit RecipesDlg(const std::vector<int> &recipes, QWidget *parent = nullptr);
    ~RecipesDlg();
    QList<int> recipesOn;

private slots:
    void on_buttonBox_accepted();

    void on_pushCheckAll_clicked();

    void on_pushUncheckAll_clicked();

private:
    Ui::RecipesDlg *ui;
};

#endif // RECIPESDLG_H
