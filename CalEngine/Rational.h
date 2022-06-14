#ifndef RATIONAL_H
#define RATIONAL_H

#include <QVector>

namespace CalEngine
{
    class Rational{

    private:
        //存储小数和整数位
        QVector<int8_t> mInteger;                                                                               //从左往右为个位，十位，百位
        QVector<int8_t> mDecimal;                                                                               //从左往右为十分位，百分位，千分位
        bool mSign;                                                                                             //正负，0正1负
        int32_t mDecimalSize;                                                                                   //小数大小
        int32_t mIntegerSize;                                                                                   //整数大小

        void deleteLeadingZreo(Rational &A)const;                                                              //删除前导零
        //高精度运算
        int8_t rantionalCompare(const Rational &A,const Rational &B)const;                                    //高精度比较
        void rantionalAdd(const Rational &A,const Rational &B,Rational &Res)const;                           //高精度加法
        void rantionalSubtract(const Rational &A,const Rational &B,Rational &Res)const;                      //高精度减法
        void rantionalMultiply(const Rational &A,const Rational &B,Rational &Res)const;                      //高精度乘法
        void rantionalDivide(const Rational &A,const Rational &B,Rational &Res,int32_t precision)const;      //高精度除法
    public:
        //构造函数
        Rational();                                                //创建空数字
        Rational(const Rational &inputNumber);                    //从Rational创建数字
        Rational(const QString &inputNumber);                      //从字符串创建数字
        Rational(const Rational &&inputNumber);
        Rational(const int32_t &inputNumber);                      //从int32创建数字
        Rational(const long double &inputNumber);                  //从double64创建数字
        Rational(const double &inputNumber);
        Rational(const char* inputNumber);                         //从char*创建数字
        ~Rational();

        void setNumber(const QString &inputNumber);                 //设置高精度数
        bool hasNumber();                                           //检查是否存有高精度数
        QString getNumber()const;                                   //输出高精度数为字符串
        QString getDecimal()const;                                  //单独获取小数部分
        QString getInteger()const;                                  //获取整数部分
        Rational getOppositeNumber()const;                         //获取相反数
        void clearNumber();                                         //清除存储的数字

        void setOppositeNumber();                                   //设置相反数
        void setPrecision(const int32_t precision);                 //设置精度
        bool isNegative()const;                                     //判断正负数

        template<class T>
        static QVector<T> getReverse(const QVector<T> &A);          //生成Vector内元素倒序序列并返回
        //运算符重载
        bool operator>(const Rational &A)const;                    //重载大于号
        bool operator>=(const Rational &A)const;                   //重载大于等于号
        bool operator<(const Rational &A)const;                    //重载小于号
        bool operator<=(const Rational &A)const;                   //重载小于等于号
        bool operator==(const Rational &A)const;                   //重载等于号
        bool operator!=(const Rational &A)const;                   //重载不等于号
        Rational operator+(const Rational &A)const;               //重载加法
        Rational operator-(const Rational &A)const;               //重载减法
        Rational operator*(const Rational &A)const;               //重载乘法
        Rational operator/(const Rational &A)const;               //重载除法
        void operator=(const Rational &A);                         //重载赋值号 深拷贝
        Rational& operator=(Rational &&A);                        //重载赋值号 浅拷贝
        operator QString();                                         //重载强制类型转换

        void operator+=(const Rational &A);
        void operator-=(const Rational &A);
        void operator*=(const Rational &A);
        void operator/=(const Rational &A);

    };

    Rational operator "" _rat(const char* inputString,size_t);     //自定义字面量

}

#endif // RATIONAL_H
