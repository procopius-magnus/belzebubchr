#include "recipesdlg.h"
#include "ui_recipesdlg.h"

#include "../recipe.h"
using namespace Belzebub;

RecipesDlg::RecipesDlg(const std::vector<int> &recipes, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RecipesDlg)
{
    ui->setupUi(this);
    for (const int position : recipes) {
        recipesOn.append(position);
    }
    for (int i = (int)RecipeType::TransmuteRegularGem; i < (int)RecipeType::End; ++i) {
        QString str = QString::number(i);
        if (recipeNames.count((RecipeType)i) == 1) {
            str = QString::fromStdString(recipeNames.at((RecipeType)i));
        }
        QListWidgetItem *item = new QListWidgetItem(str);
        item->setCheckState(recipesOn.contains(i) ? Qt::Checked : Qt::Unchecked);
        item->setData(Qt::UserRole, i);
        ui->listWidget->addItem(item);
    }
}

RecipesDlg::~RecipesDlg()
{
    delete ui;
}

void RecipesDlg::on_buttonBox_accepted()
{
    recipesOn.clear();
    for (int i = 0; i < ui->listWidget->count(); ++i) {
        if (ui->listWidget->item(i)->checkState() == Qt::Checked) {
            recipesOn.append(ui->listWidget->item(i)->data(Qt::UserRole).toInt());
        }
        else {
            recipesOn.append(-ui->listWidget->item(i)->data(Qt::UserRole).toInt());
        }
    }
}


void RecipesDlg::on_pushCheckAll_clicked()
{
    for (int i = 0; i < ui->listWidget->count(); ++i) {
        ui->listWidget->item(i)->setCheckState(Qt::Checked);
    }
}


void RecipesDlg::on_pushUncheckAll_clicked()
{
    for (int i = 0; i < ui->listWidget->count(); ++i) {
        ui->listWidget->item(i)->setCheckState(Qt::Unchecked);
    }
}

