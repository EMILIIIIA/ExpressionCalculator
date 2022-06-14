#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "PageEngine/WindowsApi.h"
#include "Pages/ScienceCalPage.h"
#include "Pages/RandomPage.h"
#include "Pages/NormalCalPage.h"
#include "Pages/ProgrammerCalPage.h"
#include "CalEngine/CalException.h"

#include <QGraphicsEffect>
#include <QMessageBox>
#include <QKeyEvent>
#include <QTimer>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,mWindowWidth(250)
    ,mWindowHeight(500)
{
    //--------------------------接下来是初始化相关内容--------------------------//
    ui->setupUi(this);
    this->setAttribute(Qt::WA_TranslucentBackground, true);//透明背景
    this->setWindowFlags(Qt::FramelessWindowHint);//无边框窗口
    this->resize(mWindowWidth, mWindowHeight);//窗口大小初始化
    ui->centralwidget->setMouseTracking(true);
    centralWidget()->setMouseTracking(true);//开启鼠标轨迹追踪
    ui->HistoryPage->hide();//隐藏历史记录栏

    // QIcon icon(":/new/prefix/History.png");
    // ui->showHis->setIcon(icon);
    //--------------------------接下来是页面相关内容--------------------------//
    mChooseBarWidget =new FunctionChooseBar; //创建功能选择栏
    mChooseBarWidget->setParent(this);
    // QPoint globalPos1=this->mapToGlobal(QPoint(0,0));
    //chooseBarWidget->move(globalPos1.x()+50,globalPos1.y()+50);
    mChooseBarWidget->hide();

    mPagelist.addCalPage(new NormalCalculatorPage,ui->NormalCal);
    mPagelist.addCalPage(new ScienceCalPage,ui->ScienceCal);
    mPagelist.addCalPage(new ProgrammerCalPage,ui->ProgrammerCal);
    mPagelist.addCalPage(new RandomPage,ui->RandomCal);
    mPagelist.setCalPageFocus(0);

    ui->CalStackedWidget->setCurrentIndex(0);
   // updateFocustoWidget();
    //--------------------------接下来是信号与槽相关内容--------------------------//
    connect(mChooseBarWidget, SIGNAL(emitSelectedModes(int)),this, SLOT(getReturnedMode(int)) ); //接受功能选择结果
    connect(this, SIGNAL(functionChooseBarOpenAnimation() ),mChooseBarWidget, SLOT(showOpenAnimation() ) );//控制动画开启效果
    connect(this, SIGNAL(functionChooseBarCloseAnimation() ),mChooseBarWidget, SLOT(showCloseAnimation() ) );//控制动画结束效果

    //--------------------------接下来是WindowsAPI相关内容--------------------------//
    WindowsApi::RGBColor tempColor;
    try
    {
        tempColor=WindowsApi::getSystemColor(); //通过WindowsAPI获取系统配色
    }
    catch (CalEngine::CalException &exp)
    {
        tempColor={31,206,255};//默认颜色，Windows10青绿
    }

    try
    {
        WindowsApi::setWindowBlurEffect(HWND(winId()));//实现毛玻璃效果,winId()为qt中获得当前窗口句柄的函数
    }
    catch (CalEngine::CalException &exp)
    {}
    //--------------------------接下来是qss样式表相关内容--------------------------//
    QString centralWidgeStyleSheet=QString("QWidget{background-color: rgba(245,245, 245,220);border:1px solid rgb(")+QString::number(tempColor.r)+QString(",")+QString::number(tempColor.g)+QString(",")+QString::number(tempColor.b)+QString(");}");
    centralWidget()->setStyleSheet(centralWidgeStyleSheet);//设置带系统配色边框的窗口

    QTimer::singleShot(100,this, [=]() {mPagelist.setCalPageSize(ui->CalStackedWidget->width(),ui->CalStackedWidget->height());});//构造函数中无法获取正确的窗口大小，所以要延时处理
}

MainWindow::~MainWindow()
{

    delete ui;
}

/*
void MainWindow::paintEvent(QPaintEvent *event)
{
    nowWidth=this->rect().width(),nowHeight=this->rect().height();
    QPainter painter(this);
    painter.setPen(QPen(systemColor,4));//设置画笔
    painter.drawLine(1,1,nowWidth,1);//画直线
    painter.drawLine(nowWidth,1,nowWidth,nowHeight);
    painter.drawLine(nowWidth,nowHeight,1,nowHeight);
    painter.drawLine(1,nowHeight,1,1);
    //qDebug()<<w<<" "<<h;
}
*/

