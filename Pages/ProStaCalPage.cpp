#include "ProStaCalPage.h"
#include "ui_ProStaCalPage.h"

ProStaCalPage::ProStaCalPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProStaCalPage)
{
    ui->setupUi(this);
    ui->lineEdit->cursorPosition();
}

ProStaCalPage::~ProStaCalPage()
{
    delete ui;
}
