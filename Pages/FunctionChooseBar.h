#ifndef FUNCTIONCHOOSEBAR_H
#define FUNCTIONCHOOSEBAR_H

#include <QWidget>
#include <QPropertyAnimation>
namespace Ui {
class FunctionChooseBar;
}

class FunctionChooseBar : public QWidget
{
    Q_OBJECT

public:
    explicit FunctionChooseBar(QWidget *parent = nullptr);
    ~FunctionChooseBar();
    QString getSelectedWindow();

private slots:


    void on_normalButton_clicked();

    void on_scienceButton_clicked();

    void on_programmerButton_clicked();

    void on_randomPageButton_clicked();

public slots:
    void showOpenAnimation();
    void showCloseAnimation();
signals:
    void emitSelectedModes(int selectedMode);

private:
    Ui::FunctionChooseBar *ui;
    QString windowChoose;
    QPropertyAnimation *openAnimation = new QPropertyAnimation(this, "geometry");
    QPropertyAnimation *closeAnimation = new QPropertyAnimation(this, "geometry");
};

#endif // FUNCTIONCHOOSEBAR_H
