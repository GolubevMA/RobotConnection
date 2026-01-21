/********************************************************************************
** Form generated from reading UI file 'formremote.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMREMOTE_H
#define UI_FORMREMOTE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FormRemote
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_14;
    QComboBox *comboBox;
    QSpacerItem *horizontalSpacer_2;
    QFrame *frame_2;
    QGridLayout *gridLayout_4;
    QSpinBox *spinBox_Speed;
    QPushButton *pushButton_2;
    QPushButton *pushButton_Move;
    QLabel *label_13;
    QGridLayout *gridLayout_2;
    QLabel *label_17;
    QPushButton *pushButton_rz_minus;
    QSpinBox *spinBox_Step;
    QPushButton *pushButton_y_minus;
    QPushButton *pushButton_y_plus;
    QPushButton *pushButton_rx_minus;
    QPushButton *pushButton_rx_plus;
    QPushButton *pushButton_rz_plus;
    QLabel *label_7;
    QLabel *label_12;
    QPushButton *pushButton_ry_minus;
    QLabel *label_9;
    QPushButton *pushButton_ry_plus;
    QPushButton *pushButton_z_plus;
    QLabel *label_8;
    QPushButton *pushButton_x_plus;
    QPushButton *pushButton_z_minus;
    QPushButton *pushButton_x_minus;
    QLabel *label_10;
    QLabel *label_11;
    QFrame *frame_Trac;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_6;
    QLabel *label_16;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_BuildStart;
    QPushButton *pushButton_BuildStop;
    QTableWidget *tableWidget_points;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_addPt;
    QPushButton *pushButton_RemovePt;
    QPushButton *pushButton_ChangePt;
    QPushButton *pushButton_ZERO;
    QSpacerItem *verticalSpacer;
    QFrame *frame;
    QGridLayout *gridLayout_3;
    QLabel *label_axis7;
    QLabel *label_axis1;
    QLabel *label_axis3;
    QLabel *label;
    QLabel *label_15;
    QLabel *label_4;
    QLabel *label_2;
    QLabel *label_axis2;
    QLabel *label_5;
    QLabel *label_axis4;
    QLabel *label_3;
    QLabel *label_axis5;
    QLabel *label_6;
    QLabel *label_axis6;

    void setupUi(QWidget *FormRemote)
    {
        if (FormRemote->objectName().isEmpty())
            FormRemote->setObjectName(QString::fromUtf8("FormRemote"));
        FormRemote->resize(550, 917);
        FormRemote->setMinimumSize(QSize(550, 0));
        QFont font;
        font.setPointSize(12);
        FormRemote->setFont(font);
        verticalLayout_2 = new QVBoxLayout(FormRemote);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_14 = new QLabel(FormRemote);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        horizontalLayout_5->addWidget(label_14);

        comboBox = new QComboBox(FormRemote);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        horizontalLayout_5->addWidget(comboBox);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout_5);

        frame_2 = new QFrame(FormRemote);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        gridLayout_4 = new QGridLayout(frame_2);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        spinBox_Speed = new QSpinBox(frame_2);
        spinBox_Speed->setObjectName(QString::fromUtf8("spinBox_Speed"));
        spinBox_Speed->setMinimum(1);
        spinBox_Speed->setMaximum(1000);
        spinBox_Speed->setValue(10);

        gridLayout_4->addWidget(spinBox_Speed, 1, 2, 1, 1);

        pushButton_2 = new QPushButton(frame_2);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setMinimumSize(QSize(100, 60));

        gridLayout_4->addWidget(pushButton_2, 5, 1, 2, 2);

        pushButton_Move = new QPushButton(frame_2);
        pushButton_Move->setObjectName(QString::fromUtf8("pushButton_Move"));
        pushButton_Move->setMinimumSize(QSize(0, 40));

        gridLayout_4->addWidget(pushButton_Move, 0, 1, 1, 2);

        label_13 = new QLabel(frame_2);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        gridLayout_4->addWidget(label_13, 1, 1, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_17 = new QLabel(frame_2);
        label_17->setObjectName(QString::fromUtf8("label_17"));

        gridLayout_2->addWidget(label_17, 6, 0, 1, 1);

        pushButton_rz_minus = new QPushButton(frame_2);
        pushButton_rz_minus->setObjectName(QString::fromUtf8("pushButton_rz_minus"));
        pushButton_rz_minus->setMinimumSize(QSize(40, 40));
        pushButton_rz_minus->setMaximumSize(QSize(40, 40));

        gridLayout_2->addWidget(pushButton_rz_minus, 5, 2, 1, 1);

        spinBox_Step = new QSpinBox(frame_2);
        spinBox_Step->setObjectName(QString::fromUtf8("spinBox_Step"));
        spinBox_Step->setMinimumSize(QSize(0, 28));
        spinBox_Step->setMinimum(-500);
        spinBox_Step->setMaximum(500);

        gridLayout_2->addWidget(spinBox_Step, 6, 1, 1, 2);

        pushButton_y_minus = new QPushButton(frame_2);
        pushButton_y_minus->setObjectName(QString::fromUtf8("pushButton_y_minus"));
        pushButton_y_minus->setMinimumSize(QSize(40, 40));
        pushButton_y_minus->setMaximumSize(QSize(40, 40));

        gridLayout_2->addWidget(pushButton_y_minus, 1, 2, 1, 1);

        pushButton_y_plus = new QPushButton(frame_2);
        pushButton_y_plus->setObjectName(QString::fromUtf8("pushButton_y_plus"));
        pushButton_y_plus->setMinimumSize(QSize(40, 40));
        pushButton_y_plus->setMaximumSize(QSize(40, 40));

        gridLayout_2->addWidget(pushButton_y_plus, 1, 0, 1, 1);

        pushButton_rx_minus = new QPushButton(frame_2);
        pushButton_rx_minus->setObjectName(QString::fromUtf8("pushButton_rx_minus"));
        pushButton_rx_minus->setMinimumSize(QSize(40, 40));
        pushButton_rx_minus->setMaximumSize(QSize(40, 40));

        gridLayout_2->addWidget(pushButton_rx_minus, 3, 2, 1, 1);

        pushButton_rx_plus = new QPushButton(frame_2);
        pushButton_rx_plus->setObjectName(QString::fromUtf8("pushButton_rx_plus"));
        pushButton_rx_plus->setMinimumSize(QSize(40, 40));
        pushButton_rx_plus->setMaximumSize(QSize(40, 40));

        gridLayout_2->addWidget(pushButton_rx_plus, 3, 0, 1, 1);

        pushButton_rz_plus = new QPushButton(frame_2);
        pushButton_rz_plus->setObjectName(QString::fromUtf8("pushButton_rz_plus"));
        pushButton_rz_plus->setMinimumSize(QSize(40, 40));
        pushButton_rz_plus->setMaximumSize(QSize(40, 40));

        gridLayout_2->addWidget(pushButton_rz_plus, 5, 0, 1, 1);

        label_7 = new QLabel(frame_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setMaximumSize(QSize(100, 100));
        label_7->setFont(font);
        label_7->setStyleSheet(QString::fromUtf8("background-color:white"));
        label_7->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_7, 0, 1, 1, 1);

        label_12 = new QLabel(frame_2);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setFont(font);
        label_12->setStyleSheet(QString::fromUtf8("background-color:white"));
        label_12->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_12, 5, 1, 1, 1);

        pushButton_ry_minus = new QPushButton(frame_2);
        pushButton_ry_minus->setObjectName(QString::fromUtf8("pushButton_ry_minus"));
        pushButton_ry_minus->setMinimumSize(QSize(40, 40));
        pushButton_ry_minus->setMaximumSize(QSize(40, 40));

        gridLayout_2->addWidget(pushButton_ry_minus, 4, 2, 1, 1);

        label_9 = new QLabel(frame_2);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setFont(font);
        label_9->setStyleSheet(QString::fromUtf8("background-color:white"));
        label_9->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_9, 2, 1, 1, 1);

        pushButton_ry_plus = new QPushButton(frame_2);
        pushButton_ry_plus->setObjectName(QString::fromUtf8("pushButton_ry_plus"));
        pushButton_ry_plus->setMinimumSize(QSize(40, 40));
        pushButton_ry_plus->setMaximumSize(QSize(40, 40));

        gridLayout_2->addWidget(pushButton_ry_plus, 4, 0, 1, 1);

        pushButton_z_plus = new QPushButton(frame_2);
        pushButton_z_plus->setObjectName(QString::fromUtf8("pushButton_z_plus"));
        pushButton_z_plus->setMinimumSize(QSize(40, 40));
        pushButton_z_plus->setMaximumSize(QSize(40, 40));

        gridLayout_2->addWidget(pushButton_z_plus, 2, 0, 1, 1);

        label_8 = new QLabel(frame_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setFont(font);
        label_8->setStyleSheet(QString::fromUtf8("background-color:white"));
        label_8->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_8, 1, 1, 1, 1);

        pushButton_x_plus = new QPushButton(frame_2);
        pushButton_x_plus->setObjectName(QString::fromUtf8("pushButton_x_plus"));
        pushButton_x_plus->setMinimumSize(QSize(40, 40));
        pushButton_x_plus->setMaximumSize(QSize(40, 40));

        gridLayout_2->addWidget(pushButton_x_plus, 0, 0, 1, 1);

        pushButton_z_minus = new QPushButton(frame_2);
        pushButton_z_minus->setObjectName(QString::fromUtf8("pushButton_z_minus"));
        pushButton_z_minus->setMinimumSize(QSize(40, 40));
        pushButton_z_minus->setMaximumSize(QSize(40, 40));

        gridLayout_2->addWidget(pushButton_z_minus, 2, 2, 1, 1);

        pushButton_x_minus = new QPushButton(frame_2);
        pushButton_x_minus->setObjectName(QString::fromUtf8("pushButton_x_minus"));
        pushButton_x_minus->setMinimumSize(QSize(40, 40));
        pushButton_x_minus->setMaximumSize(QSize(40, 40));

        gridLayout_2->addWidget(pushButton_x_minus, 0, 2, 1, 1);

        label_10 = new QLabel(frame_2);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setFont(font);
        label_10->setStyleSheet(QString::fromUtf8("background-color:white"));
        label_10->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_10, 3, 1, 1, 1);

        label_11 = new QLabel(frame_2);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setFont(font);
        label_11->setStyleSheet(QString::fromUtf8("background-color:white"));
        label_11->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_11, 4, 1, 1, 1);


        gridLayout_4->addLayout(gridLayout_2, 0, 3, 7, 1);

        frame_Trac = new QFrame(frame_2);
        frame_Trac->setObjectName(QString::fromUtf8("frame_Trac"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame_Trac->sizePolicy().hasHeightForWidth());
        frame_Trac->setSizePolicy(sizePolicy);
        frame_Trac->setFrameShape(QFrame::StyledPanel);
        frame_Trac->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(frame_Trac);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Maximum);

        verticalLayout->addItem(verticalSpacer_6);

        label_16 = new QLabel(frame_Trac);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_16);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        pushButton_BuildStart = new QPushButton(frame_Trac);
        pushButton_BuildStart->setObjectName(QString::fromUtf8("pushButton_BuildStart"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton_BuildStart->sizePolicy().hasHeightForWidth());
        pushButton_BuildStart->setSizePolicy(sizePolicy1);
        pushButton_BuildStart->setMinimumSize(QSize(0, 30));

        horizontalLayout_2->addWidget(pushButton_BuildStart);

        pushButton_BuildStop = new QPushButton(frame_Trac);
        pushButton_BuildStop->setObjectName(QString::fromUtf8("pushButton_BuildStop"));
        sizePolicy1.setHeightForWidth(pushButton_BuildStop->sizePolicy().hasHeightForWidth());
        pushButton_BuildStop->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(pushButton_BuildStop);


        verticalLayout->addLayout(horizontalLayout_2);

        tableWidget_points = new QTableWidget(frame_Trac);
        if (tableWidget_points->columnCount() < 3)
            tableWidget_points->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_points->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_points->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget_points->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        if (tableWidget_points->rowCount() < 3)
            tableWidget_points->setRowCount(3);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget_points->setVerticalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget_points->setVerticalHeaderItem(1, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget_points->setVerticalHeaderItem(2, __qtablewidgetitem5);
        tableWidget_points->setObjectName(QString::fromUtf8("tableWidget_points"));
        tableWidget_points->setMinimumSize(QSize(380, 0));

        verticalLayout->addWidget(tableWidget_points);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton_addPt = new QPushButton(frame_Trac);
        pushButton_addPt->setObjectName(QString::fromUtf8("pushButton_addPt"));
        pushButton_addPt->setMinimumSize(QSize(80, 28));

        horizontalLayout->addWidget(pushButton_addPt);

        pushButton_RemovePt = new QPushButton(frame_Trac);
        pushButton_RemovePt->setObjectName(QString::fromUtf8("pushButton_RemovePt"));
        pushButton_RemovePt->setMinimumSize(QSize(80, 28));

        horizontalLayout->addWidget(pushButton_RemovePt);

        pushButton_ChangePt = new QPushButton(frame_Trac);
        pushButton_ChangePt->setObjectName(QString::fromUtf8("pushButton_ChangePt"));
        pushButton_ChangePt->setMinimumSize(QSize(80, 0));
        pushButton_ChangePt->setMaximumSize(QSize(180, 16777215));

        horizontalLayout->addWidget(pushButton_ChangePt);


        verticalLayout->addLayout(horizontalLayout);


        gridLayout_4->addWidget(frame_Trac, 3, 1, 1, 2);

        pushButton_ZERO = new QPushButton(frame_2);
        pushButton_ZERO->setObjectName(QString::fromUtf8("pushButton_ZERO"));
        pushButton_ZERO->setMinimumSize(QSize(0, 40));

        gridLayout_4->addWidget(pushButton_ZERO, 2, 1, 1, 2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_4->addItem(verticalSpacer, 4, 2, 1, 1);


        verticalLayout_2->addWidget(frame_2);

        frame = new QFrame(FormRemote);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_3 = new QGridLayout(frame);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_axis7 = new QLabel(frame);
        label_axis7->setObjectName(QString::fromUtf8("label_axis7"));
        label_axis7->setMinimumSize(QSize(100, 28));
        label_axis7->setStyleSheet(QString::fromUtf8("background-color:white"));

        gridLayout_3->addWidget(label_axis7, 7, 1, 1, 1);

        label_axis1 = new QLabel(frame);
        label_axis1->setObjectName(QString::fromUtf8("label_axis1"));
        label_axis1->setMinimumSize(QSize(100, 28));
        label_axis1->setStyleSheet(QString::fromUtf8("background-color:white"));

        gridLayout_3->addWidget(label_axis1, 0, 1, 1, 1);

        label_axis3 = new QLabel(frame);
        label_axis3->setObjectName(QString::fromUtf8("label_axis3"));
        label_axis3->setStyleSheet(QString::fromUtf8("background-color:white"));

        gridLayout_3->addWidget(label_axis3, 2, 1, 1, 1);

        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(120, 0));
        label->setMaximumSize(QSize(150, 16777215));

        gridLayout_3->addWidget(label, 0, 0, 1, 1);

        label_15 = new QLabel(frame);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        gridLayout_3->addWidget(label_15, 7, 0, 1, 1);

        label_4 = new QLabel(frame);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setMinimumSize(QSize(120, 0));

        gridLayout_3->addWidget(label_4, 2, 0, 1, 1);

        label_2 = new QLabel(frame);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(100, 0));
        label_2->setMaximumSize(QSize(150, 16777215));

        gridLayout_3->addWidget(label_2, 1, 0, 1, 1);

        label_axis2 = new QLabel(frame);
        label_axis2->setObjectName(QString::fromUtf8("label_axis2"));
        label_axis2->setMinimumSize(QSize(100, 0));
        label_axis2->setStyleSheet(QString::fromUtf8("background-color:white"));

        gridLayout_3->addWidget(label_axis2, 1, 1, 1, 1);

        label_5 = new QLabel(frame);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setMinimumSize(QSize(100, 0));
        label_5->setMaximumSize(QSize(150, 16777215));

        gridLayout_3->addWidget(label_5, 0, 2, 1, 1);

        label_axis4 = new QLabel(frame);
        label_axis4->setObjectName(QString::fromUtf8("label_axis4"));
        label_axis4->setMinimumSize(QSize(100, 28));
        label_axis4->setStyleSheet(QString::fromUtf8("background-color:white"));

        gridLayout_3->addWidget(label_axis4, 0, 3, 1, 1);

        label_3 = new QLabel(frame);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMinimumSize(QSize(120, 0));
        label_3->setMaximumSize(QSize(150, 16777215));

        gridLayout_3->addWidget(label_3, 1, 2, 1, 1);

        label_axis5 = new QLabel(frame);
        label_axis5->setObjectName(QString::fromUtf8("label_axis5"));
        label_axis5->setMinimumSize(QSize(100, 28));
        label_axis5->setStyleSheet(QString::fromUtf8("background-color:white"));

        gridLayout_3->addWidget(label_axis5, 1, 3, 1, 1);

        label_6 = new QLabel(frame);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setMinimumSize(QSize(100, 0));
        label_6->setMaximumSize(QSize(150, 16777215));

        gridLayout_3->addWidget(label_6, 2, 2, 1, 1);

        label_axis6 = new QLabel(frame);
        label_axis6->setObjectName(QString::fromUtf8("label_axis6"));
        label_axis6->setMinimumSize(QSize(100, 0));
        label_axis6->setStyleSheet(QString::fromUtf8("background-color:white"));

        gridLayout_3->addWidget(label_axis6, 2, 3, 1, 1);


        verticalLayout_2->addWidget(frame);


        retranslateUi(FormRemote);

        QMetaObject::connectSlotsByName(FormRemote);
    } // setupUi

    void retranslateUi(QWidget *FormRemote)
    {
        FormRemote->setWindowTitle(QCoreApplication::translate("FormRemote", "Form", nullptr));
        label_14->setText(QCoreApplication::translate("FormRemote", " MOTION TYPE", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("FormRemote", "JOINT", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("FormRemote", "BASE", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("FormRemote", "TOOl", nullptr));

        pushButton_2->setText(QCoreApplication::translate("FormRemote", "Stop", nullptr));
        pushButton_Move->setText(QCoreApplication::translate("FormRemote", "Move", nullptr));
        label_13->setText(QCoreApplication::translate("FormRemote", "Speed", nullptr));
        label_17->setText(QCoreApplication::translate("FormRemote", "Setp", nullptr));
        pushButton_rz_minus->setText(QCoreApplication::translate("FormRemote", "-", nullptr));
        pushButton_y_minus->setText(QCoreApplication::translate("FormRemote", "-", nullptr));
        pushButton_y_plus->setText(QCoreApplication::translate("FormRemote", "+", nullptr));
        pushButton_rx_minus->setText(QCoreApplication::translate("FormRemote", "-", nullptr));
        pushButton_rx_plus->setText(QCoreApplication::translate("FormRemote", "+", nullptr));
        pushButton_rz_plus->setText(QCoreApplication::translate("FormRemote", "+", nullptr));
        label_7->setText(QCoreApplication::translate("FormRemote", "1/x", nullptr));
        label_12->setText(QCoreApplication::translate("FormRemote", "6/rz", nullptr));
        pushButton_ry_minus->setText(QCoreApplication::translate("FormRemote", "-", nullptr));
        label_9->setText(QCoreApplication::translate("FormRemote", "3/z", nullptr));
        pushButton_ry_plus->setText(QCoreApplication::translate("FormRemote", "+", nullptr));
        pushButton_z_plus->setText(QCoreApplication::translate("FormRemote", "+", nullptr));
        label_8->setText(QCoreApplication::translate("FormRemote", "2/y", nullptr));
        pushButton_x_plus->setText(QCoreApplication::translate("FormRemote", "+", nullptr));
        pushButton_z_minus->setText(QCoreApplication::translate("FormRemote", "-", nullptr));
        pushButton_x_minus->setText(QCoreApplication::translate("FormRemote", "-", nullptr));
        label_10->setText(QCoreApplication::translate("FormRemote", "4/rx", nullptr));
        label_11->setText(QCoreApplication::translate("FormRemote", "5/ry", nullptr));
        label_16->setText(QCoreApplication::translate("FormRemote", "Linear", nullptr));
        pushButton_BuildStart->setText(QCoreApplication::translate("FormRemote", "start", nullptr));
        pushButton_BuildStop->setText(QCoreApplication::translate("FormRemote", "stop", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_points->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("FormRemote", "X", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_points->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("FormRemote", "Y", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_points->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("FormRemote", "Z", nullptr));
        pushButton_addPt->setText(QCoreApplication::translate("FormRemote", "add", nullptr));
        pushButton_RemovePt->setText(QCoreApplication::translate("FormRemote", "remove", nullptr));
        pushButton_ChangePt->setText(QCoreApplication::translate("FormRemote", "change", nullptr));
        pushButton_ZERO->setText(QCoreApplication::translate("FormRemote", "SET ZERO", nullptr));
        label_axis7->setText(QString());
        label_axis1->setText(QString());
        label_axis3->setText(QString());
        label->setText(QCoreApplication::translate("FormRemote", "1/X", nullptr));
        label_15->setText(QCoreApplication::translate("FormRemote", "reserv", nullptr));
        label_4->setText(QCoreApplication::translate("FormRemote", "3/Z", nullptr));
        label_2->setText(QCoreApplication::translate("FormRemote", "2/Y", nullptr));
        label_axis2->setText(QString());
        label_5->setText(QCoreApplication::translate("FormRemote", "4/O", nullptr));
        label_axis4->setText(QString());
        label_3->setText(QCoreApplication::translate("FormRemote", "5/A", nullptr));
        label_axis5->setText(QString());
        label_6->setText(QCoreApplication::translate("FormRemote", "6/T", nullptr));
        label_axis6->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class FormRemote: public Ui_FormRemote {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMREMOTE_H
