#************  Qt Configurations  *****************************************************************
QT -= gui
CONFIG += c++11 console
CONFIG -= app_bundle
DEFINES += QT_DEPRECATED_WARNINGS
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000


#************  X 3rd Party Libs  ******************************************************************


#************  X Modules  *************************************************************************
include($$PWD/../../libraries/x_orm/x_orm.pri)
include($$PWD/../../libraries/x_utils/x_utils.pri)


#************  QML Configurations  ****************************************************************


#************  App Sources  ***********************************************************************
HEADERS += \
    $$PWD/src/entities/customer.hpp \
    $$PWD/src/entities/product.hpp \
    $$PWD/src/entities/invoice.hpp \
    $$PWD/src/entities/invoiceproduct.hpp \
    $$PWD/src/entities/account.hpp \
    $$PWD/src/entities/converters/datetimeconverter.hpp \
    $$PWD/src/entities/converters/categoryconverter.hpp

SOURCES += \
    $$PWD/src/main.cpp \
    $$PWD/src/entities/customer.cpp \
    $$PWD/src/entities/product.cpp \
    $$PWD/src/entities/invoice.cpp \
    $$PWD/src/entities/invoiceproduct.cpp \
    $$PWD/src/entities/account.cpp \
    $$PWD/src/entities/converters/datetimeconverter.cpp \
    $$PWD/src/entities/converters/categoryconverter.cpp

INCLUDEPATH += \
    $$PWD/src \
    $$PWD/src/entities \
    $$PWD/src/entities/converters


#************  Resources  *************************************************************************


#************  Images Files  **********************************************************************


#************  QML Files  *************************************************************************


##************  Android Configurations  ************************************************************

