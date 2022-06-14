#include "CalEngine/Rational.h"
#include "CalEngine/RationalMath.h"
#include "CalEngine/CalException.h"
namespace CalEngine
{
    //构造函数，将传入的字符串存为高精度数或者暂时不做任何事情
    Rational::Rational()
    {
        clearNumber();
    }

    Rational::~Rational()
    {
        clearNumber();
    }

    Rational::Rational(const Rational &inputNumber)
    {
        setNumber(inputNumber.getNumber());
    }

    Rational::Rational(const Rational &&inputNumber)
    {
        setNumber(inputNumber.getNumber());
    }

    Rational::Rational(const QString &inputNumber)
    {
        setNumber(inputNumber);
    }

    Rational::Rational(const int32_t &inputNumber)
    {
        setNumber(QString::number(inputNumber,'f',6));
    }

    Rational::Rational(const long double &inputNumber)
    {
        setNumber(QString::number(inputNumber,'f',16));
    }

    Rational::Rational(const double &inputNumber)
    {
        setNumber(QString::number(inputNumber,'f',16));
    }

    Rational::Rational(const char* inputNumber)
    {
        QString tempNum(inputNumber);
        setNumber(tempNum);
    }

    //反转序列，方便一些对齐计算
    template<class T>
    QVector<T> Rational::getReverse(const QVector<T> &A)
    {
        QVector<T> res;
        //QVector<T>::const_reverse_iterator 手动指定会报错，换成auto自动推导
        for (auto it = A.rbegin(); it != A.rend(); it++)
        {
            res.push_back(*it);
        }
        return res;
    }

    void Rational::deleteLeadingZreo(Rational &A)const
    {
        if(A.mIntegerSize>1)
        {
            for (QVector<int8_t>::const_iterator it = A.mInteger.constBegin(); it != A.mInteger.constEnd()-1; it++)
            {
                if(*it==0)
                {
                    A.mInteger.pop_front();
                }
                else
                {
                    break;
                }
            }
        }

        for (QVector<int8_t>::const_reverse_iterator it = A.mDecimal.rbegin(); it != A.mDecimal.rend(); it++)
        {
            if(*it==0)
            {
                A.mDecimal.pop_back();
            }
            else
            {
                break;
            }
        }
        //更新大小
        A.mDecimalSize=A.mDecimal.size();
        A.mIntegerSize=A.mInteger.size();
    }
    bool Rational::isNegative()const
    {
        return mSign;
    }
    //比较大小
    int8_t Rational::rantionalCompare(const Rational &A,const Rational &B)const
    {
        //其中一个数为0的情况
        if(A.mDecimalSize==0 && A.mIntegerSize==1 && A.mInteger[0]==0)
        {
            if(B.mDecimalSize==0 && B.mIntegerSize==1 && B.mInteger[0]==0)
                return 0;
            return B.mSign==0 ? -1 : 1;
        }
        if(B.mDecimalSize==0 && B.mIntegerSize==1 && B.mInteger[0]==0)
        {
            if(A.mDecimalSize==0 && A.mIntegerSize==1 && A.mInteger[0]==0)
                return 0;
            return A.mSign==0 ? 1 : -1;
        }
        //一正一负的情况
        if(A.mSign!=B.mSign)
            return A.mSign==0? 1 : -1 ;
        //同正同负整数位长度不同的情况
        if(A.mIntegerSize>B.mIntegerSize)
            return 1;
        if((A.mIntegerSize<B.mIntegerSize))
            return -1;
        //整数位长度相同的情况
        for(int i=0;i<A.mIntegerSize;i++)
        {
            if(A.mInteger[i]!=B.mInteger[i])
                return (A.mInteger[i]>B.mInteger[i]) ? 1 : -1;
        }
        //整数位完全相同的情况
        int32_t minSize=A.mDecimalSize<B.mDecimalSize?A.mDecimalSize:B.mDecimalSize;
        for(int i=0;i<minSize;i++)
        {
            if(A.mDecimal[i]!=B.mDecimal[i])
                return (A.mDecimal[i]>B.mDecimal[i]) ? 1 : -1;
        }
        //最后判断小数位长度是否不一样
        if(A.mDecimalSize!= B.mDecimalSize)
            return A.mDecimalSize>B.mDecimalSize ? 1 : -1;
        //整数小数完全相同
        return 0;
    }

