#-------------------------------------------------
#
# Project created by QtCreator 2024-12-18T08:34:21
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RobotConnection
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


CONFIG += resources_big

SOURCES += \
    OcctGlTools.cpp \
    OcctQtViewer.cpp \
        main.cpp \
        tmainwindow.cpp \
    trobotwidget.cpp \
    trobotmotion.cpp \
    vars.cpp \
    trobotmodel.cpp \
    expressschema.cpp \
    stepfile.cpp \
    tpointdialog.cpp

HEADERS += \
    OcctGlTools.h \
    OcctQtViewer.h \
        tmainwindow.h \
    trobotwidget.h \
    trobotmotion.h \
    vars.h \
    trobotmodel.h \
    expressschema.h \
    stepfile.h \
    tpointdialog.h

FORMS += \
        tmainwindow.ui \
    tpointdialog.ui

LIBS += -lOpengl32
LIBS += -lws2_32

RESOURCES += \
    res.qrc

INCLUDEPATH += j:\OCCT_7.8.0\dev\build\inc

#LIBS +=  j:\Qt\Qt5.13.0\5.13.0\mingw73_64\bin\libgcc_s_seh-1.dll

LIBS +=  j:\OCCT_7.8.0\dev\build\win64\gcc\bin\libTKernel.dll
LIBS +=  j:\OCCT_7.8.0\dev\build\win64\gcc\bin\libTKGeomAlgo.dll
LIBS +=  j:\OCCT_7.8.0\dev\build\win64\gcc\bin\libTKGeomBase.dll
LIBS +=  j:\OCCT_7.8.0\dev\build\win64\gcc\bin\libTKG2d.dll
LIBS +=  j:\OCCT_7.8.0\dev\build\win64\gcc\bin\libTKV3d.dll
LIBS +=  j:\OCCT_7.8.0\dev\build\win64\gcc\bin\libTKHLR.dll
LIBS +=  j:\OCCT_7.8.0\dev\build\win64\gcc\bin\libTKService.dll
LIBS +=  j:\OCCT_7.8.0\dev\build\win64\gcc\bin\libTKMath.dll
LIBS +=  j:\OCCT_7.8.0\dev\build\win64\gcc\bin\libTKBRep.dll
LIBS +=  j:\OCCT_7.8.0\dev\build\win64\gcc\bin\libTKTopAlgo.dll
LIBS +=  j:\OCCT_7.8.0\dev\build\win64\gcc\bin\libTKOpenGl.dll
LIBS +=  j:\OCCT_7.8.0\dev\build\win64\gcc\bin\libTKPrim.dll
LIBS +=  j:\OCCT_7.8.0\dev\build\win64\gcc\bin\libTKOpenGlTest.dll
LIBS +=  j:\OCCT_7.8.0\dev\build\win64\gcc\bin\libTKXSBase.dll
LIBS +=  j:\OCCT_7.8.0\dev\build\win64\gcc\bin\libTKG3d.dll
LIBS +=  j:\OCCT_7.8.0\dev\build\win64\gcc\bin\libTKMesh.dll
LIBS +=  j:\OCCT_7.8.0\dev\build\win64\gcc\bin\libTKQADraw.dll
LIBS +=  j:\OCCT_7.8.0\dev\build\win64\gcc\bin\libTKCDF.dll
LIBS +=  j:\OCCT_7.8.0\dev\build\win64\gcc\bin\libTKCAF.dll
LIBS +=  j:\OCCT_7.8.0\dev\build\win64\gcc\bin\libTKBRep.dll
LIBS +=  j:\OCCT_7.8.0\dev\build\win64\gcc\bin\libTKBool.dll
LIBS +=  j:\OCCT_7.8.0\dev\build\win64\gcc\bin\libTKBO.dll
LIBS +=  j:\OCCT_7.8.0\dev\build\win64\gcc\bin\libTKBinXCAF.dll
LIBS +=  j:\OCCT_7.8.0\dev\build\win64\gcc\bin\libTKBinTObj.dll
LIBS +=  j:\OCCT_7.8.0\dev\build\win64\gcc\bin\libTKBinL.dll
LIBS +=  j:\OCCT_7.8.0\dev\build\win64\gcc\bin\libTKBin.dll
LIBS +=  j:\OCCT_7.8.0\dev\build\win64\gcc\bin\libTKDE.dll
LIBS +=  j:\OCCT_7.8.0\dev\build\win64\gcc\bin\libTKHLR.dll
LIBS +=  j:\OCCT_7.8.0\dev\build\win64\gcc\bin\libTKDCAF.dll
LIBS +=  j:\OCCT_7.8.0\dev\build\win64\gcc\bin\libTKDEGLTF.dll
LIBS +=  j:\OCCT_7.8.0\dev\build\win64\gcc\bin\libTKDE.dll
LIBS +=  j:\OCCT_7.8.0\dev\build\win64\gcc\bin\libTKDECascade.dll
LIBS +=  j:\OCCT_7.8.0\dev\build\win64\gcc\bin\libTKDEGLTF.dll
LIBS +=  j:\OCCT_7.8.0\dev\build\win64\gcc\bin\libTKDEIGES.dll
LIBS +=  j:\OCCT_7.8.0\dev\build\win64\gcc\bin\libTKDEOBJ.dll
LIBS +=  j:\OCCT_7.8.0\dev\build\win64\gcc\bin\libTKDEPLY.dll
LIBS +=  j:\OCCT_7.8.0\dev\build\win64\gcc\bin\libTKDraw.dll
LIBS +=  j:\OCCT_7.8.0\dev\build\win64\gcc\bin\libTKShHealing.dll
LIBS +=  j:\OCCT_7.8.0\dev\build\win64\gcc\bin\libTKService.dll
LIBS +=  j:\OCCT_7.8.0\dev\build\win64\gcc\bin\libTKXSDRAWSTEP.dll
LIBS +=  j:\OCCT_7.8.0\dev\build\win64\gcc\bin\libTKDESTEP.dll
