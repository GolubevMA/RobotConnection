/********************************************************************************
** Form generated from reading UI file 'tpointdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TPOINTDIALOG_H
#define UI_TPOINTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_TPointDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QFrame *frame_XYZ;
    QGridLayout *gridLayout_3;
    QLabel *label_4;
    QSpinBox *spinBox_Y;
    QLabel *label;
    QSpinBox *spinBox_X;
    QSpinBox *spinBox_Z;
    QLabel *label_3;
    QVBoxLayout *verticalLayout;
    QFrame *frame_angle;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_7;
    QSpinBox *spinBox_Angle;
    QFrame *frame_OAT;
    QGridLayout *gridLayout_2;
    QSpinBox *spinBox_rz;
    QLabel *label_5;
    QSpinBox *spinBox_ry;
    QSpinBox *spinBox_rx;
    QLabel *label_2;
    QLabel *label_6;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QDialog *TPointDialog)
    {
        if (TPointDialog->objectName().isEmpty())
            TPointDialog->setObjectName(QString::fromUtf8("TPointDialog"));
        TPointDialog->resize(626, 221);
        QFont font;
        font.setPointSize(12);
        TPointDialog->setFont(font);
        verticalLayout_2 = new QVBoxLayout(TPointDialog);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        frame_XYZ = new QFrame(TPointDialog);
        frame_XYZ->setObjectName(QString::fromUtf8("frame_XYZ"));
        frame_XYZ->setFrameShape(QFrame::StyledPanel);
        frame_XYZ->setFrameShadow(QFrame::Raised);
        gridLayout_3 = new QGridLayout(frame_XYZ);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_4 = new QLabel(frame_XYZ);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setMinimumSize(QSize(150, 0));

        gridLayout_3->addWidget(label_4, 2, 0, 1, 1);

        spinBox_Y = new QSpinBox(frame_XYZ);
        spinBox_Y->setObjectName(QString::fromUtf8("spinBox_Y"));
        spinBox_Y->setMinimumSize(QSize(100, 0));
        spinBox_Y->setMinimum(-360000);
        spinBox_Y->setMaximum(300060);

        gridLayout_3->addWidget(spinBox_Y, 2, 2, 1, 2);

        label = new QLabel(frame_XYZ);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(150, 0));
        label->setMaximumSize(QSize(150, 16777215));

        gridLayout_3->addWidget(label, 0, 0, 1, 1);

        spinBox_X = new QSpinBox(frame_XYZ);
        spinBox_X->setObjectName(QString::fromUtf8("spinBox_X"));
        spinBox_X->setMinimumSize(QSize(120, 0));
        spinBox_X->setMinimum(-10000000);
        spinBox_X->setMaximum(10000000);

        gridLayout_3->addWidget(spinBox_X, 0, 2, 1, 2);

        spinBox_Z = new QSpinBox(frame_XYZ);
        spinBox_Z->setObjectName(QString::fromUtf8("spinBox_Z"));
        spinBox_Z->setMinimumSize(QSize(120, 0));
        spinBox_Z->setMinimum(-3600000);
        spinBox_Z->setMaximum(360000000);

        gridLayout_3->addWidget(spinBox_Z, 3, 2, 1, 1);

        label_3 = new QLabel(frame_XYZ);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMinimumSize(QSize(150, 0));
        label_3->setMaximumSize(QSize(150, 16777215));

        gridLayout_3->addWidget(label_3, 3, 0, 1, 1);


        horizontalLayout_3->addWidget(frame_XYZ);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        frame_angle = new QFrame(TPointDialog);
        frame_angle->setObjectName(QString::fromUtf8("frame_angle"));
        frame_angle->setFrameShape(QFrame::StyledPanel);
        frame_angle->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame_angle);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_7 = new QLabel(frame_angle);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_2->addWidget(label_7);

        spinBox_Angle = new QSpinBox(frame_angle);
        spinBox_Angle->setObjectName(QString::fromUtf8("spinBox_Angle"));
        spinBox_Angle->setMinimumSize(QSize(120, 0));
        spinBox_Angle->setMinimum(-360);
        spinBox_Angle->setMaximum(360);

        horizontalLayout_2->addWidget(spinBox_Angle);


        verticalLayout->addWidget(frame_angle);

        frame_OAT = new QFrame(TPointDialog);
        frame_OAT->setObjectName(QString::fromUtf8("frame_OAT"));
        frame_OAT->setFrameShape(QFrame::StyledPanel);
        frame_OAT->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame_OAT);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        spinBox_rz = new QSpinBox(frame_OAT);
        spinBox_rz->setObjectName(QString::fromUtf8("spinBox_rz"));
        spinBox_rz->setMinimumSize(QSize(120, 0));
        spinBox_rz->setMinimum(-360);
        spinBox_rz->setMaximum(360);

        gridLayout_2->addWidget(spinBox_rz, 2, 1, 1, 1);

        label_5 = new QLabel(frame_OAT);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setMinimumSize(QSize(150, 0));
        label_5->setMaximumSize(QSize(150, 16777215));

        gridLayout_2->addWidget(label_5, 1, 0, 1, 1);

        spinBox_ry = new QSpinBox(frame_OAT);
        spinBox_ry->setObjectName(QString::fromUtf8("spinBox_ry"));
        spinBox_ry->setMinimumSize(QSize(120, 0));
        spinBox_ry->setMinimum(-360);
        spinBox_ry->setMaximum(360);

        gridLayout_2->addWidget(spinBox_ry, 1, 1, 1, 1);

        spinBox_rx = new QSpinBox(frame_OAT);
        spinBox_rx->setObjectName(QString::fromUtf8("spinBox_rx"));
        spinBox_rx->setMinimumSize(QSize(120, 0));
        spinBox_rx->setMinimum(-360);
        spinBox_rx->setMaximum(360);

        gridLayout_2->addWidget(spinBox_rx, 0, 1, 1, 1);

        label_2 = new QLabel(frame_OAT);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(150, 0));
        label_2->setMaximumSize(QSize(150, 16777215));

        gridLayout_2->addWidget(label_2, 0, 0, 1, 1);

        label_6 = new QLabel(frame_OAT);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setMinimumSize(QSize(150, 0));
        label_6->setMaximumSize(QSize(150, 16777215));

        gridLayout_2->addWidget(label_6, 2, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Preferred);

        gridLayout_2->addItem(verticalSpacer, 3, 0, 1, 1);


        verticalLayout->addWidget(frame_OAT);


        horizontalLayout_3->addLayout(verticalLayout);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton = new QPushButton(TPointDialog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setMinimumSize(QSize(100, 0));

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(TPointDialog);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setMinimumSize(QSize(100, 0));

        horizontalLayout->addWidget(pushButton_2);


        verticalLayout_2->addLayout(horizontalLayout);


        retranslateUi(TPointDialog);

        QMetaObject::connectSlotsByName(TPointDialog);
    } // setupUi

    void retranslateUi(QDialog *TPointDialog)
    {
        TPointDialog->setWindowTitle(QCoreApplication::translate("TPointDialog", "Dialog", nullptr));
        label_4->setText(QCoreApplication::translate("TPointDialog", "2/Y", nullptr));
        label->setText(QCoreApplication::translate("TPointDialog", "1/X", nullptr));
        label_3->setText(QCoreApplication::translate("TPointDialog", "3/Z", nullptr));
        label_7->setText(QCoreApplication::translate("TPointDialog", "A", nullptr));
        label_5->setText(QCoreApplication::translate("TPointDialog", "5/A", nullptr));
        label_2->setText(QCoreApplication::translate("TPointDialog", "4/O", nullptr));
        label_6->setText(QCoreApplication::translate("TPointDialog", "6/T", nullptr));
        pushButton->setText(QCoreApplication::translate("TPointDialog", "OK", nullptr));
        pushButton_2->setText(QCoreApplication::translate("TPointDialog", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TPointDialog: public Ui_TPointDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TPOINTDIALOG_H