void MainWindow::mouseMoveEvent(QMouseEvent *event){
    if(mIsMousePressed){
        if(mMouseState == 0)//移动位置
        {
            QPointF displacement = event->globalPosition() - mMousePosition;
            this->move(displacement.toPoint());
        }
        else if(mMouseState == 1)//改变宽度
        {
            int displacementX = event->pos().x() - this->rect().width();
            if(this->rect().width() + displacementX >= 250){
                this->resize(this->rect().width() + displacementX, this->rect().height());
            }

        }
        else if(mMouseState == 2)//改变高度
        {
            int displacementY = event->pos().y() - this->rect().height();
            if(this->rect().height() + displacementY >= 500)
                this->resize(this->rect().width(), this->rect().height() + displacementY);
        }
        else//改变高度和宽度
        {
            int displacementX = event->pos().x() - this->rect().width();
            if(this->rect().width() + displacementX >= 250)
                this->resize(this->rect().width() + displacementX, this->rect().height());
            int displacementY = event->pos().y() - this->rect().height();
            if(this->rect().height() + displacementY >= 500)
                this->resize(this->rect().width(), this->rect().height() + displacementY);
        }
        mWindowWidth=this->rect().width();
        mWindowHeight=this->rect().height();
    }

    else
    {
        int _x = abs(event->pos().x()- this->rect().width());
        int _y = abs(event->pos().y() - this->rect().height());
        //qDebug()<<_x<<" "<<_y;
        if(_x < 10 && _y < 10)
        {
            this->setCursor(Qt::SizeFDiagCursor);
            mMouseState = 3;
        }
        else if(_x < 5 && _y > 5 && event->pos().y() > ui->TitleBar->height())
        {
            this->setCursor(Qt::SizeHorCursor);
            mMouseState = 1;
        }
        else if(_x > 5 && _y < 5)
        {
            this->setCursor(Qt::SizeVerCursor);
            mMouseState = 2;
        }
        else
        {
            this->setCursor(Qt::ArrowCursor);
            mMouseState = 0;
        }
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    ui->TitleBar->resize(this->rect().width() - 10, ui->TitleBar->height());
    mMousePosition = event->pos();
    mIsMousePressed = true;
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    mIsMousePressed = false;
    this->setCursor(Qt::ArrowCursor);
    mMouseState = 0;
    //updateFocustoWidget();
    mPagelist.setCalPageFocus(ui->CalStackedWidget->currentIndex());//焦点归还给窗口
}


//窗口强制置顶选项
void MainWindow::on_fixFront_clicked()
{
    Qt::WindowFlags nowflags = windowFlags();
    if(!mIsShowFront)
    {
        //改变位置
        QRect systemRect = QGuiApplication::primaryScreen()->geometry();
        short systemWidth=systemRect.width();//systemHeight=systemRect.height();
        this->setGeometry(systemWidth-mWindowWidth-100,100,mWindowWidth,mWindowHeight);
        //设置置顶
        setWindowFlags(nowflags | Qt::WindowStaysOnTopHint);
        this->show();
        mIsShowFront=true;
    }
    else
    {
        setWindowFlags(nowflags & ~Qt::WindowStaysOnTopHint);
        this->show();
        mIsShowFront=false;
    }

}

void MainWindow::on_maximum_clicked()
{
    if(!mIsMaximum)
    {
        this->showMaximized();
        mIsMaximum=true;
    }
    else
    {
        this->showNormal();
        mIsMaximum=false;
    }
}

void MainWindow::on_shutdown_clicked()
{
    qApp->exit();
}

void MainWindow::on_minimum_clicked()
{
    this->showMinimized();
}

//历史记录侧边栏显示
void MainWindow::on_showHis_clicked()
{
    //int tempWidth=ui->CalWidget->width(),tempHeight=ui->CalWidget->height();
    if(mIsShowHis==false)
    {
        ui->HistoryPage->show();
        mWindowWidth+=250;
        mIsShowHis=true;
    }
    else
    {
        ui->HistoryPage->hide();
        mWindowWidth-=250;
        mIsShowHis=false;
    }
    // ui->CalWidget->resize(tempHeight ,tempWidth);
    this->resize(mWindowWidth,mWindowHeight);
}

void MainWindow::on_modeSwitchButton_clicked()
{
    mChooseBarWidget->resize(150,this->rect().height());
    mChooseBarWidget->show();
    emit functionChooseBarOpenAnimation();
}


void MainWindow::resizeEvent(QResizeEvent *event)
{
    mPagelist.setCalPageSize(ui->CalStackedWidget->width(),ui->CalStackedWidget->height());
}


void MainWindow::getReturnedMode(int selectedMode)
{
    ui->CalStackedWidget->setCurrentIndex(selectedMode);
    this->mPagelist.setCalPageFocus(selectedMode);
}



void MainWindow::updateHistoryPage(QString willupdate)
{
    ui->HisBrowser->append(willupdate);
}