    //同正同负高精度相加
    void Rational::rantionalAdd(const Rational &A, const Rational &B, Rational &Res)const
    {
        //小数位相加
        int32_t maxSize = A.mDecimalSize > B.mDecimalSize ? A.mDecimalSize : B.mDecimalSize;
        int32_t addValue = 0;//进位数
        for (int32_t i = maxSize - 1; i >= 0; i--)
        {
            int32_t value = addValue;
            if (i < A.mDecimalSize)
                value += A.mDecimal[i];
            if (i < B.mDecimalSize)
                value += B.mDecimal[i];
            addValue = value / 10;
            Res.mDecimal.push_front(value % 10); //因为是从高位到低位运算，所以要pushfront
        }
        Res.mDecimalSize = maxSize;
        //整数位相加
        maxSize = A.mIntegerSize > B.mIntegerSize ? A.mIntegerSize : B.mIntegerSize;
        QVector<int8_t> rIntegerA = getReverse(A.mInteger), rIntegerB = getReverse(B.mInteger); //获取相反序列，方便相加进位
        for (int32_t i = 0; i < maxSize; i++)
        {
            int32_t value = addValue;
            if (i < A.mIntegerSize)
                value += rIntegerA[i];
            if (i < B.mIntegerSize)
                value += rIntegerB[i];
            addValue = value / 10;
            Res.mInteger.push_front(value % 10);
        }
        if (addValue > 0)
        {
            Res.mIntegerSize = maxSize + 1;
            Res.mInteger.push_front(addValue);
        }
        else
        {
            Res.mIntegerSize = maxSize;
        }
        Res.mSign = A.mSign;
        deleteLeadingZreo(Res);
    }

    //高精度相减
    void Rational::rantionalSubtract(const Rational &A, const Rational &B, Rational &Res)const
    {
        //测试数据 1.1 100.1  1.1 1000
        const Rational *numA=&A,*numB=&B;
        if(A==B)//A和B相等时候直接返回零
        {
            Res.setNumber("0");
            return;
        }
        if(RationalMath::abs(A)<RationalMath::abs(B))//使得较大的数为被减数
        {
            numA=&B;
            numB=&A;
            Res.setOppositeNumber();
        }
        //开始计算小数部分
        int32_t needValue=0;//借位数
        int32_t maxSize=numA->mDecimalSize>numB->mDecimalSize?numA->mDecimalSize:numB->mDecimalSize;
        for(int32_t i=maxSize-1;i>=0;i--)
        {
            int32_t value = -needValue;
            if (i < numA->mDecimalSize)//防止越位，需要判断一下
                value+=numA->mDecimal[i];
            if (i < numB->mDecimalSize)
                value-=numB->mDecimal[i];
            if(value<0)
            {
                value+=10;
                needValue=1;
            }
            else
                needValue=0;
            Res.mDecimal.push_front(value);
        }

        Res.mDecimalSize=maxSize;//更新小数位数大小
        //开始计算整数部分
        maxSize=numA->mIntegerSize>numB->mIntegerSize?numA->mIntegerSize:numB->mIntegerSize;
        QVector<int8_t> rIntegerA = getReverse(numA->mInteger), rIntegerB = getReverse(numB->mInteger);//获取相反序列，方便相减借位
        for(int i=0;i<maxSize;i++)
        {
            int32_t value = -needValue;
            if (i < numA->mIntegerSize)//防止越位，需要判断一下
                value+=rIntegerA[i];
            if (i < numB->mIntegerSize)
                value-=rIntegerB[i];
            if(value<0)
            {
                value+=10;
                needValue=1;
            }
            else
                needValue=0;
            Res.mInteger.push_front(value);
        }
        Res.mIntegerSize=maxSize;//更新整数位数大小
        if(A.mSign==1)//说明两个输入数都为负数
        {
            Res.setOppositeNumber();
        }
        deleteLeadingZreo(Res);
    }

