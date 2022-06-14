#ifndef MAINDISPLAYLINEEDIT_H
#define MAINDISPLAYLINEEDIT_H

#include <QLineEdit>
class MainDisplayLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    MainDisplayLineEdit(QWidget* parent);

    QString getExpression();                                            //获取表达式
    void setExpression(const QString &inputExp);                        //设置表达式
    void appendExpression(const QString &willappend);                   //在表达式中追加字符
    void insertExpression(const QString &willappend,const int32_t pos);
    void chopExpression(unsigned int par);                              //在表达式中删减字符
    void clearExpression();                                             //清除表达式
    void removeExpression(const int32_t pos,const int32_t n);
    void changeTextToFormat();                                          //格式化并更新
    void setError(const QString &inputExp);                             //设置表达式错误信息状态
    bool getHasError();                                                 //获取表达式错误信息状态
private:
    QFont mDispFont;                                                     //显示字体
    bool mHasError;                                                      //错误信息标识
    bool mIsEmptyExp;                                                        //为空表达式
public slots:

    void on_linedit_textedited(QString);                               //文本改变槽函数
};

#endif // MAINDISPLAYLINEEDIT_H
