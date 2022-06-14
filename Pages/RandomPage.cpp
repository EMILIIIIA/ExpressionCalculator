#include "RandomPage.h"
#include "ui_RandomPage.h"
#include "CalEngine/RandomProducer.h"
#include <QRegularExpressionValidator>
#include <QMessageBox>

using CalEngine::AbstractRandomProducer;
using CalEngine::randomInterface;

RandomPage::RandomPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RandomPage)
{
    ui->setupUi(this);
    ui->MaxmumEdit->setValidator(new QRegularExpressionValidator(QRegularExpression(R"((^\d{0,9})|(4294967295)$)")));
    ui->MinimumEdit->setValidator(new QRegularExpressionValidator(QRegularExpression(R"((^\d{0,9})|(4294967295)$)")));
}

RandomPage::~RandomPage()
{
    delete ui;
}

void RandomPage::on_RanC98button_clicked()
{
    randomInterface thisinterface(AbstractRandomProducer::C98Rand);
    uint32_t minNum=(ui->MinimumEdit->text()).toUInt(),maxNum=(ui->MaxmumEdit->text()).toUInt();
    QString ranRes;
    if(minNum>maxNum)
        ui->RanDisplayCur->setText("参数错误");
    else
        ranRes=QString::number(thisinterface.getRandom(minNum,maxNum));
    //qDebug()<<thisinterface.getRandom(0,10000);
    updateCurrent(ranRes);
    updateHistory(ranRes);
}


void RandomPage::on_RanC11button_clicked()
{
    randomInterface thisinterface(AbstractRandomProducer::C11Rand);
    uint32_t minNum=(ui->MinimumEdit->text()).toUInt(),maxNum=(ui->MaxmumEdit->text()).toUInt();
    QString ranRes;
    if(minNum>maxNum)
        ui->RanDisplayCur->setText("参数错误");
    else
        ranRes=QString::number(thisinterface.getRandom(minNum,maxNum));
    //qDebug()<<thisinterface.getRandom(0,10000);
    updateCurrent(ranRes);
    updateHistory(ranRes);
}


void RandomPage::on_RanCPUbutton_clicked()
{
    randomInterface thisinterface(AbstractRandomProducer::CPURand);
    uint32_t minNum=(ui->MinimumEdit->text()).toUInt(),maxNum=(ui->MaxmumEdit->text()).toUInt();
    QString ranRes;
    if(minNum>maxNum)
        ui->RanDisplayCur->setText("参数错误");
    else
    {
        try {
            ranRes=QString::number(thisinterface.getRandom(minNum,maxNum));
        }
        catch (QString errorEspression){
            if(errorEspression=="cpu not support")
            QMessageBox::warning(NULL,"错误","当前CPU不支持RDRAND指令");
            return;
        }
    }
    //qDebug()<<thisinterface.getRandom(0,10000);
    updateCurrent(ranRes);
    updateHistory(ranRes);
}
void RandomPage::updateCurrent(QString willupdate)
{
    ui->RanDisplayHis->setText(ui->RanDisplayCur->text());
    ui->RanDisplayCur->setText(willupdate);
}

void RandomPage::updateHistory(QString willupdate)
{
   // ui->HisBrowser->append(willupdate);

}
