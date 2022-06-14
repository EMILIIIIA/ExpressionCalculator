#include "ScienceCalPage.h"
#include "ui_ScienceCalPage.h"
#include "CalEngine/ExpressionCalculation/ScienceExpressionCalculation.h"
#include "CalEngine/CalException.h"
#include "MainWindow.h"

#include<QTimer>
using CalEngine::ScienceExpressionCalculation;
using CalEngine::CalException;
using CalEngine::ErrorName;

ScienceCalPage::ScienceCalPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScienceCalPage)
{
    ui->setupUi(this);

    //connect(this, SIGNAL(updateHistoryPage(QString)),this->window(), SLOT(updateHistoryPage(QString)) );

    connect(ui->num0, &QPushButton::clicked, [=](){
        int32_t pos=ui->displayCur->cursorPosition();
        ui->displayCur->insertExpression("0",pos);
        ui->displayCur->setFocus();
        ui->displayCur->setCursorPosition(pos+1);});

    connect(ui->num1, &QPushButton::clicked, [=](){
        int32_t pos=ui->displayCur->cursorPosition();
        ui->displayCur->insertExpression("1",pos);
        ui->displayCur->setFocus();
        ui->displayCur->setCursorPosition(pos+1);});

    connect(ui->num2, &QPushButton::clicked, [=](){
        int32_t pos=ui->displayCur->cursorPosition();
        ui->displayCur->insertExpression("2",pos);
        ui->displayCur->setFocus();
        ui->displayCur->setCursorPosition(pos+1);});

    connect(ui->num3, &QPushButton::clicked, [=](){
        int32_t pos=ui->displayCur->cursorPosition();
        ui->displayCur->insertExpression("3",pos);
        ui->displayCur->setFocus();
        ui->displayCur->setCursorPosition(pos+1);});

    connect(ui->num4, &QPushButton::clicked, [=](){
        int32_t pos=ui->displayCur->cursorPosition();
        ui->displayCur->insertExpression("4",pos);
        ui->displayCur->setFocus();
        ui->displayCur->setCursorPosition(pos+1);});

    connect(ui->num5, &QPushButton::clicked, [=](){
        int32_t pos=ui->displayCur->cursorPosition();
        ui->displayCur->insertExpression("5",pos);
        ui->displayCur->setFocus();
        ui->displayCur->setCursorPosition(pos+1);});

    connect(ui->num6, &QPushButton::clicked, [=](){
        int32_t pos=ui->displayCur->cursorPosition();
        ui->displayCur->insertExpression("6",pos);
        ui->displayCur->setFocus();
        ui->displayCur->setCursorPosition(pos+1);});

    connect(ui->num7, &QPushButton::clicked, [=](){
        int32_t pos=ui->displayCur->cursorPosition();
        ui->displayCur->insertExpression("7",pos);
        ui->displayCur->setFocus();
        ui->displayCur->setCursorPosition(pos+1);});

    connect(ui->num8, &QPushButton::clicked, [=](){
        int32_t pos=ui->displayCur->cursorPosition();
        ui->displayCur->insertExpression("8",pos);
        ui->displayCur->setFocus();
        ui->displayCur->setCursorPosition(pos+1);});

    connect(ui->num9, &QPushButton::clicked, [=](){
        int32_t pos=ui->displayCur->cursorPosition();
        ui->displayCur->insertExpression("9",pos);
        ui->displayCur->setFocus();
        ui->displayCur->setCursorPosition(pos+1);});



    connect(ui->bckSpace, &QPushButton::clicked, [=](){
        int32_t pos=ui->displayCur->cursorPosition();
        ui->displayCur->removeExpression(pos-1,1);
        ui->displayCur->setFocus();
        ui->displayCur->setCursorPosition(pos);});

    connect(ui->opAdd, &QPushButton::clicked, [=](){
        int32_t pos=ui->displayCur->cursorPosition();
        ui->displayCur->insertExpression("+",pos);
        ui->displayCur->setFocus();
        ui->displayCur->setCursorPosition(pos+1);});

    connect(ui->opSub, &QPushButton::clicked, [=](){
        int32_t pos=ui->displayCur->cursorPosition();
        ui->displayCur->insertExpression("-",pos);
        ui->displayCur->setFocus();
        ui->displayCur->setCursorPosition(pos+1);});

    connect(ui->opMulti, &QPushButton::clicked, [=](){
        int32_t pos=ui->displayCur->cursorPosition();
        ui->displayCur->insertExpression("*",pos);
        ui->displayCur->setFocus();
        ui->displayCur->setCursorPosition(pos+1);});

    connect(ui->opDiv, &QPushButton::clicked, [=](){
        int32_t pos=ui->displayCur->cursorPosition();
        ui->displayCur->insertExpression("/",pos);
        ui->displayCur->setFocus();
        ui->displayCur->setCursorPosition(pos+1);});

    connect(ui->opBrckL, &QPushButton::clicked, [=](){
        int32_t pos=ui->displayCur->cursorPosition();
        ui->displayCur->insertExpression("(",pos);
        ui->displayCur->setFocus();
        ui->displayCur->setCursorPosition(pos+1);});

    connect(ui->opBrckR, &QPushButton::clicked, [=](){
        int32_t pos=ui->displayCur->cursorPosition();
        ui->displayCur->insertExpression(")",pos);
        ui->displayCur->setFocus();
        ui->displayCur->setCursorPosition(pos+1);});

    connect(ui->opDot, &QPushButton::clicked, [=](){
        int32_t pos=ui->displayCur->cursorPosition();
        ui->displayCur->insertExpression(".",pos);
        ui->displayCur->setFocus();
        ui->displayCur->setCursorPosition(pos+1);});

    connect(ui->opMod, &QPushButton::clicked, [=](){
        int32_t pos=ui->displayCur->cursorPosition();
        ui->displayCur->insertExpression("%",pos);
        ui->displayCur->setFocus();
        ui->displayCur->setCursorPosition(pos+1);});

    connect(ui->opFact, &QPushButton::clicked, [=](){
        int32_t pos=ui->displayCur->cursorPosition();
        ui->displayCur->insertExpression("!",pos);
        ui->displayCur->setFocus();
        ui->displayCur->setCursorPosition(pos+1);});


    connect(ui->opClear, &QPushButton::clicked, [=](){ui->displayCur->clearExpression();});
    connect(ui->opEqual, &QPushButton::clicked, [=](){calResult();});

    connect(ui->opPow, &QPushButton::clicked, [=](){
        int32_t pos=ui->displayCur->cursorPosition();
        ui->displayCur->insertExpression("pow(,)",pos);
        ui->displayCur->setFocus();
        ui->displayCur->setCursorPosition(pos+4);});

    connect(ui->opSqrt, &QPushButton::clicked, [=](){
        int32_t pos=ui->displayCur->cursorPosition();
        ui->displayCur->insertExpression("sqrt(,)",pos);
        ui->displayCur->setFocus();
        ui->displayCur->setCursorPosition(pos+5);});

    connect(ui->opLog, &QPushButton::clicked, [=](){
        int32_t pos=ui->displayCur->cursorPosition();
        ui->displayCur->insertExpression("log(,)",pos);
        ui->displayCur->setFocus();
        ui->displayCur->setCursorPosition(pos+4);});

    connect(ui->opLn, &QPushButton::clicked, [=](){
        int32_t pos=ui->displayCur->cursorPosition();
        ui->displayCur->insertExpression("ln()",pos);
        ui->displayCur->setFocus();
        ui->displayCur->setCursorPosition(pos+3);});

    connect(ui->opPi, &QPushButton::clicked, [=](){
        int32_t pos=ui->displayCur->cursorPosition();
        ui->displayCur->insertExpression("π",pos);
        ui->displayCur->setFocus();
        ui->displayCur->setCursorPosition(pos+1);});

    connect(ui->opE, &QPushButton::clicked, [=](){
        int32_t pos=ui->displayCur->cursorPosition();
        ui->displayCur->insertExpression("e",pos);
        ui->displayCur->setFocus();
        ui->displayCur->setCursorPosition(pos+1);});

    QTimer::singleShot(100,this, [=]() {connect(this,SIGNAL(updateHistoryPage(QString)),this->window(),SLOT(updateHistoryPage(QString)));});//连接历史窗口
}

