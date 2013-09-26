#-------------------------------------------------
#
# Project created by QtCreator 2012-04-19T02:28:04
#
#-------------------------------------------------

QT       += core gui

TARGET = simple_dmc
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++0x

LIBS += -L/usr/lib64 -lboost_regex

SOURCES += src/main.cpp\
    src/errors/handbookerror.cpp \
    src/mc/reactionspool.cpp \
    src/reactions/abshreaction.cpp \
    src/reactions/addch2reaction.cpp \
    src/reactions/addhreaction.cpp \
    src/reactions/dropdimerreaction.cpp \
    src/reactions/dualreaction.cpp \
    src/reactions/etchingreaction.cpp \
    src/reactions/formdimerreaction.cpp \
    src/reactions/migrationbridgeinfo.cpp \
    src/reactions/migrationbridgereaction.cpp \
    src/reactions/migrationfrontdown.cpp \
    src/reactions/migrationhreaction.cpp \
    src/reactions/monoreaction.cpp \
    src/reactions/reaction.cpp \
    src/savers/crystalsaver.cpp \
    src/savers/reactionpoolsaver.cpp \
    src/savers/saver.cpp \
    src/savers/surfacesaver.cpp \
    src/savers/timenumbercurvessaver.cpp \
    src/surface/crystal.cpp \
    src/surface/layer.cpp \
    src/surface/surface.cpp \
    src/tools/configurator.cpp \
    src/tools/handbook.cpp \
    src/tools/runner.cpp

HEADERS  += \
    src/int3.h \
    src/errors/handbookerror.h \
    src/errors/parse_error.h \
    src/errors/parse_params_error.h \
    src/mc/reactionspool.h \
    src/reactions/abshreaction.h \
    src/reactions/addch2reaction.h \
    src/reactions/addhreaction.h \
    src/reactions/dropdimerreaction.h \
    src/reactions/dualreaction.h \
    src/reactions/etchingreaction.h \
    src/reactions/formdimerreaction.h \
    src/reactions/migrationbridgeinfo.h \
    src/reactions/migrationbridgereaction.h \
    src/reactions/migrationfrontdown.h \
    src/reactions/migrationhreaction.h \
    src/reactions/monoreaction.h \
    src/reactions/reaction.h \
    src/reactions/reactor.h \
    src/savers/crystalsaver.h \
    src/savers/reactionpoolsaver.h \
    src/savers/saver.h \
    src/savers/surfacesaver.h \
    src/savers/timenumbercurvessaver.h \
    src/surface/carbon.h \
    src/surface/crystal.h \
    src/surface/layer.h \
    src/surface/surface.h \
    src/tools/configurator.h \
    src/tools/handbook.h \
    src/tools/runner.h

OTHER_FILES += \
    .gitignore \
    handbook.cnf
