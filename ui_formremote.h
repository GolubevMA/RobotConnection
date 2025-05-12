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
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FormRemote
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_14;
    QComboBox *comboBox;
    QSpacerItem *horizontalSpacer_2;
    QFrame *frame_2;
    QGridLayout *gridLayout_4;
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
    QSpacerItem *verticalSpacer;
    QDoubleSpinBox *doubleSpinBox_Depart;
    QPushButton *pushButton_2;
    QPushButton *pushButton_Move;
    QPushButton *pushButton_ZERO;
    QPushButton *pushButton;
    QPushButton *pushButton_linear;
    QFrame *frame;
    QGridLayout *gridLayout_3;
    QLabel *label_axis3;
    QLabel *label_axis5;
    QLabel *label_axis7;
    QLabel *label_axis2;
    QLabel *label_axis4;
    QLabel *label_axis6;
    QLabel *label_3;
    QLabel *label;
    QLabel *label_15;
    QLabel *label_axis1;
    QLabel *label_6;
    QLabel *label_4;
    QLabel *label_2;
    QLabel *label_5;

    void setupUi(QWidget *FormRemote)
    {
        if (FormRemote->objectName().isEmpty())
            FormRemote->setObjectName(QString::fromUtf8("FormRemote"));
        FormRemote->resize(476, 745);
        QFont font;
        font.setPointSize(12);
        FormRemote->setFont(font);
        verticalLayout = new QVBoxLayout(FormRemote);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
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


        verticalLayout->addLayout(horizontalLayout_5);

        frame_2 = new QFrame(FormRemote);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        gridLayout_4 = new QGridLayout(frame_2);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
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
        spinBox_Step->setMinimum(-180);
        spinBox_Step->setMaximum(180);

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


        gridLayout_4->addLayout(gridLayout_2, 0, 2, 7, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_4->addItem(verticalSpacer, 4, 1, 1, 1);

        doubleSpinBox_Depart = new QDoubleSpinBox(frame_2);
        doubleSpinBox_Depart->setObjectName(QString::fromUtf8("doubleSpinBox_Depart"));
        doubleSpinBox_Depart->setMinimumSize(QSize(100, 28));

        gridLayout_4->addWidget(doubleSpinBox_Depart, 1, 1, 1, 1);

        pushButton_2 = new QPushButton(frame_2);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setMinimumSize(QSize(100, 60));

        gridLayout_4->addWidget(pushButton_2, 5, 0, 2, 2);

        pushButton_Move = new QPushButton(frame_2);
        pushButton_Move->setObjectName(QString::fromUtf8("pushButton_Move"));
        pushButton_Move->setMinimumSize(QSize(0, 40));

        gridLayout_4->addWidget(pushButton_Move, 0, 0, 1, 2);

        pushButton_ZERO = new QPushButton(frame_2);
        pushButton_ZERO->setObjectName(QString::fromUtf8("pushButton_ZERO"));
        pushButton_ZERO->setMinimumSize(QSize(0, 40));

        gridLayout_4->addWidget(pushButton_ZERO, 2, 0, 1, 2);

        pushButton = new QPushButton(frame_2);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setMinimumSize(QSize(0, 30));

        gridLayout_4->addWidget(pushButton, 1, 0, 1, 1);

        pushButton_linear = new QPushButton(frame_2);
        pushButton_linear->setObjectName(QString::fromUtf8("pushButton_linear"));
        pushButton_linear->setMinimumSize(QSize(0, 40));

        gridLayout_4->addWidget(pushButton_linear, 3, 0, 1, 2);


        verticalLayout->addWidget(frame_2);

        frame = new QFrame(FormRemote);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_3 = new QGridLayout(frame);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_axis3 = new QLabel(frame);
        label_axis3->setObjectName(QString::fromUtf8("label_axis3"));
        label_axis3->setStyleSheet(QString::fromUtf8("background-color:white"));

        gridLayout_3->addWidget(label_axis3, 1, 1, 1, 1);

        label_axis5 = new QLabel(frame);
        label_axis5->setObjectName(QString::fromUtf8("label_axis5"));
        label_axis5->setMinimumSize(QSize(100, 28));
        label_axis5->setStyleSheet(QString::fromUtf8("background-color:white"));

        gridLayout_3->addWidget(label_axis5, 4, 1, 1, 1);

        label_axis7 = new QLabel(frame);
        label_axis7->setObjectName(QString::fromUtf8("label_axis7"));
        label_axis7->setMinimumSize(QSize(100, 28));
        label_axis7->setStyleSheet(QString::fromUtf8("background-color:white"));

        gridLayout_3->addWidget(label_axis7, 6, 1, 1, 1);

        label_axis2 = new QLabel(frame);
        label_axis2->setObjectName(QString::fromUtf8("label_axis2"));
        label_axis2->setMinimumSize(QSize(100, 0));
        label_axis2->setStyleSheet(QString::fromUtf8("background-color:white"));

        gridLayout_3->addWidget(label_axis2, 0, 3, 1, 1);

        label_axis4 = new QLabel(frame);
        label_axis4->setObjectName(QString::fromUtf8("label_axis4"));
        label_axis4->setMinimumSize(QSize(100, 28));
        label_axis4->setStyleSheet(QString::fromUtf8("background-color:white"));

        gridLayout_3->addWidget(label_axis4, 1, 3, 1, 1);

        label_axis6 = new QLabel(frame);
        label_axis6->setObjectName(QString::fromUtf8("label_axis6"));
        label_axis6->setMinimumSize(QSize(100, 0));
        label_axis6->setStyleSheet(QString::fromUtf8("background-color:white"));

        gridLayout_3->addWidget(label_axis6, 4, 3, 1, 1);

        label_3 = new QLabel(frame);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMinimumSize(QSize(120, 0));
        label_3->setMaximumSize(QSize(150, 16777215));

        gridLayout_3->addWidget(label_3, 4, 0, 1, 1);

        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(120, 0));
        label->setMaximumSize(QSize(150, 16777215));

        gridLayout_3->addWidget(label, 0, 0, 1, 1);

        label_15 = new QLabel(frame);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        gridLayout_3->addWidget(label_15, 6, 0, 1, 1);

        label_axis1 = new QLabel(frame);
        label_axis1->setObjectName(QString::fromUtf8("label_axis1"));
        label_axis1->setMinimumSize(QSize(100, 28));
        label_axis1->setStyleSheet(QString::fromUtf8("background-color:white"));

        gridLayout_3->addWidget(label_axis1, 0, 1, 1, 1);

        label_6 = new QLabel(frame);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setMinimumSize(QSize(100, 0));
        label_6->setMaximumSize(QSize(150, 16777215));

        gridLayout_3->addWidget(label_6, 4, 2, 1, 1);

        label_4 = new QLabel(frame);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setMinimumSize(QSize(120, 0));

        gridLayout_3->addWidget(label_4, 1, 0, 1, 1);

        label_2 = new QLabel(frame);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(100, 0));
        label_2->setMaximumSize(QSize(150, 16777215));

        gridLayout_3->addWidget(label_2, 0, 2, 1, 1);

        label_5 = new QLabel(frame);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setMinimumSize(QSize(100, 0));
        label_5->setMaximumSize(QSize(150, 16777215));

        gridLayout_3->addWidget(label_5, 1, 2, 1, 1);


        verticalLayout->addWidget(frame);


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
        pushButton_2->setText(QCoreApplication::translate("FormRemote", "Stop", nullptr));
        pushButton_Move->setText(QCoreApplication::translate("FormRemote", "Move", nullptr));
        pushButton_ZERO->setText(QCoreApplication::translate("FormRemote", "SET ZERO", nullptr));
        pushButton->setText(QCoreApplication::translate("FormRemote", "Depart", nullptr));
        pushButton_linear->setText(QCoreApplication::translate("FormRemote", "LINEAR", nullptr));
        label_axis3->setText(QString());
        label_axis5->setText(QString());
        label_axis7->setText(QString());
        label_axis2->setText(QString());
        label_axis4->setText(QString());
        label_axis6->setText(QString());
        label_3->setText(QCoreApplication::translate("FormRemote", "5/ry", nullptr));
        label->setText(QCoreApplication::translate("FormRemote", "1/X", nullptr));
        label_15->setText(QCoreApplication::translate("FormRemote", "reserv", nullptr));
        label_axis1->setText(QString());
        label_6->setText(QCoreApplication::translate("FormRemote", "6/rz", nullptr));
        label_4->setText(QCoreApplication::translate("FormRemote", "3/Z", nullptr));
        label_2->setText(QCoreApplication::translate("FormRemote", "2/Y", nullptr));
        label_5->setText(QCoreApplication::translate("FormRemote", "4/rx", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FormRemote: public Ui_FormRemote {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMREMOTE_H
