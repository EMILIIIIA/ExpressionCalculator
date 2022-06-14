#ifndef PROGRAMMERCALPAGE_H
#define PROGRAMMERCALPAGE_H

#include <QWidget>

namespace Ui {
    class ProgrammerCalPage;
}

class ProgrammerCalPage : public QWidget
{
    Q_OBJECT

public:
    explicit ProgrammerCalPage(QWidget *parent = nullptr);
    ~ProgrammerCalPage();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ProgrammerCalPage *ui;
};

#endif // PROGRAMMERCALPAGE_H
