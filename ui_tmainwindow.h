/********************************************************************************
** Form generated from reading UI file 'tmainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TMAINWINDOW_H
#define UI_TMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <modelform.h>
#include "autoscanerlform.h"
#include "formremote.h"
#include "occtqtviewer.h"
#include "voiceparseform.h"

QT_BEGIN_NAMESPACE

class Ui_TMainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QSplitter *splitter_4;
    QSplitter *splitter_3;
    ModelForm *widget_Model;
    AutoScanerlForm *widget_AutoScan;
    QSplitter *splitter;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_6;
    QSpinBox *spinBox_JT1;
    QSpinBox *spinBox_JT2;
    QSpinBox *spinBox_JT3;
    QSpinBox *spinBox_JT4;
    QSpinBox *spinBox_JT5;
    QSpinBox *spinBox_JT6;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *pushButton_Remote;
    OcctQtViewer *widget_Robot;
    QFrame *frame_Bottom;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_EncoderActive;
    QLabel *label_TubePosLabel;
    QLabel *label_TubePos;
    QLabel *label_13;
    QLabel *label_freq;
    QPushButton *pushButton_conn;
    QSpacerItem *horizontalSpacer_16;
    QSplitter *splitter_2;
    FormRemote *widget_Remote;
    VoiceParseForm *widget_Voice;
    QMenuBar *menuBar;
    QMenu *menu;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *TMainWindow)
    {
        if (TMainWindow->objectName().isEmpty())
            TMainWindow->setObjectName(QString::fromUtf8("TMainWindow"));
        TMainWindow->resize(1216, 694);
        QFont font;
        font.setPointSize(12);
        TMainWindow->setFont(font);
        centralWidget = new QWidget(TMainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        splitter_4 = new QSplitter(centralWidget);
        splitter_4->setObjectName(QString::fromUtf8("splitter_4"));
        splitter_4->setOrientation(Qt::Horizontal);
        splitter_3 = new QSplitter(splitter_4);
        splitter_3->setObjectName(QString::fromUtf8("splitter_3"));
        splitter_3->setOrientation(Qt::Vertical);
        widget_Model = new ModelForm(splitter_3);
        widget_Model->setObjectName(QString::fromUtf8("widget_Model"));
        splitter_3->addWidget(widget_Model);
        widget_AutoScan = new AutoScanerlForm(splitter_3);
        widget_AutoScan->setObjectName(QString::fromUtf8("widget_AutoScan"));
        widget_AutoScan->setMinimumSize(QSize(100, 0));
        splitter_3->addWidget(widget_AutoScan);
        splitter_4->addWidget(splitter_3);
        splitter = new QSplitter(splitter_4);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(layoutWidget);
        widget->setObjectName(QString::fromUtf8("widget"));

        verticalLayout->addWidget(widget);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        spinBox_JT1 = new QSpinBox(layoutWidget);
        spinBox_JT1->setObjectName(QString::fromUtf8("spinBox_JT1"));
        spinBox_JT1->setMinimumSize(QSize(100, 0));
        spinBox_JT1->setMinimum(-180);
        spinBox_JT1->setMaximum(180);

        horizontalLayout_6->addWidget(spinBox_JT1);

        spinBox_JT2 = new QSpinBox(layoutWidget);
        spinBox_JT2->setObjectName(QString::fromUtf8("spinBox_JT2"));
        spinBox_JT2->setMinimumSize(QSize(100, 0));
        spinBox_JT2->setMinimum(-180);
        spinBox_JT2->setMaximum(180);

        horizontalLayout_6->addWidget(spinBox_JT2);

        spinBox_JT3 = new QSpinBox(layoutWidget);
        spinBox_JT3->setObjectName(QString::fromUtf8("spinBox_JT3"));
        spinBox_JT3->setMinimumSize(QSize(100, 0));
        spinBox_JT3->setMinimum(-180);
        spinBox_JT3->setMaximum(180);

        horizontalLayout_6->addWidget(spinBox_JT3);

        spinBox_JT4 = new QSpinBox(layoutWidget);
        spinBox_JT4->setObjectName(QString::fromUtf8("spinBox_JT4"));
        spinBox_JT4->setMinimumSize(QSize(100, 0));
        spinBox_JT4->setMinimum(-180);
        spinBox_JT4->setMaximum(180);

        horizontalLayout_6->addWidget(spinBox_JT4);

        spinBox_JT5 = new QSpinBox(layoutWidget);
        spinBox_JT5->setObjectName(QString::fromUtf8("spinBox_JT5"));
        spinBox_JT5->setMinimumSize(QSize(100, 0));
        spinBox_JT5->setMinimum(-180);
        spinBox_JT5->setMaximum(180);

        horizontalLayout_6->addWidget(spinBox_JT5);

        spinBox_JT6 = new QSpinBox(layoutWidget);
        spinBox_JT6->setObjectName(QString::fromUtf8("spinBox_JT6"));
        spinBox_JT6->setMinimumSize(QSize(100, 0));
        spinBox_JT6->setMinimum(-180);
        spinBox_JT6->setMaximum(180);

        horizontalLayout_6->addWidget(spinBox_JT6);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_5);

        pushButton_Remote = new QPushButton(layoutWidget);
        pushButton_Remote->setObjectName(QString::fromUtf8("pushButton_Remote"));
        pushButton_Remote->setMinimumSize(QSize(0, 40));
        pushButton_Remote->setCheckable(true);

        horizontalLayout_6->addWidget(pushButton_Remote);


        verticalLayout->addLayout(horizontalLayout_6);

        widget_Robot = new OcctQtViewer(layoutWidget);
        widget_Robot->setObjectName(QString::fromUtf8("widget_Robot"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget_Robot->sizePolicy().hasHeightForWidth());
        widget_Robot->setSizePolicy(sizePolicy);
        widget_Robot->setMinimumSize(QSize(0, 100));

        verticalLayout->addWidget(widget_Robot);

        frame_Bottom = new QFrame(layoutWidget);
        frame_Bottom->setObjectName(QString::fromUtf8("frame_Bottom"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(frame_Bottom->sizePolicy().hasHeightForWidth());
        frame_Bottom->setSizePolicy(sizePolicy1);
        frame_Bottom->setMinimumSize(QSize(50, 50));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        QBrush brush1(QColor(0, 0, 0, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        QBrush brush2(QColor(120, 120, 120, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        frame_Bottom->setPalette(palette);
        QFont font1;
        font1.setFamily(QString::fromUtf8("Tahoma"));
        font1.setPointSize(10);
        frame_Bottom->setFont(font1);
        frame_Bottom->setAutoFillBackground(true);
        frame_Bottom->setFrameShape(QFrame::StyledPanel);
        frame_Bottom->setFrameShadow(QFrame::Raised);
        horizontalLayout_3 = new QHBoxLayout(frame_Bottom);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_EncoderActive = new QLabel(frame_Bottom);
        label_EncoderActive->setObjectName(QString::fromUtf8("label_EncoderActive"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_EncoderActive->sizePolicy().hasHeightForWidth());
        label_EncoderActive->setSizePolicy(sizePolicy2);
        label_EncoderActive->setMinimumSize(QSize(32, 32));
        label_EncoderActive->setPixmap(QPixmap(QString::fromUtf8(":/images/red_led_transparent.png")));

        horizontalLayout_3->addWidget(label_EncoderActive);

        label_TubePosLabel = new QLabel(frame_Bottom);
        label_TubePosLabel->setObjectName(QString::fromUtf8("label_TubePosLabel"));
        QSizePolicy sizePolicy3(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(label_TubePosLabel->sizePolicy().hasHeightForWidth());
        label_TubePosLabel->setSizePolicy(sizePolicy3);
        label_TubePosLabel->setMinimumSize(QSize(0, 0));

        horizontalLayout_3->addWidget(label_TubePosLabel);

        label_TubePos = new QLabel(frame_Bottom);
        label_TubePos->setObjectName(QString::fromUtf8("label_TubePos"));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(label_TubePos->sizePolicy().hasHeightForWidth());
        label_TubePos->setSizePolicy(sizePolicy4);
        label_TubePos->setMinimumSize(QSize(100, 0));
        QPalette palette1;
        QBrush brush3(QColor(0, 255, 0, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush3);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush3);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        label_TubePos->setPalette(palette1);
        QFont font2;
        font2.setFamily(QString::fromUtf8("Arial"));
        font2.setPointSize(16);
        font2.setBold(true);
        font2.setWeight(75);
        label_TubePos->setFont(font2);

        horizontalLayout_3->addWidget(label_TubePos);

        label_13 = new QLabel(frame_Bottom);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        horizontalLayout_3->addWidget(label_13);

        label_freq = new QLabel(frame_Bottom);
        label_freq->setObjectName(QString::fromUtf8("label_freq"));
        label_freq->setMinimumSize(QSize(100, 0));
        QFont font3;
        font3.setPointSize(16);
        label_freq->setFont(font3);
        label_freq->setStyleSheet(QString::fromUtf8("color:green"));

        horizontalLayout_3->addWidget(label_freq);

        pushButton_conn = new QPushButton(frame_Bottom);
        pushButton_conn->setObjectName(QString::fromUtf8("pushButton_conn"));

        horizontalLayout_3->addWidget(pushButton_conn);

        horizontalSpacer_16 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_16);


        verticalLayout->addWidget(frame_Bottom);

        splitter->addWidget(layoutWidget);
        splitter_2 = new QSplitter(splitter);
        splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
        splitter_2->setOrientation(Qt::Vertical);
        widget_Remote = new FormRemote(splitter_2);
        widget_Remote->setObjectName(QString::fromUtf8("widget_Remote"));
        sizePolicy.setHeightForWidth(widget_Remote->sizePolicy().hasHeightForWidth());
        widget_Remote->setSizePolicy(sizePolicy);
        widget_Remote->setMinimumSize(QSize(250, 100));
        widget_Remote->setMaximumSize(QSize(1000, 16777215));
        splitter_2->addWidget(widget_Remote);
        widget_Voice = new VoiceParseForm(splitter_2);
        widget_Voice->setObjectName(QString::fromUtf8("widget_Voice"));
        widget_Voice->setMinimumSize(QSize(0, 100));
        splitter_2->addWidget(widget_Voice);
        splitter->addWidget(splitter_2);
        splitter_4->addWidget(splitter);

        verticalLayout_2->addWidget(splitter_4);

        TMainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(TMainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1216, 21));
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        TMainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(TMainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        TMainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(TMainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        TMainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());

        retranslateUi(TMainWindow);

        QMetaObject::connectSlotsByName(TMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *TMainWindow)
    {
        TMainWindow->setWindowTitle(QCoreApplication::translate("TMainWindow", "TMainWindow", nullptr));
        pushButton_Remote->setText(QCoreApplication::translate("TMainWindow", "Hand", nullptr));
        label_TubePosLabel->setText(QCoreApplication::translate("TMainWindow", "\320\232\320\276\320\276\321\200\320\264\320\270\320\275\320\260\321\202\320\260 \321\200\320\276\320\261\320\276\321\202\320\260:", nullptr));
        label_TubePos->setText(QCoreApplication::translate("TMainWindow", "- - -", nullptr));
        label_13->setText(QCoreApplication::translate("TMainWindow", "\320\247\320\260\321\201\321\202\320\276\321\202\320\260 \320\236\320\237\320\240\320\236\320\241\320\220", nullptr));
        label_freq->setText(QCoreApplication::translate("TMainWindow", "----", nullptr));
        pushButton_conn->setText(QCoreApplication::translate("TMainWindow", "conn", nullptr));
        menu->setTitle(QCoreApplication::translate("TMainWindow", "\320\244\320\260\320\271\320\273", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TMainWindow: public Ui_TMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TMAINWINDOW_H
