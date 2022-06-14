#include "MainDisplayLineEdit.h"
#include <QRegularExpressionValidator>


MainDisplayLineEdit::MainDisplayLineEdit(QWidget* parent)
{
    this->setValidator(new QRegularExpressionValidator(QRegularExpression(R"(^([0-9\+\-\*\/×÷\(\)\!\,.]|[a-z])*$)")));
    //^([0-9\+\-\*\/×÷\(\)\!\,.]|sqrt|ln|log|sin|cos|tan|cot|sec|csc|arc)*$

    this->setText("0");//初始化

    //connect(this, SIGNAL(textChanged(QString)), this, SLOT(on_linedit_textchanged(QString)));
    connect(this, SIGNAL(textEdited(QString)), this, SLOT(on_linedit_textedited(QString)));


    mDispFont.setFamily("Microsoft Yahei");
    //dispFont.setFamily("Arial");
    mDispFont.setPointSize(32);
    //dispFont.setBold(true);
    mDispFont.setStyleStrategy(QFont::PreferAntialias);
    mIsEmptyExp=true;
}


QString MainDisplayLineEdit::getExpression()
{
    QString expression=this->text();
    expression.replace("÷", "/").replace("×", "*");
    return expression;
}

void MainDisplayLineEdit::setExpression(const QString &inputExp)
{
    this->setText(inputExp);
    changeTextToFormat();
}


void MainDisplayLineEdit::removeExpression(const int32_t pos,const int32_t n)
{
    QString expression=this->text();
    expression.remove(pos,n);
    this->setText(expression);
    changeTextToFormat();
}
void MainDisplayLineEdit::appendExpression(const QString &willappend)
{
    QString expression=this->text();
    expression.append(willappend);
    this->setText(expression);
    changeTextToFormat();
}

void MainDisplayLineEdit::insertExpression(const QString &willappend, const int32_t pos)
{
    QString expression=this->text();
    expression.insert(pos,willappend);
    this->setText(expression);
    changeTextToFormat();
}
void MainDisplayLineEdit::chopExpression(unsigned int par)
{
    QString expression=this->text();
    expression.chop(par);
    this->setText(expression);
    changeTextToFormat();
}

void MainDisplayLineEdit::clearExpression()
{
    this->clear();
    changeTextToFormat();
}

void MainDisplayLineEdit::on_linedit_textedited(QString str)
{
    changeTextToFormat();
}


void MainDisplayLineEdit::changeTextToFormat()
{

    //删除错误提示
    if(mHasError==true)
    {
        this->setReadOnly(false);
        QString temstr;
        for(const QChar &i:this->text())
        {
            if(i.isNumber() || i.isSymbol() || i.isLower() || i.isMark() || i.isPunct())
                temstr.append(i);
        }
        this->setText(temstr);
        mHasError=false;
    }

    //删除默认显示的零
    if(mIsEmptyExp==true)
    {
        this->setText(this->text().remove(0,1));
        mIsEmptyExp=false;
    }

    //处理没有表达式时候的默认字符
    if(this->text().isEmpty() || this->text()=="0")
    {
        this->setText("0");
        mIsEmptyExp=true;
    }

    //qDebug()<<this->text();
    QString willupdate=this->text();
    willupdate.replace('/', "÷").replace('*', "×");

    //记录箭头位置好还原
    auto cursorPos=this->cursorPosition();
    //处理空白加零和字体宽度自适应

    int displayLen=this->width()-10;

    //dispFont.setBold(true);

    for(int i=32;i>=2;i--)
    {
        mDispFont.setPointSize(i);
        QFontMetrics fm(mDispFont);
        int pixelWid=fm.horizontalAdvance(willupdate);
        if(displayLen>pixelWid)
            break;
    }
    this->setFont(mDispFont);
    //处理字符
    this->setText(willupdate);
    //还原箭头位置
    this->setCursorPosition(cursorPos);
}

void MainDisplayLineEdit::setError(const QString &inputExp)
{
    this->setText(inputExp);
    this->setReadOnly(true);
    mHasError=true;
}

bool MainDisplayLineEdit::getHasError()
{
    return mHasError;
}
