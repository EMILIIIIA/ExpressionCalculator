#ifndef SCIENCECALPAGE_H
#define SCIENCECALPAGE_H

#include <QWidget>

namespace Ui {
    class ScienceCalPage;
}

class ScienceCalPage : public QWidget
{
    Q_OBJECT

public:
    explicit ScienceCalPage(QWidget *parent = nullptr);
    ~ScienceCalPage();

private slots:


private:
    Ui::ScienceCalPage *ui;
    void updateHisLabel(QString);
    void calResult();
    void keyPressEvent(QKeyEvent *event)override;
    void resizeEvent(QResizeEvent *event)override;

signals:
    void updateHistoryPage(QString willupdate);

};


#endif // SCIENCECALPAGE_H
