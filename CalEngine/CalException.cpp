#include "CalException.h"

namespace CalEngine
{
    CalException::CalException(const ErrorName inpErr)
    {
        mError=inpErr;
    }

    ErrorName CalException::getErrorName()
    {
        return mError;
    }
}

