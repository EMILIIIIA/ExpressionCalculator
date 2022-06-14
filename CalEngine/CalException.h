#ifndef CALEXCEPTION_H
#define CALEXCEPTION_H

#include<QException>
namespace CalEngine
{
    enum ErrorName
    {
        CalDefaultError,CalSyntaxError,CalParameterError,CalBracketError,CalOperatorError,CalSystemError,CalUnknownError
    };

    class CalException:public QException
    {
    private:
        ErrorName mError;
    public:
        CalException(const ErrorName inpErr);
        ErrorName getErrorName();


    };
}


#endif // CALEXCEPTION_H
