QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    AdapterWidget.cpp \
    QtOsgView.cpp \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    AdapterWidget.h \
    MainWindow.h \
    QtOsgView.h

FORMS += \
    MainWindow.ui



INCLUDEPATH += $$PWD/../../OpenSceneGraph/include
DEPENDPATH += $$PWD/../../OpenSceneGraph/include

INCLUDEPATH += $$PWD/../../OpenSceneGraph/OutPut/include
DEPENDPATH += $$PWD/../../OpenSceneGraph/OutPut/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../OpenSceneGraph/OutPut/lib/ -losgDB
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../OpenSceneGraph/OutPut/lib/ -losgDBd

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../OpenSceneGraph/OutPut/lib/ -losg
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../OpenSceneGraph/OutPut/lib/ -losgd

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../OpenSceneGraph/OutPut/lib/ -losgUtil
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../OpenSceneGraph/OutPut/lib/ -losgUtild

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../OpenSceneGraph/OutPut/lib/ -losgViewer
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../OpenSceneGraph/OutPut/lib/ -losgViewerd

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../OpenSceneGraph/OutPut/lib/ -losgGA
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../OpenSceneGraph/OutPut/lib/ -losgGAd

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../OpenSceneGraph/OutPut/lib/ -lOpenThreadsd
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../OpenSceneGraph/OutPut/lib/ -lOpenThreadsd
