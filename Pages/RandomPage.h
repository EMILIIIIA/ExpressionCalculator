#ifndef RANDOMPAGE_H
#define RANDOMPAGE_H

#include <QWidget>

namespace Ui {
class RandomPage;
}

class RandomPage : public QWidget
{
    Q_OBJECT

public:
    explicit RandomPage(QWidget *parent = nullptr);
    ~RandomPage();

private:
    Ui::RandomPage *ui;
    void updateHistory(QString willupdate);
    void updateCurrent(QString willupdate);
private slots:

    void on_RanC98button_clicked();

    void on_RanC11button_clicked();

    void on_RanCPUbutton_clicked();



};
#endif // RANDOMPAGE_H