    void Rational::rantionalMultiply(const Rational &A, const Rational &B, Rational &Res)const
    {
        if(A.mSign^B.mSign)
            Res.mSign=1;
        Rational numA(A.getNumber().replace(".","")),numB(B.getNumber().replace(".",""));

        if(numA.mIntegerSize<numB.mIntegerSize)//确保A为位数多的
        {
            numA.setNumber(B.getNumber().replace(".",""));
            numB.setNumber(A.getNumber().replace(".",""));
        }
        //在Res中开辟空间
        for(int32_t i=0;i<numA.mIntegerSize+numB.mIntegerSize-1;i++)
            Res.mInteger.push_back(0);
        int32_t addValue=0;//进位数
        for(int32_t i=numB.mIntegerSize-1;i>=0;i--)
        {
            for(int32_t j=numA.mIntegerSize-1;j>=0;j--)
            {
                int32_t value=addValue+numA.mInteger[j]*numB.mInteger[i]+Res.mInteger[i+j];//进位数 加入数 现存数
                Res.mInteger[i+j]=value%10;
                addValue=value/10;
            }
            //处理进位
            while(addValue>0)
            {
                if(i-1>=0)
                    Res.mInteger[i-1]=addValue%10;
                else
                    Res.mInteger.push_front(addValue%10);
                addValue/=10;
            }
        }
        //小数点移位
        for(int i=A.mDecimalSize+B.mDecimalSize-1;i>=0;i--)
        {
            if((Res.mInteger.size()==1 && Res.mInteger[0]==0) || Res.mInteger.isEmpty())//如果整数位只剩下零或空
            {
                Res.mDecimal.push_front(0);
            }
            else//如果整数还有数字
            {
                Res.mDecimal.push_front(Res.mInteger.back());
                Res.mInteger.pop_back();
            }
        }
        //补零，防止10*0.01特殊情况
        if(Res.mInteger.isEmpty())
        {
            Res.mInteger.push_back(0);
        }
        Res.mDecimalSize=Res.mDecimal.size();
        Res.mIntegerSize=Res.mInteger.size();
        deleteLeadingZreo(Res);
    }

    //高精度除法
    void Rational::rantionalDivide(const Rational &A, const Rational &B, Rational &Res,int32_t precision)const
    {
        //测试数据 -1 -1  1 1.2
        //判断除零
        if(B.getNumber()=="0")
        {
            throw CalException(CalParameterError);
        }
        //处理符号
        if(A.mSign^B.mSign)
            Res.mSign=1;
        //除数化整
        Rational numA=A,numB=B;
        numA.mSign=0;
        numB.mSign=0;
        for(int i=0;i<B.mDecimalSize;i++)
        {
            numB.mInteger.push_back(numB.mDecimal.front());
            numB.mDecimal.pop_front();
            if(numA.mDecimal.size()>0)
            {
                numA.mInteger.push_back(numA.mDecimal.front());
                numA.mDecimal.pop_front();
            }
            else
            {
                numA.mInteger.push_back(0);
            }
        }
        //更新大小，去除前导零
        numA.mIntegerSize=numA.mInteger.size();
        numB.mIntegerSize=numB.mInteger.size();
        numA.mDecimalSize=numA.mDecimal.size();
        numB.mDecimalSize=numB.mDecimal.size();
        deleteLeadingZreo(numA);
        deleteLeadingZreo(numB);
        //开始除法计算
        //整数部分
        Rational nowValue("0");//记录当前被除的值
        for(int i=0;i<numA.mIntegerSize;i++)
        {
            nowValue=nowValue*Rational("10")+Rational(numA.mInteger[i]);
            if(nowValue<numB)
            {
                Res.mInteger.push_back(0);
                continue;
            }
            int8_t j=1;
            for(j=1;j<=9;j++)
            {
                if(numB*Rational(j)>nowValue)
                {
                    break;
                }
            }
            Res.mInteger.push_back(j-1);
            nowValue=nowValue-numB*Rational(j-1);
        }
        //小数部分
        for(int i=0;i<numA.mDecimalSize;i++)
        {
            nowValue=nowValue*Rational("10")+Rational(numA.mDecimal[i]);
            if(nowValue<numB)
            {
                Res.mDecimal.push_back(0);
                continue;
            }
            int8_t j=1;
            for(j=1;j<=9;j++)
            {
                if(numB*Rational(j)>nowValue)
                {
                    break;
                }
            }
            Res.mDecimal.push_back(j-1);
            nowValue=nowValue-numB*Rational(j-1);
        }
        //增加部分
        for(int i=0;i<precision;i++)
        {
            if(nowValue.getNumber()=="0")//说明除尽
            {
                break;
            }
            nowValue=nowValue*Rational("10");
            if(nowValue<numB)
            {
                Res.mDecimal.push_back(0);
                continue;
            }
            int8_t j=1;
            for(j=1;j<=9;j++)
            {
                if(numB*Rational(j)>nowValue)
                {
                    break;
                }
            }
            Res.mDecimal.push_back(j-1);
            nowValue=nowValue-numB*Rational(j-1);
        }
        //答案去先导零，更新size
        Res.mIntegerSize=Res.mInteger.size();
        Res.mDecimalSize=Res.mDecimal.size();
        deleteLeadingZreo(Res);
    }

