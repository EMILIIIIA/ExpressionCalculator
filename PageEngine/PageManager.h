#ifndef PAGEMANAGER_H
#define PAGEMANAGER_H

#include <QObject>
#include <QVector>
namespace PageEngine
{
    class PageManager : public QObject
    {
        Q_OBJECT
        //Q_CLASSINFO("index","doc.qt.io");
    private:
        QVector<QWidget*> mCalPages;
        QObject *mParentWindow;
    public:
        explicit PageManager(QObject *parent = nullptr);
        void addCalPage(QWidget* willadd,QWidget *parent);
        void setCalPageSize(int32_t xx,int32_t yy);
        void setCalPageFocus(int32_t pageIndex);
        QWidget* getCalPage(int32_t widgetIndex);
    signals:

    };

}

#endif // PAGEMANAGER_H
