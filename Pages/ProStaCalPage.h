#ifndef PROSTACALPAGE_H
#define PROSTACALPAGE_H

#include <QWidget>

namespace Ui {
class ProStaCalPage;
}

class ProStaCalPage : public QWidget
{
    Q_OBJECT

public:
    explicit ProStaCalPage(QWidget *parent = nullptr);
    ~ProStaCalPage();

private:
    Ui::ProStaCalPage *ui;
};

#endif // PROSTACALPAGE_H
