/********************************************************************************
** Form generated from reading UI file 'tmainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TMAINWINDOW_H
#define UI_TMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <trobotwidget.h>

QT_BEGIN_NAMESPACE

class Ui_TMainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_14;
    QComboBox *comboBox;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton_XY_PLane;
    QPushButton *pushButton_YZ_Plane;
    QPushButton *pushButton_XZ_PLane;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_6;
    QSpinBox *spinBox_JT1;
    QSpinBox *spinBox_JT2;
    QSpinBox *spinBox_JT3;
    QSpinBox *spinBox_JT4;
    QSpinBox *spinBox_JT5;
    QSpinBox *spinBox_JT6;
    QSpacerItem *horizontalSpacer_5;
    TRobotWidget *widget_Robot;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer;
    QFrame *frame;
    QGridLayout *gridLayout_3;
    QSpinBox *spinBox_reserv;
    QLabel *label_13;
    QLabel *label_15;
    QLabel *label;
    QSpinBox *spinBox_X;
    QLabel *label_2;
    QSpinBox *spinBox_Z;
    QLabel *label_5;
    QLabel *label_4;
    QSpinBox *spinBox_Y;
    QSpinBox *spinBox_rx;
    QSpinBox *spinBox_ry;
    QLabel *label_6;
    QLabel *label_3;
    QPushButton *pushButton_Move;
    QSpinBox *spinBox_rz;
    QPushButton *pushButton_2;
    QHBoxLayout *horizontalLayout_4;
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout_2;
    QSpacerItem *verticalSpacer_4;
    QSpacerItem *verticalSpacer;
    QSpacerItem *verticalSpacer_2;
    QLabel *label_17;
    QSpinBox *spinBox_Step;
    QLabel *label_7;
    QPushButton *pushButton_x_minus;
    QPushButton *pushButton_y_plus;
    QLabel *label_8;
    QPushButton *pushButton_z_plus;
    QPushButton *pushButton_x_plus;
    QPushButton *pushButton_y_minus;
    QPushButton *pushButton_ry_plus;
    QPushButton *pushButton_z_minus;
    QLabel *label_9;
    QPushButton *pushButton_rx_plus;
    QLabel *label_10;
    QPushButton *pushButton_rz_plus;
    QPushButton *pushButton_rx_minus;
    QPushButton *pushButton_ry_minus;
    QLabel *label_12;
    QLabel *label_11;
    QPushButton *pushButton_rz_minus;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *pushButton;
    QDoubleSpinBox *doubleSpinBox_Depart;
    QPushButton *pushButton_ZERO;
    QPlainTextEdit *plainTextEdit;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *TMainWindow)
    {
        if (TMainWindow->objectName().isEmpty())
            TMainWindow->setObjectName(QStringLiteral("TMainWindow"));
        TMainWindow->resize(1146, 845);
        QFont font;
        font.setPointSize(12);
        TMainWindow->setFont(font);
        centralWidget = new QWidget(TMainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_14 = new QLabel(centralWidget);
        label_14->setObjectName(QStringLiteral("label_14"));

        horizontalLayout_5->addWidget(label_14);

        comboBox = new QComboBox(centralWidget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QStringLiteral("comboBox"));

        horizontalLayout_5->addWidget(comboBox);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout_5);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        pushButton_XY_PLane = new QPushButton(centralWidget);
        pushButton_XY_PLane->setObjectName(QStringLiteral("pushButton_XY_PLane"));
        pushButton_XY_PLane->setMinimumSize(QSize(40, 40));
        pushButton_XY_PLane->setMaximumSize(QSize(40, 40));
        pushButton_XY_PLane->setIconSize(QSize(40, 40));

        horizontalLayout_3->addWidget(pushButton_XY_PLane);

        pushButton_YZ_Plane = new QPushButton(centralWidget);
        pushButton_YZ_Plane->setObjectName(QStringLiteral("pushButton_YZ_Plane"));
        pushButton_YZ_Plane->setMinimumSize(QSize(40, 40));
        pushButton_YZ_Plane->setMaximumSize(QSize(40, 40));

        horizontalLayout_3->addWidget(pushButton_YZ_Plane);

        pushButton_XZ_PLane = new QPushButton(centralWidget);
        pushButton_XZ_PLane->setObjectName(QStringLiteral("pushButton_XZ_PLane"));
        pushButton_XZ_PLane->setMinimumSize(QSize(40, 40));
        pushButton_XZ_PLane->setMaximumSize(QSize(40, 40));

        horizontalLayout_3->addWidget(pushButton_XZ_PLane);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        spinBox_JT1 = new QSpinBox(centralWidget);
        spinBox_JT1->setObjectName(QStringLiteral("spinBox_JT1"));
        spinBox_JT1->setMinimumSize(QSize(100, 0));
        spinBox_JT1->setMaximum(180);

        horizontalLayout_6->addWidget(spinBox_JT1);

        spinBox_JT2 = new QSpinBox(centralWidget);
        spinBox_JT2->setObjectName(QStringLiteral("spinBox_JT2"));
        spinBox_JT2->setMinimumSize(QSize(100, 0));
        spinBox_JT2->setMaximum(180);

        horizontalLayout_6->addWidget(spinBox_JT2);

        spinBox_JT3 = new QSpinBox(centralWidget);
        spinBox_JT3->setObjectName(QStringLiteral("spinBox_JT3"));
        spinBox_JT3->setMinimumSize(QSize(100, 0));
        spinBox_JT3->setMaximum(180);

        horizontalLayout_6->addWidget(spinBox_JT3);

        spinBox_JT4 = new QSpinBox(centralWidget);
        spinBox_JT4->setObjectName(QStringLiteral("spinBox_JT4"));
        spinBox_JT4->setMinimumSize(QSize(100, 0));
        spinBox_JT4->setMaximum(180);

        horizontalLayout_6->addWidget(spinBox_JT4);

        spinBox_JT5 = new QSpinBox(centralWidget);
        spinBox_JT5->setObjectName(QStringLiteral("spinBox_JT5"));
        spinBox_JT5->setMinimumSize(QSize(100, 0));
        spinBox_JT5->setMaximum(180);

        horizontalLayout_6->addWidget(spinBox_JT5);

        spinBox_JT6 = new QSpinBox(centralWidget);
        spinBox_JT6->setObjectName(QStringLiteral("spinBox_JT6"));
        spinBox_JT6->setMinimumSize(QSize(100, 0));
        spinBox_JT6->setMaximum(180);

        horizontalLayout_6->addWidget(spinBox_JT6);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_5);


        verticalLayout->addLayout(horizontalLayout_6);

        widget_Robot = new TRobotWidget(centralWidget);
        widget_Robot->setObjectName(QStringLiteral("widget_Robot"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget_Robot->sizePolicy().hasHeightForWidth());
        widget_Robot->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(widget_Robot);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 0, 1, 1);

        frame = new QFrame(centralWidget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_3 = new QGridLayout(frame);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        spinBox_reserv = new QSpinBox(frame);
        spinBox_reserv->setObjectName(QStringLiteral("spinBox_reserv"));

        gridLayout_3->addWidget(spinBox_reserv, 7, 1, 1, 1);

        label_13 = new QLabel(frame);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setMinimumSize(QSize(0, 28));
        label_13->setMaximumSize(QSize(16777215, 28));
        label_13->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_13, 0, 0, 1, 8);

        label_15 = new QLabel(frame);
        label_15->setObjectName(QStringLiteral("label_15"));

        gridLayout_3->addWidget(label_15, 7, 0, 1, 1);

        label = new QLabel(frame);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(150, 0));
        label->setMaximumSize(QSize(150, 16777215));

        gridLayout_3->addWidget(label, 1, 0, 1, 1);

        spinBox_X = new QSpinBox(frame);
        spinBox_X->setObjectName(QStringLiteral("spinBox_X"));
        spinBox_X->setMinimumSize(QSize(120, 0));
        spinBox_X->setMinimum(-1000);
        spinBox_X->setMaximum(1000);

        gridLayout_3->addWidget(spinBox_X, 1, 1, 1, 1);

        label_2 = new QLabel(frame);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMinimumSize(QSize(150, 0));
        label_2->setMaximumSize(QSize(150, 16777215));

        gridLayout_3->addWidget(label_2, 1, 3, 1, 1);

        spinBox_Z = new QSpinBox(frame);
        spinBox_Z->setObjectName(QStringLiteral("spinBox_Z"));
        spinBox_Z->setMinimumSize(QSize(120, 0));
        spinBox_Z->setMinimum(-360);
        spinBox_Z->setMaximum(360);

        gridLayout_3->addWidget(spinBox_Z, 2, 1, 1, 1);

        label_5 = new QLabel(frame);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setMinimumSize(QSize(150, 0));
        label_5->setMaximumSize(QSize(150, 16777215));

        gridLayout_3->addWidget(label_5, 2, 3, 1, 1);

        label_4 = new QLabel(frame);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setMinimumSize(QSize(150, 0));

        gridLayout_3->addWidget(label_4, 2, 0, 1, 1);

        spinBox_Y = new QSpinBox(frame);
        spinBox_Y->setObjectName(QStringLiteral("spinBox_Y"));
        spinBox_Y->setMinimumSize(QSize(100, 0));
        spinBox_Y->setMinimum(-360);
        spinBox_Y->setMaximum(360);

        gridLayout_3->addWidget(spinBox_Y, 1, 4, 1, 1);

        spinBox_rx = new QSpinBox(frame);
        spinBox_rx->setObjectName(QStringLiteral("spinBox_rx"));
        spinBox_rx->setMinimumSize(QSize(120, 0));
        spinBox_rx->setMinimum(-360);
        spinBox_rx->setMaximum(360);

        gridLayout_3->addWidget(spinBox_rx, 2, 4, 1, 1);

        spinBox_ry = new QSpinBox(frame);
        spinBox_ry->setObjectName(QStringLiteral("spinBox_ry"));
        spinBox_ry->setMinimumSize(QSize(120, 0));
        spinBox_ry->setMinimum(-360);
        spinBox_ry->setMaximum(360);

        gridLayout_3->addWidget(spinBox_ry, 5, 1, 1, 2);

        label_6 = new QLabel(frame);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setMinimumSize(QSize(150, 0));
        label_6->setMaximumSize(QSize(150, 16777215));

        gridLayout_3->addWidget(label_6, 5, 3, 1, 1);

        label_3 = new QLabel(frame);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setMinimumSize(QSize(150, 0));
        label_3->setMaximumSize(QSize(150, 16777215));

        gridLayout_3->addWidget(label_3, 5, 0, 1, 1);

        pushButton_Move = new QPushButton(frame);
        pushButton_Move->setObjectName(QStringLiteral("pushButton_Move"));

        gridLayout_3->addWidget(pushButton_Move, 7, 3, 1, 1);

        spinBox_rz = new QSpinBox(frame);
        spinBox_rz->setObjectName(QStringLiteral("spinBox_rz"));
        spinBox_rz->setMinimumSize(QSize(120, 0));
        spinBox_rz->setMinimum(-360);
        spinBox_rz->setMaximum(360);

        gridLayout_3->addWidget(spinBox_rz, 5, 4, 1, 1);

        pushButton_2 = new QPushButton(frame);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        gridLayout_3->addWidget(pushButton_2, 7, 4, 1, 1);


        gridLayout->addWidget(frame, 0, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);


        horizontalLayout_2->addLayout(verticalLayout);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_4, 6, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 12, 1, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 180, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_2->addItem(verticalSpacer_2, 10, 1, 1, 1);

        label_17 = new QLabel(centralWidget);
        label_17->setObjectName(QStringLiteral("label_17"));

        gridLayout_2->addWidget(label_17, 7, 0, 1, 1);

        spinBox_Step = new QSpinBox(centralWidget);
        spinBox_Step->setObjectName(QStringLiteral("spinBox_Step"));
        spinBox_Step->setMinimum(-180);
        spinBox_Step->setMaximum(180);

        gridLayout_2->addWidget(spinBox_Step, 7, 1, 1, 2);

        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setMaximumSize(QSize(100, 100));
        label_7->setFont(font);
        label_7->setStyleSheet(QStringLiteral("background-color:white"));
        label_7->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_7, 0, 1, 1, 1);

        pushButton_x_minus = new QPushButton(centralWidget);
        pushButton_x_minus->setObjectName(QStringLiteral("pushButton_x_minus"));
        pushButton_x_minus->setMinimumSize(QSize(40, 40));
        pushButton_x_minus->setMaximumSize(QSize(40, 40));

        gridLayout_2->addWidget(pushButton_x_minus, 0, 2, 1, 1);

        pushButton_y_plus = new QPushButton(centralWidget);
        pushButton_y_plus->setObjectName(QStringLiteral("pushButton_y_plus"));
        pushButton_y_plus->setMinimumSize(QSize(40, 40));
        pushButton_y_plus->setMaximumSize(QSize(40, 40));

        gridLayout_2->addWidget(pushButton_y_plus, 1, 0, 1, 1);

        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setFont(font);
        label_8->setStyleSheet(QStringLiteral("background-color:white"));
        label_8->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_8, 1, 1, 1, 1);

        pushButton_z_plus = new QPushButton(centralWidget);
        pushButton_z_plus->setObjectName(QStringLiteral("pushButton_z_plus"));
        pushButton_z_plus->setMinimumSize(QSize(40, 40));
        pushButton_z_plus->setMaximumSize(QSize(40, 40));

        gridLayout_2->addWidget(pushButton_z_plus, 2, 0, 1, 1);

        pushButton_x_plus = new QPushButton(centralWidget);
        pushButton_x_plus->setObjectName(QStringLiteral("pushButton_x_plus"));
        pushButton_x_plus->setMinimumSize(QSize(40, 40));
        pushButton_x_plus->setMaximumSize(QSize(40, 40));

        gridLayout_2->addWidget(pushButton_x_plus, 0, 0, 1, 1);

        pushButton_y_minus = new QPushButton(centralWidget);
        pushButton_y_minus->setObjectName(QStringLiteral("pushButton_y_minus"));
        pushButton_y_minus->setMinimumSize(QSize(40, 40));
        pushButton_y_minus->setMaximumSize(QSize(40, 40));

        gridLayout_2->addWidget(pushButton_y_minus, 1, 2, 1, 1);

        pushButton_ry_plus = new QPushButton(centralWidget);
        pushButton_ry_plus->setObjectName(QStringLiteral("pushButton_ry_plus"));
        pushButton_ry_plus->setMinimumSize(QSize(40, 40));
        pushButton_ry_plus->setMaximumSize(QSize(40, 40));

        gridLayout_2->addWidget(pushButton_ry_plus, 4, 0, 1, 1);

        pushButton_z_minus = new QPushButton(centralWidget);
        pushButton_z_minus->setObjectName(QStringLiteral("pushButton_z_minus"));
        pushButton_z_minus->setMinimumSize(QSize(40, 40));
        pushButton_z_minus->setMaximumSize(QSize(40, 40));

        gridLayout_2->addWidget(pushButton_z_minus, 2, 2, 1, 1);

        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setFont(font);
        label_9->setStyleSheet(QStringLiteral("background-color:white"));
        label_9->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_9, 2, 1, 1, 1);

        pushButton_rx_plus = new QPushButton(centralWidget);
        pushButton_rx_plus->setObjectName(QStringLiteral("pushButton_rx_plus"));
        pushButton_rx_plus->setMinimumSize(QSize(40, 40));
        pushButton_rx_plus->setMaximumSize(QSize(40, 40));

        gridLayout_2->addWidget(pushButton_rx_plus, 3, 0, 1, 1);

        label_10 = new QLabel(centralWidget);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setFont(font);
        label_10->setStyleSheet(QStringLiteral("background-color:white"));
        label_10->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_10, 3, 1, 1, 1);

        pushButton_rz_plus = new QPushButton(centralWidget);
        pushButton_rz_plus->setObjectName(QStringLiteral("pushButton_rz_plus"));
        pushButton_rz_plus->setMinimumSize(QSize(40, 40));
        pushButton_rz_plus->setMaximumSize(QSize(40, 40));

        gridLayout_2->addWidget(pushButton_rz_plus, 5, 0, 1, 1);

        pushButton_rx_minus = new QPushButton(centralWidget);
        pushButton_rx_minus->setObjectName(QStringLiteral("pushButton_rx_minus"));
        pushButton_rx_minus->setMinimumSize(QSize(40, 40));
        pushButton_rx_minus->setMaximumSize(QSize(40, 40));

        gridLayout_2->addWidget(pushButton_rx_minus, 3, 2, 1, 1);

        pushButton_ry_minus = new QPushButton(centralWidget);
        pushButton_ry_minus->setObjectName(QStringLiteral("pushButton_ry_minus"));
        pushButton_ry_minus->setMinimumSize(QSize(40, 40));
        pushButton_ry_minus->setMaximumSize(QSize(40, 40));

        gridLayout_2->addWidget(pushButton_ry_minus, 4, 2, 1, 1);

        label_12 = new QLabel(centralWidget);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setFont(font);
        label_12->setStyleSheet(QStringLiteral("background-color:white"));
        label_12->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_12, 5, 1, 1, 1);

        label_11 = new QLabel(centralWidget);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setFont(font);
        label_11->setStyleSheet(QStringLiteral("background-color:white"));
        label_11->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_11, 4, 1, 1, 1);

        pushButton_rz_minus = new QPushButton(centralWidget);
        pushButton_rz_minus->setObjectName(QStringLiteral("pushButton_rz_minus"));
        pushButton_rz_minus->setMinimumSize(QSize(40, 40));
        pushButton_rz_minus->setMaximumSize(QSize(40, 40));

        gridLayout_2->addWidget(pushButton_rz_minus, 5, 2, 1, 1);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout_7->addWidget(pushButton);

        doubleSpinBox_Depart = new QDoubleSpinBox(centralWidget);
        doubleSpinBox_Depart->setObjectName(QStringLiteral("doubleSpinBox_Depart"));
        doubleSpinBox_Depart->setMinimumSize(QSize(100, 0));

        horizontalLayout_7->addWidget(doubleSpinBox_Depart);


        gridLayout_2->addLayout(horizontalLayout_7, 9, 0, 1, 3);

        pushButton_ZERO = new QPushButton(centralWidget);
        pushButton_ZERO->setObjectName(QStringLiteral("pushButton_ZERO"));

        gridLayout_2->addWidget(pushButton_ZERO, 11, 0, 1, 3);


        horizontalLayout->addLayout(gridLayout_2);


        horizontalLayout_4->addLayout(horizontalLayout);


        horizontalLayout_2->addLayout(horizontalLayout_4);


        verticalLayout_2->addLayout(horizontalLayout_2);

        plainTextEdit = new QPlainTextEdit(centralWidget);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(plainTextEdit->sizePolicy().hasHeightForWidth());
        plainTextEdit->setSizePolicy(sizePolicy1);
        plainTextEdit->setMaximumSize(QSize(16777215, 60));

        verticalLayout_2->addWidget(plainTextEdit);

        TMainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(TMainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1146, 21));
        TMainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(TMainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        TMainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(TMainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        TMainWindow->setStatusBar(statusBar);

        retranslateUi(TMainWindow);

        QMetaObject::connectSlotsByName(TMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *TMainWindow)
    {
        TMainWindow->setWindowTitle(QApplication::translate("TMainWindow", "TMainWindow", nullptr));
        label_14->setText(QApplication::translate("TMainWindow", " MOTION TYPE", nullptr));
        comboBox->setItemText(0, QApplication::translate("TMainWindow", "JOINT", nullptr));
        comboBox->setItemText(1, QApplication::translate("TMainWindow", "BASE", nullptr));
        comboBox->setItemText(2, QApplication::translate("TMainWindow", "TOOl", nullptr));

        pushButton_XY_PLane->setText(QApplication::translate("TMainWindow", "XY", nullptr));
        pushButton_YZ_Plane->setText(QApplication::translate("TMainWindow", "YZ", nullptr));
        pushButton_XZ_PLane->setText(QApplication::translate("TMainWindow", "XZ", nullptr));
        label_13->setText(QApplication::translate("TMainWindow", "Coord", nullptr));
        label_15->setText(QApplication::translate("TMainWindow", "reserv", nullptr));
        label->setText(QApplication::translate("TMainWindow", "1/X", nullptr));
        label_2->setText(QApplication::translate("TMainWindow", "2/Y", nullptr));
        label_5->setText(QApplication::translate("TMainWindow", "4/rx", nullptr));
        label_4->setText(QApplication::translate("TMainWindow", "3/Z", nullptr));
        label_6->setText(QApplication::translate("TMainWindow", "6/rz", nullptr));
        label_3->setText(QApplication::translate("TMainWindow", "5/ry", nullptr));
        pushButton_Move->setText(QApplication::translate("TMainWindow", "Move", nullptr));
        pushButton_2->setText(QApplication::translate("TMainWindow", "Stop", nullptr));
        label_17->setText(QApplication::translate("TMainWindow", "Setp", nullptr));
        label_7->setText(QApplication::translate("TMainWindow", "1/x", nullptr));
        pushButton_x_minus->setText(QApplication::translate("TMainWindow", "-", nullptr));
        pushButton_y_plus->setText(QApplication::translate("TMainWindow", "+", nullptr));
        label_8->setText(QApplication::translate("TMainWindow", "2/y", nullptr));
        pushButton_z_plus->setText(QApplication::translate("TMainWindow", "+", nullptr));
        pushButton_x_plus->setText(QApplication::translate("TMainWindow", "+", nullptr));
        pushButton_y_minus->setText(QApplication::translate("TMainWindow", "-", nullptr));
        pushButton_ry_plus->setText(QApplication::translate("TMainWindow", "+", nullptr));
        pushButton_z_minus->setText(QApplication::translate("TMainWindow", "-", nullptr));
        label_9->setText(QApplication::translate("TMainWindow", "3/z", nullptr));
        pushButton_rx_plus->setText(QApplication::translate("TMainWindow", "+", nullptr));
        label_10->setText(QApplication::translate("TMainWindow", "4/rx", nullptr));
        pushButton_rz_plus->setText(QApplication::translate("TMainWindow", "+", nullptr));
        pushButton_rx_minus->setText(QApplication::translate("TMainWindow", "-", nullptr));
        pushButton_ry_minus->setText(QApplication::translate("TMainWindow", "-", nullptr));
        label_12->setText(QApplication::translate("TMainWindow", "6/rz", nullptr));
        label_11->setText(QApplication::translate("TMainWindow", "5/ry", nullptr));
        pushButton_rz_minus->setText(QApplication::translate("TMainWindow", "-", nullptr));
        pushButton->setText(QApplication::translate("TMainWindow", "Depart", nullptr));
        pushButton_ZERO->setText(QApplication::translate("TMainWindow", "SET ZERO", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TMainWindow: public Ui_TMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TMAINWINDOW_H
