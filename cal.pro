QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
QMAKE_CXXFLAGS_RELEASE += -O3       # Release -O3
SOURCES += \
    CalEngine//ExpressionCalculation/AbstractExpressionCalculation.cpp \
    CalEngine/CalException.cpp \
    CalEngine/ExpressionCalculation/NormalExpressionCalculation.cpp \
    CalEngine/ExpressionCalculation/ProgrammerExpressionCalculation.cpp \
    CalEngine/ExpressionCalculation/ScienceExpressionCalculation.cpp \
    CalEngine/Rational.cpp \
    CalEngine/RationalMath.cpp \
    PageEngine/MainDisplayLineEdit.cpp \
    PageEngine/PageManager.cpp \
    PageEngine/Widgets/ZeroOneButton.cpp \
    Pages/FunctionChooseBar.cpp \
    Pages/NormalCalPage.cpp \
    Pages/ProgrammerCalPage.cpp \
    Pages/RandomPage.cpp \
    Pages/ProStaCalPage.cpp \
    PageEngine/WindowsApi.cpp \
    Pages/ScienceCalPage.cpp \
    main.cpp \
    MainWindow.cpp \
    CalEngine/RandomProducer.cpp

HEADERS += \
    CalEngine//ExpressionCalculation/AbstractExpressionCalculation.h \
    CalEngine/CalException.h \
    CalEngine/ExpressionCalculation/NormalExpressionCalculation.h \
    CalEngine/ExpressionCalculation/ProgrammerExpressionCalculation.h \
    CalEngine/ExpressionCalculation/ScienceExpressionCalculation.h \
    CalEngine/Rational.h \
    CalEngine/RationalMath.h \
    PageEngine/MainDisplayLineEdit.h \
    PageEngine/PageManager.h \
    PageEngine/Widgets/ZeroOneButton.h \
    Pages/FunctionChooseBar.h \
    Pages/NormalCalPage.h \
    Pages/ProgrammerCalPage.h \
    Pages/RandomPage.h \
    Pages/ProStaCalPage.h \
    PageEngine/WindowsApi.h \
    MainWindow.h \
    CalEngine/RandomProducer.h \
    Pages/ScienceCalPage.h

FORMS += \
    Pages/FunctionChooseBar.ui \
    Pages/NormalCalPage.ui \
    Pages/ProgrammerCalPage.ui \
    Pages/RandomPage.ui \
    Pages/ProStaCalPage.ui \
    MainWindow.ui \
    Pages/ScienceCalPage.ui

#LIBS += -dwmapi
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Images/Images.qrc

#QMAKE_CXXFLAGS += \
#    mcmodel=large