    //设置高精度数
    void Rational::setNumber(const QString &inputNumber)
    {
        clearNumber();
        bool hasDecimal = 0;
        if (inputNumber[0] == '-')
        {
            mSign = true;
        }
        for (const QChar &i : inputNumber)
        {
            if (i.isDigit() && hasDecimal == 0)
            {
                mInteger.push_back(i.digitValue());
            }
            else if (i.isDigit() && hasDecimal == 1)
            {
                mDecimal.push_back(i.digitValue());
            }
            else if (i == '.')
            {
                hasDecimal = 1;
            }

        }
        mDecimalSize = mDecimal.size();
        mIntegerSize = mInteger.size();
        deleteLeadingZreo(*this);
    }

    //设置相反数
    void Rational::setOppositeNumber()
    {
        if(!mSign)
            mSign=1;
        else
            mSign=0;
    }

    Rational Rational::getOppositeNumber()const
    {
        Rational Res=*this;
        Res.setOppositeNumber();
        return Res;
    }
    void Rational::setPrecision(const int32_t precision)
    {
        if(mDecimalSize+mIntegerSize>precision)
        {
            for(int i=0;i<mIntegerSize;i++)//超过精度整数置零
            {
                if(i>precision)
                {
                    mInteger[i]=0;
                }
            }
            for(int i=0;i<mDecimalSize;i++)//超过精度小数抛弃
            {
                if(i+mIntegerSize-1>precision)
                {
                    mDecimal.erase(mDecimal.constBegin()+i,mDecimal.constEnd());
                    break;
                }
            }
            mDecimalSize=mDecimal.size();
        }

    }
    //检查是否存有高精度数
    bool Rational::hasNumber()
    {
        if (mInteger.isEmpty() && mDecimal.isEmpty())
            return false;
        return true;
    }
    //输出高精度数为字符串
    QString Rational::getNumber()const
    {
        QString Res;
        if (mSign == true)
            Res.append("-");
        for(QVector<int8_t>::const_iterator it = mInteger.constBegin(); it != mInteger.constEnd(); it++) //迭代器遍历vector
        {
            Res.append(QChar(*it + 48)); //通过+48使得数字转ASCII对应字符
        }
        if (!mDecimal.isEmpty())
        {
            Res.append(".");
            for (QVector<int8_t>::const_iterator it = mDecimal.constBegin(); it != mDecimal.constEnd(); it++)
            {
                Res.append(QChar(*it + 48));
            }
        }
        return Res;
    }

    QString Rational::getDecimal() const
    {
        QString Res;
        if (!mDecimal.isEmpty())
        {
            if (mSign == true)
                Res.append("-");
            Res.append("0.");
            for (QVector<int8_t>::const_iterator it = mDecimal.constBegin(); it != mDecimal.constEnd(); it++)
            {
                Res.append(QChar(*it + 48));
            }
        }
        return Res;
    }

