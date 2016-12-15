#-------------------------------------------------
#
# Project created by QtCreator 2015-10-20T23:51:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += debug
TARGET = treeproject
TEMPLATE = app
CONFIG += c++11


SOURCES += main.cpp\
    qcustomplot.cpp \
    dashboard.cpp \
    summary.cpp \
    DateFilter.cpp \
    Database.cpp \
    FieldMatchFilter.cpp \
    Filter.cpp \
    IOUtility.cpp \
    Preprocessor.cpp \
    ProcessedGrantsAndFundingRecord.cpp \
    ProcessedPresentationRecord.cpp \
    ProcessedPublicationRecord.cpp \
    ProcessedTeachingRecord.cpp \
    Utility.cpp \
    edit.cpp \
    treewidgetforgrant.cpp \
    graphhelper.cpp \
    treewidgetforpublication.cpp \
    treewidgetforpresentation.cpp \
    treewidgetforteaching.cpp

HEADERS  += \
    qcustomplot.h \
    dashboard.h \
    summary.h \
    DateFilter.h \
    Database.h \
    FieldMatchFilter.h \
    Filter.h \
    GrantsAndFundingFields.h \
    IOUtility.h \
    Preprocessor.h \
    ProcessedGrantsAndFundingRecord.h \
    ProcessedPresentationRecord.h \
    ProcessedPublicationRecord.h \
    ProcessedTeachingRecord.h \
    Utility.h \
    edit.h \
    treewidgetforgrant.h \
    graphhelper.h \
    treewidgetforpublication.h \
    treewidgetforpresentation.h \
    treewidgetforteaching.h

FORMS    += \
    dashboard.ui \
    summary.ui \
    edit.ui

RESOURCES += \
    images.qrc
