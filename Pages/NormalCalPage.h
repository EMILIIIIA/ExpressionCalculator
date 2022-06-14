#ifndef NORMALCALPAGE_H
#define NORMALCALPAGE_H

#include <QWidget>

namespace Ui {
class NormalCalculatorPage;
}

class NormalCalculatorPage : public QWidget
{
    Q_OBJECT

public:
    explicit NormalCalculatorPage(QWidget *parent = nullptr);
    ~NormalCalculatorPage();

private slots:
    void on_opInv_pressed();



private:
    Ui::NormalCalculatorPage *ui;
    void updateHisLabel(QString);
    void keyPressEvent(QKeyEvent *event)override;
    void resizeEvent(QResizeEvent *event)override;
    void calResult();

signals:
    void updateHistoryPage(QString willupdate);
};

#endif // NORMALCALPAGE_H