ScienceCalPage::~ScienceCalPage()
{
    delete ui;
}

void ScienceCalPage::calResult()
{
    if(ui->displayCur->getHasError()==true)
    {
        return;
    }
    updateHisLabel(ui->displayCur->getExpression());//上传历史记录
    QString equation=ui->displayHis->text();
    ScienceExpressionCalculation calengine(ui->displayCur->getExpression());
    int32_t isSuccessful=false;

    QString res="";
    try
    {
        res=calengine.startCalculate(&isSuccessful);
        ui->displayCur->setExpression(res);
    }
    catch (CalException &exp)
    {
        if(exp.getErrorName()==ErrorName::CalBracketError)
        {
            ui->displayCur->setError("括号匹配错误");
        }
        else if(exp.getErrorName()==ErrorName::CalOperatorError)
        {
            ui->displayCur->setError("运算符错误");
        }
        else if(exp.getErrorName()==ErrorName::CalParameterError)
        {
            ui->displayCur->setError("参数错误");
        }
        else if(exp.getErrorName()==ErrorName::CalSyntaxError)
        {
            ui->displayCur->setError("语法错误");
        }
        else
        {
            ui->displayCur->setError("未知错误");
        }

    }


    emit updateHistoryPage(equation+ui->displayCur->text());
}


