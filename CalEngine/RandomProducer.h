#ifndef RANTIONAL_H
#define RANTIONAL_H

#include <QQueue>

namespace CalEngine
{
    class AbstractRandomProducer{
    public:
        enum  ENUM_RAND_METHOD {C98Rand,CPURand,C11Rand};
        virtual uint32_t getRandom() = 0;
        virtual ~ AbstractRandomProducer();
        //我宣布虚函数是这个世界上最伟大的发明
    };

    //三种算法
        class producerC98Rand:public  AbstractRandomProducer
        {
            static bool isSrand;
            uint32_t getRandom()override;
        };

        class producerCPURand:public  AbstractRandomProducer
        {

            uint32_t getRandom()override;
        };


        class producerC11Rand:public  AbstractRandomProducer
        {
            static QQueue<uint32_t> randQue;
            uint32_t getRandom()override;
        };


        //用户接口
        class randomInterface
        {
        private:
            AbstractRandomProducer *rnd;
        public:
            randomInterface(AbstractRandomProducer::ENUM_RAND_METHOD);
            ~randomInterface();
            uint32_t getRandom(int,int);
        };

}

#endif // RANTIONAL_H
