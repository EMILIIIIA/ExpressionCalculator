#include "FunctionChooseBar.h"
#include "ui_FunctionChooseBar.h"
#include <QPropertyAnimation>
#include <QTimer>
FunctionChooseBar::FunctionChooseBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FunctionChooseBar)
{
    ui->setupUi(this);
}

FunctionChooseBar::~FunctionChooseBar()
{
    delete openAnimation;
    delete closeAnimation;
    delete ui;
}

void FunctionChooseBar::showOpenAnimation()
{
    ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);//解决残留滚动条bug
    int targetWidth=this->rect().width()+100, targetHight=this->rect().height();
    openAnimation->setParent(this);
    openAnimation->setDuration(200);
    openAnimation->setEasingCurve(QEasingCurve::InQuad);
    openAnimation->setStartValue(QRect(1, 32,0,targetHight));
    openAnimation->setEndValue(QRect(1,32, targetWidth, targetHight));
    openAnimation->start();
    //动画指针在调用完成后会自动删除
}

void FunctionChooseBar::showCloseAnimation()
{
    ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//解决残留滚动条bug
    int targetWidth=this->rect().width()+100, targetHight=this->rect().height();
    closeAnimation->setParent(this);
    closeAnimation->setDuration(200);
    closeAnimation->setEasingCurve(QEasingCurve::InQuad);
    closeAnimation->setStartValue(QRect(1, 32,targetWidth,targetHight));
    closeAnimation->setEndValue(QRect(1,32, 0, targetHight));
    closeAnimation->start();
    //因为动画还未完成，所以不能直接杀掉子窗口进程
    QTimer::singleShot(250, this,[=]() {this->close();});//方法一，延迟结束
    //方法二，使用动画结束后自动发送的信号QAbstractAnimation::finished()与自定义槽
}


void FunctionChooseBar::on_normalButton_clicked()
{
    emit emitSelectedModes(0);
    showCloseAnimation();
}


void FunctionChooseBar::on_scienceButton_clicked()
{
    emit emitSelectedModes(1);
    showCloseAnimation();
}


void FunctionChooseBar::on_programmerButton_clicked()
{
    emit emitSelectedModes(2);
    showCloseAnimation();
}


void FunctionChooseBar::on_randomPageButton_clicked()
{
    emit emitSelectedModes(3);
    showCloseAnimation();
}