void ScienceCalPage::updateHisLabel(QString willupdate)
{
    //字符串内容处理
    if(willupdate.isEmpty()==true)
        willupdate.append("0");
    willupdate=willupdate.replace('/', "÷").replace('*', "×").append("=");

    int displayLen=ui->displayHis->width()-10;
    QFont dispFont("Microsoft Yahei",32);
    dispFont.setStyleStrategy(QFont::PreferAntialias);
    for(int i=16;i>=1;i--)
    {
        dispFont.setPointSize(i);
        QFontMetrics fm(dispFont);
        int pixelWid=fm.horizontalAdvance(willupdate);
        if(displayLen>pixelWid)
            break;
    }
    ui->displayHis->setFont(dispFont);
    ui->displayHis->setText(willupdate);
    ui->displayHis->setStyleSheet("color: rgb(70, 70, 70);");
}



void ScienceCalPage::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_0:
        ui->displayCur->appendExpression("0");
        break;
    case Qt::Key_1:
        ui->displayCur->appendExpression("1");
        break;
    case Qt::Key_2:
        ui->displayCur->appendExpression("2");
        break;
    case Qt::Key_3:
        ui->displayCur->appendExpression("3");
        break;
    case Qt::Key_4:
        ui->displayCur->appendExpression("4");
        break;
    case Qt::Key_5:
        ui->displayCur->appendExpression("5");
        break;
    case Qt::Key_6:
        ui->displayCur->appendExpression("6");
        break;
    case Qt::Key_7:
        ui->displayCur->appendExpression("7");
        break;
    case Qt::Key_8:
        ui->displayCur->appendExpression("8");
        break;
    case Qt::Key_9:
        ui->displayCur->appendExpression("9");
        break;
    case Qt::Key_ParenLeft:
        ui->displayCur->appendExpression("(");
        break;
    case Qt::Key_ParenRight:
        ui->displayCur->appendExpression(")");
        break;
    case Qt::Key_Percent:
        ui->displayCur->appendExpression("%");
        break;
    case Qt::Key_AsciiCircum:
        ui->displayCur->appendExpression("^2");
        break;
    case Qt::Key_Plus:
        ui->displayCur->appendExpression("+");
        break;
    case Qt::Key_Minus :
        ui->displayCur->appendExpression("-");
        break;
    case Qt::Key_Asterisk:
        ui->displayCur->appendExpression("*");
        break;
    case Qt::Key_Slash:
        ui->displayCur->appendExpression("/");
        break;
    case Qt::Key_Period:
        ui->displayCur->appendExpression(".");
        break;
    case Qt::Key_Backspace:
        ui->displayCur->chopExpression(1);
        break;
    case Qt::Key_Delete:
        ui->displayCur->clearExpression();
        break;

    case Qt::Key_Enter:
        //两者都是回车键
    case Qt::Key_Return:
        calResult();

        break;

    }
}


//当widget大小改变时自动调用更新当前字符宽度
void ScienceCalPage::resizeEvent(QResizeEvent *event)
{
    ui->displayCur->changeTextToFormat();
}
