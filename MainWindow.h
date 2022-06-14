#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>

#include "PageEngine/PageManager.h"
#include "Pages/FunctionChooseBar.h"

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

    void on_fixFront_clicked();                                 //窗口强制置顶

    void on_maximum_clicked();                                  //窗口最大化

    void on_minimum_clicked();                                  //窗口最小化

    void on_shutdown_clicked();                                 //关闭程序

    void on_showHis_clicked();                                  //显示历史记录

    void on_modeSwitchButton_clicked();                         //打开功能选择栏


public slots:

    void getReturnedMode(int selectedMode);                     //从功能选择栏获取选项
    void updateHistoryPage(QString);                            //更新历史记录页面

signals:
    void functionChooseBarOpenAnimation();                      //控制功能选择栏开启动画
    void functionChooseBarCloseAnimation();                     //控制功能选择栏结束动画

private:


    void mouseMoveEvent(QMouseEvent *event) override;           //重写鼠标移动事件
    void mousePressEvent(QMouseEvent *event) override;          //重写鼠标按下事件
    void mouseReleaseEvent(QMouseEvent *event) override;        //重写鼠标松开事件
    void resizeEvent(QResizeEvent *event)override;
    //void paintEvent(QPaintEvent *event)override;

    FunctionChooseBar *mChooseBarWidget;                       //功能选择栏

    Ui::MainWindow *ui;

    PageEngine::PageManager mPagelist;                         //页面管理器
    int mWindowWidth;                                          //窗口宽度
    int mWindowHeight;                                         //窗口高度
    int mLastWidth;                                            //上次窗口宽度
    int mLastHeight;                                           //上次窗口高度
    int8_t mMouseState = 0;                                    //鼠标状态
    QPoint mMousePosition;                                     //鼠标位置


    bool mIsMaximum = false;                                   //是否最大化
    bool mIsShowFront =false;                                  //是否置顶显示
    bool mIsShowHis=false;                                     //是否打开历史栏
    bool mIsMousePressed = false;                              //鼠标是否按下
};
#endif // MAINWINDOW_H