    QString Rational::getInteger() const
    {
        QString Res;
        if (mSign == true)
            Res.append("-");
        for(QVector<int8_t>::const_iterator it = mInteger.constBegin(); it != mInteger.constEnd(); it++) //迭代器遍历vector
        {
            Res.append(QChar(*it + 48)); //通过+48使得数字转ASCII对应字符
        }
        return Res;
    }
    //清除存储的数字
    void Rational::clearNumber()
    {
        mInteger.clear();
        mDecimal.clear();
        mIntegerSize = 0;
        mDecimalSize = 0;
        mSign = 0;
    }

    //高精度运算重载
    bool Rational::operator>(const Rational &A)const
    {
        int8_t res=rantionalCompare(*this,A);
        if(res==1)
            return true;
        return false;
    }

    bool Rational::operator>=(const Rational &A)const
    {
        int8_t res=rantionalCompare(*this,A);
        if(res==1 || res==0)
            return true;
        return false;
    }

    bool Rational::operator<(const Rational &A)const
    {
        int8_t res=rantionalCompare(*this,A);
        if(res==-1)
            return true;
        return false;
    }
    bool Rational::operator<=(const Rational &A)const
    {
        int8_t res=rantionalCompare(*this,A);
        if(res==-1 || res==0)
            return true;
        return false;
    }
    bool Rational::operator==(const Rational &A)const
    {
        int8_t res=rantionalCompare(*this,A);
        if(res==0)
            return true;
        return false;
    }
    bool Rational::operator!=(const Rational &A)const
    {
        int8_t res=rantionalCompare(*this,A);
        if(res!=0)
            return true;
        return false;
    }
    Rational Rational::operator+(const Rational &A)const
    {
        Rational Res;
        if (mSign ^ A.mSign) //如果两个加数符号不同，则变为相减
        {
            rantionalSubtract(*this, A, Res);
        }
        else
        {
            rantionalAdd(*this, A, Res);
        }
        return Res;
    }
    Rational Rational::operator-(const Rational &A)const
    {
        Rational Res;
        if (mSign ^ A.mSign) //如果两个加数符号不同，则变为相加
        {
            rantionalAdd(*this,A, Res);
            //符号在rantionalAdd里已处理完毕
        }
        else
        {
            rantionalSubtract(*this, A, Res);
        }
        return Res;
    }

    Rational Rational::operator*(const Rational &A)const
    {
        Rational Res;
        rantionalMultiply(*this,A,Res);
        //Res.setPrecision(12);
        return Res;
    }
    Rational Rational::operator/(const Rational &A)const
    {
        Rational Res;
        int32_t precision=(A.mIntegerSize+A.mDecimalSize)>20?(A.mIntegerSize+A.mDecimalSize):20;
        rantionalDivide(*this,A,Res,precision);
        //Res.setPrecision(12);
        return Res;
    }

    void Rational::operator=(const Rational &A)
    {
        //this->setNumber(A.getNumber());
        this->mInteger=A.mInteger;
        this->mDecimal=A.mDecimal;
        this->mSign=A.mSign;
        this->mIntegerSize=A.mIntegerSize;
        this->mDecimalSize=A.mDecimalSize;
    }

    Rational::operator QString()
    {
        return this->getNumber();
    }

    Rational& Rational::operator=(Rational &&A)
    {
        this->mInteger=std::move(A.mInteger);
        this->mDecimal=std::move(A.mDecimal);
        this->mSign=A.mSign;
        this->mIntegerSize=A.mIntegerSize;
        this->mDecimalSize=A.mDecimalSize;

        return *this;
    }

    void Rational::operator+=(const Rational &A)
    {
        *this=*this+A;
    }

    void Rational::operator-=(const Rational &A)
    {
        *this=*this-A;
    }

    void Rational::operator*=(const Rational &A)
    {
        *this=(*this)*A;
    }

    void Rational::operator/=(const Rational &A)
    {
        *this=*this/A;
    }

    //自定义字面量
    Rational operator "" _rat(const char* inputString,size_t)
    {
        Rational Res(inputString);
        return Res;
    }

}
