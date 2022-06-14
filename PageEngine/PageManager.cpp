#include "PageManager.h"
#include "CalEngine/CalException.h"
#include<QWidget>

using CalEngine::CalException;
using CalEngine::ErrorName;

namespace PageEngine
{
    PageManager::PageManager(QObject *parent) : QObject(parent)
    {
        mParentWindow=parent;
    }

    void PageManager::addCalPage(QWidget *willadd,QWidget *parent)
    {
        willadd->setParent(parent);
        mCalPages.append(willadd);
        //m_calPages.last()->setParent(parent);
    }

    void PageManager::setCalPageSize(int32_t xx, int32_t yy)
    {
        for(QWidget* page:mCalPages)
        {
            page->resize(xx,yy);
        }
    }

    void PageManager::setCalPageFocus(int32_t widgetIndex)
    {
        if(widgetIndex>=mCalPages.size())
        {

            throw CalException(ErrorName::CalParameterError);
        }
        mCalPages[widgetIndex]->activateWindow();//激活 默认窗口，是设置焦点的前提
        mCalPages[widgetIndex]->setFocus();//将焦点交给子窗口，激活子窗口keypressevent
    }
    QWidget* PageManager::getCalPage(int32_t widgetIndex)
    {
        if(widgetIndex>=mCalPages.size())
        {
            throw CalException(ErrorName::CalParameterError);
        }
        return mCalPages[widgetIndex];
    }

}

