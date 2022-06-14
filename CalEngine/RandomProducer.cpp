#include "CalEngine/RandomProducer.h"
#include "CalEngine/CalException.h"
#include <cstdlib>
#include <random>
#define minmax(a,b,c) ((a%(c-b+1))+b)

namespace CalEngine {
    bool producerC98Rand::isSrand=false;
    QQueue<uint32_t> producerC11Rand::randQue;

    AbstractRandomProducer::~ AbstractRandomProducer(){}

    uint32_t producerC98Rand::getRandom()
    {
        if(!isSrand)
        {
            srand((int)time(NULL));
            isSrand=true;
        }
        return rand();
    }


#ifdef _WIN32
    uint32_t producerCPURand::getRandom()
    {
        long flag=0;
        asm volatile("movl $1, %%eax \n" "cpuid \n" "and $0x20000000, %%eax \n" "test $0, %%eax \n" "jnz L \n" "movl $1,%0 \n" "L: \n" "movl $1,%0 \n":"=r"(flag)::"memory");
        //    R"(
        //    movl $1, %eax
        //    cpuid
        //    and $0x20000000, %eax
        //    test $0, %eax
        //    jnz L
        //    movl $1,%[op1]
        //    L:
        //    )"

        if (!flag)
        {
            throw CalException(CalSystemError);
            return 0;
        }
        //    asm(
        //    R"(
        //    .section .data
        //    result : .int 0
        //    .section .text
        //    rdrand %eax
        //    movabs %eax, result
        //    )"
        //    );
        uint32_t result;
        asm volatile("rdrand %%eax \n" "movl %%eax,%0 \n":"=r"(result)::"memory");
        return result;
    }
#else
};
    unsigned long producerCPURand::getRandom()
    {
        throw CalException(CalSystemError);
    }
#endif

    uint32_t producerC11Rand::getRandom()
    {
        if(randQue.empty())
        {
            std::default_random_engine c11random((int)time(NULL));
            for(short i=0;i<=100;i++)
                randQue.push_back(c11random());
        }
        long ans=randQue.front();
        randQue.pop_front();
        return ans;
    }



    randomInterface::randomInterface(AbstractRandomProducer::ENUM_RAND_METHOD choosedMethod)
    {
        if (choosedMethod==AbstractRandomProducer::C98Rand)
            rnd = new producerC98Rand;
        else if (choosedMethod==AbstractRandomProducer::CPURand)
            rnd = new producerCPURand;
        else
            rnd = new producerC11Rand;
    }

    randomInterface::~randomInterface()
    {
        delete rnd;
    }

    uint32_t randomInterface::getRandom(int minNum,int maxNum)
    {
        long ans=minmax(rnd->getRandom(),minNum,maxNum);
        return ans;
    }

};
