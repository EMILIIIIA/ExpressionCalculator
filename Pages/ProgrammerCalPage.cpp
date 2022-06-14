#include "ProgrammerCalPage.h"
#include "ui_ProgrammerCalPage.h"

#include "CalEngine/ExpressionCalculation/ProgrammerExpressionCalculation.h"

ProgrammerCalPage::ProgrammerCalPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProgrammerCalPage)
{
    ui->setupUi(this);
}

ProgrammerCalPage::~ProgrammerCalPage()
{
    delete ui;
}

void ProgrammerCalPage::on_pushButton_clicked()
{
    CalEngine::ProgrammerExpressionCalculation a("2147483647*2","");
    CalEngine::ProgrammerExpressionCalculation b("2147483647*2","");
    int32_t success=0;
    //ui->label->setText(ui->label->text()+a.startCalculate(&success)+b.startCalculate(&success));
}

