/********************************************************************************
** Form generated from reading UI file 'tpointdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TPOINTDIALOG_H
#define UI_TPOINTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
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
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *label_6;
    QSpinBox *spinBox_rz;
    QSpinBox *spinBox_ry;
    QLabel *label_15;
    QLabel *label_3;
    QSpinBox *spinBox_reserv;
    QLabel *label_4;
    QSpinBox *spinBox_Z;
    QLabel *label_5;
    QSpinBox *spinBox_rx;
    QLabel *label;
    QSpinBox *spinBox_X;
    QLabel *label_2;
    QSpinBox *spinBox_Y;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QDialog *TPointDialog)
    {
        if (TPointDialog->objectName().isEmpty())
            TPointDialog->setObjectName(QStringLiteral("TPointDialog"));
        TPointDialog->resize(578, 173);
        QFont font;
        font.setPointSize(12);
        TPointDialog->setFont(font);
        verticalLayout = new QVBoxLayout(TPointDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_6 = new QLabel(TPointDialog);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setMinimumSize(QSize(150, 0));
        label_6->setMaximumSize(QSize(150, 16777215));

        gridLayout->addWidget(label_6, 2, 2, 1, 2);

        spinBox_rz = new QSpinBox(TPointDialog);
        spinBox_rz->setObjectName(QStringLiteral("spinBox_rz"));
        spinBox_rz->setMinimumSize(QSize(120, 0));
        spinBox_rz->setMinimum(-360);
        spinBox_rz->setMaximum(360);

        gridLayout->addWidget(spinBox_rz, 2, 4, 1, 1);

        spinBox_ry = new QSpinBox(TPointDialog);
        spinBox_ry->setObjectName(QStringLiteral("spinBox_ry"));
        spinBox_ry->setMinimumSize(QSize(120, 0));
        spinBox_ry->setMinimum(-360);
        spinBox_ry->setMaximum(360);

        gridLayout->addWidget(spinBox_ry, 2, 1, 1, 1);

        label_15 = new QLabel(TPointDialog);
        label_15->setObjectName(QStringLiteral("label_15"));

        gridLayout->addWidget(label_15, 3, 0, 1, 1);

        label_3 = new QLabel(TPointDialog);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setMinimumSize(QSize(150, 0));
        label_3->setMaximumSize(QSize(150, 16777215));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        spinBox_reserv = new QSpinBox(TPointDialog);
        spinBox_reserv->setObjectName(QStringLiteral("spinBox_reserv"));

        gridLayout->addWidget(spinBox_reserv, 3, 1, 1, 1);

        label_4 = new QLabel(TPointDialog);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setMinimumSize(QSize(150, 0));

        gridLayout->addWidget(label_4, 1, 0, 1, 1);

        spinBox_Z = new QSpinBox(TPointDialog);
        spinBox_Z->setObjectName(QStringLiteral("spinBox_Z"));
        spinBox_Z->setMinimumSize(QSize(120, 0));
        spinBox_Z->setMinimum(-360);
        spinBox_Z->setMaximum(360);

        gridLayout->addWidget(spinBox_Z, 1, 1, 1, 1);

        label_5 = new QLabel(TPointDialog);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setMinimumSize(QSize(150, 0));
        label_5->setMaximumSize(QSize(150, 16777215));

        gridLayout->addWidget(label_5, 1, 2, 1, 2);

        spinBox_rx = new QSpinBox(TPointDialog);
        spinBox_rx->setObjectName(QStringLiteral("spinBox_rx"));
        spinBox_rx->setMinimumSize(QSize(120, 0));
        spinBox_rx->setMinimum(-360);
        spinBox_rx->setMaximum(360);

        gridLayout->addWidget(spinBox_rx, 1, 4, 1, 1);

        label = new QLabel(TPointDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(150, 0));
        label->setMaximumSize(QSize(150, 16777215));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        spinBox_X = new QSpinBox(TPointDialog);
        spinBox_X->setObjectName(QStringLiteral("spinBox_X"));
        spinBox_X->setMinimumSize(QSize(120, 0));
        spinBox_X->setMinimum(-1000);
        spinBox_X->setMaximum(1000);

        gridLayout->addWidget(spinBox_X, 0, 1, 1, 1);

        label_2 = new QLabel(TPointDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMinimumSize(QSize(150, 0));
        label_2->setMaximumSize(QSize(150, 16777215));

        gridLayout->addWidget(label_2, 0, 2, 1, 2);

        spinBox_Y = new QSpinBox(TPointDialog);
        spinBox_Y->setObjectName(QStringLiteral("spinBox_Y"));
        spinBox_Y->setMinimumSize(QSize(100, 0));
        spinBox_Y->setMinimum(-360);
        spinBox_Y->setMaximum(360);

        gridLayout->addWidget(spinBox_Y, 0, 4, 1, 1);


        verticalLayout->addLayout(gridLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton = new QPushButton(TPointDialog);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setMinimumSize(QSize(100, 0));

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(TPointDialog);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setMinimumSize(QSize(100, 0));

        horizontalLayout->addWidget(pushButton_2);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(TPointDialog);

        QMetaObject::connectSlotsByName(TPointDialog);
    } // setupUi

    void retranslateUi(QDialog *TPointDialog)
    {
        TPointDialog->setWindowTitle(QApplication::translate("TPointDialog", "Dialog", nullptr));
        label_6->setText(QApplication::translate("TPointDialog", "6/rz", nullptr));
        label_15->setText(QApplication::translate("TPointDialog", "reserv", nullptr));
        label_3->setText(QApplication::translate("TPointDialog", "5/ry", nullptr));
        label_4->setText(QApplication::translate("TPointDialog", "3/Z", nullptr));
        label_5->setText(QApplication::translate("TPointDialog", "4/rx", nullptr));
        label->setText(QApplication::translate("TPointDialog", "1/X", nullptr));
        label_2->setText(QApplication::translate("TPointDialog", "2/Y", nullptr));
        pushButton->setText(QApplication::translate("TPointDialog", "OK", nullptr));
        pushButton_2->setText(QApplication::translate("TPointDialog", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TPointDialog: public Ui_TPointDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TPOINTDIALOG_H
