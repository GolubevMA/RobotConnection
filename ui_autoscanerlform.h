/********************************************************************************
** Form generated from reading UI file 'autoscanerlform.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUTOSCANERLFORM_H
#define UI_AUTOSCANERLFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AutoScanerlForm
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer;
    QGridLayout *gridLayout_2;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QDoubleSpinBox *spinBoxStartX;
    QDoubleSpinBox *spinBoxStartY;
    QDoubleSpinBox *spinBoxStartZ;
    QLabel *label_2;
    QSpacerItem *verticalSpacer_3;
    QGridLayout *gridLayout;
    QLabel *label_5;
    QDoubleSpinBox *spinBoxEndX;
    QLabel *label_4;
    QDoubleSpinBox *spinBoxEndZ;
    QLabel *label_6;
    QDoubleSpinBox *spinBoxEndY;
    QLabel *label_3;
    QSpacerItem *verticalSpacer_4;
    QGridLayout *gridLayout_3;
    QDoubleSpinBox *spinBoxSpeed;
    QDoubleSpinBox *spinBoxRad;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_10;
    QDoubleSpinBox *spinBoxAngle;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *verticalSpacer_5;
    QLabel *label_ScanInfo;
    QSpacerItem *verticalSpacer_6;
    QPushButton *pushButton;
    QPushButton *pushButton_Check;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pushButton_2;

    void setupUi(QWidget *AutoScanerlForm)
    {
        if (AutoScanerlForm->objectName().isEmpty())
            AutoScanerlForm->setObjectName(QString::fromUtf8("AutoScanerlForm"));
        AutoScanerlForm->resize(507, 668);
        QFont font;
        font.setPointSize(12);
        AutoScanerlForm->setFont(font);
        verticalLayout = new QVBoxLayout(AutoScanerlForm);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        label = new QLabel(AutoScanerlForm);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font1;
        font1.setPointSize(14);
        label->setFont(font1);

        horizontalLayout_2->addWidget(label);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout_2);

        verticalSpacer = new QSpacerItem(20, 50, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_7 = new QLabel(AutoScanerlForm);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setMinimumSize(QSize(80, 0));
        label_7->setMaximumSize(QSize(80, 16777215));

        gridLayout_2->addWidget(label_7, 1, 0, 1, 1);

        label_8 = new QLabel(AutoScanerlForm);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setMinimumSize(QSize(80, 0));
        label_8->setMaximumSize(QSize(80, 16777215));

        gridLayout_2->addWidget(label_8, 2, 0, 1, 1);

        label_9 = new QLabel(AutoScanerlForm);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setMinimumSize(QSize(80, 0));
        label_9->setMaximumSize(QSize(80, 16777215));

        gridLayout_2->addWidget(label_9, 3, 0, 1, 1);

        spinBoxStartX = new QDoubleSpinBox(AutoScanerlForm);
        spinBoxStartX->setObjectName(QString::fromUtf8("spinBoxStartX"));
        spinBoxStartX->setMinimumSize(QSize(120, 28));
        spinBoxStartX->setMaximumSize(QSize(120, 28));
        spinBoxStartX->setDecimals(1);
        spinBoxStartX->setMinimum(-10000.000000000000000);
        spinBoxStartX->setMaximum(100000.000000000000000);

        gridLayout_2->addWidget(spinBoxStartX, 1, 1, 1, 1);

        spinBoxStartY = new QDoubleSpinBox(AutoScanerlForm);
        spinBoxStartY->setObjectName(QString::fromUtf8("spinBoxStartY"));
        spinBoxStartY->setMinimumSize(QSize(120, 28));
        spinBoxStartY->setMaximumSize(QSize(120, 28));
        spinBoxStartY->setDecimals(1);
        spinBoxStartY->setMinimum(-10000.000000000000000);
        spinBoxStartY->setMaximum(100000.000000000000000);
        spinBoxStartY->setValue(480.000000000000000);

        gridLayout_2->addWidget(spinBoxStartY, 2, 1, 1, 1);

        spinBoxStartZ = new QDoubleSpinBox(AutoScanerlForm);
        spinBoxStartZ->setObjectName(QString::fromUtf8("spinBoxStartZ"));
        spinBoxStartZ->setMinimumSize(QSize(120, 28));
        spinBoxStartZ->setMaximumSize(QSize(120, 28));
        spinBoxStartZ->setDecimals(1);
        spinBoxStartZ->setMinimum(-10000.000000000000000);
        spinBoxStartZ->setMaximum(100000.000000000000000);
        spinBoxStartZ->setValue(-340.000000000000000);

        gridLayout_2->addWidget(spinBoxStartZ, 3, 1, 1, 1);

        label_2 = new QLabel(AutoScanerlForm);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font1);

        gridLayout_2->addWidget(label_2, 0, 0, 1, 2);


        verticalLayout->addLayout(gridLayout_2);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_3);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_5 = new QLabel(AutoScanerlForm);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setMinimumSize(QSize(80, 0));
        label_5->setMaximumSize(QSize(80, 16777215));

        gridLayout->addWidget(label_5, 3, 0, 1, 1);

        spinBoxEndX = new QDoubleSpinBox(AutoScanerlForm);
        spinBoxEndX->setObjectName(QString::fromUtf8("spinBoxEndX"));
        spinBoxEndX->setMinimumSize(QSize(120, 28));
        spinBoxEndX->setMaximumSize(QSize(120, 28));
        spinBoxEndX->setDecimals(1);
        spinBoxEndX->setMinimum(-10000.000000000000000);
        spinBoxEndX->setMaximum(100000.000000000000000);

        gridLayout->addWidget(spinBoxEndX, 2, 1, 1, 1);

        label_4 = new QLabel(AutoScanerlForm);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setMinimumSize(QSize(80, 0));
        label_4->setMaximumSize(QSize(80, 16777215));

        gridLayout->addWidget(label_4, 2, 0, 1, 1);

        spinBoxEndZ = new QDoubleSpinBox(AutoScanerlForm);
        spinBoxEndZ->setObjectName(QString::fromUtf8("spinBoxEndZ"));
        spinBoxEndZ->setMinimumSize(QSize(120, 28));
        spinBoxEndZ->setMaximumSize(QSize(120, 28));
        spinBoxEndZ->setDecimals(1);
        spinBoxEndZ->setMinimum(-10000.000000000000000);
        spinBoxEndZ->setMaximum(100000.000000000000000);
        spinBoxEndZ->setValue(-340.000000000000000);

        gridLayout->addWidget(spinBoxEndZ, 4, 1, 1, 1);

        label_6 = new QLabel(AutoScanerlForm);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setMinimumSize(QSize(80, 0));
        label_6->setMaximumSize(QSize(80, 16777215));

        gridLayout->addWidget(label_6, 4, 0, 1, 1);

        spinBoxEndY = new QDoubleSpinBox(AutoScanerlForm);
        spinBoxEndY->setObjectName(QString::fromUtf8("spinBoxEndY"));
        spinBoxEndY->setMinimumSize(QSize(120, 28));
        spinBoxEndY->setMaximumSize(QSize(120, 28));
        spinBoxEndY->setDecimals(1);
        spinBoxEndY->setMinimum(-10000.000000000000000);
        spinBoxEndY->setMaximum(100000.000000000000000);
        spinBoxEndY->setValue(400.000000000000000);

        gridLayout->addWidget(spinBoxEndY, 3, 1, 1, 1);

        label_3 = new QLabel(AutoScanerlForm);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font1);

        gridLayout->addWidget(label_3, 1, 0, 1, 2);


        verticalLayout->addLayout(gridLayout);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_4);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        spinBoxSpeed = new QDoubleSpinBox(AutoScanerlForm);
        spinBoxSpeed->setObjectName(QString::fromUtf8("spinBoxSpeed"));
        spinBoxSpeed->setMinimumSize(QSize(120, 28));
        spinBoxSpeed->setMaximumSize(QSize(120, 28));
        spinBoxSpeed->setDecimals(1);
        spinBoxSpeed->setMinimum(-10000.000000000000000);
        spinBoxSpeed->setMaximum(100000.000000000000000);

        gridLayout_3->addWidget(spinBoxSpeed, 3, 3, 1, 1);

        spinBoxRad = new QDoubleSpinBox(AutoScanerlForm);
        spinBoxRad->setObjectName(QString::fromUtf8("spinBoxRad"));
        spinBoxRad->setMinimumSize(QSize(120, 28));
        spinBoxRad->setMaximumSize(QSize(120, 28));
        spinBoxRad->setDecimals(1);
        spinBoxRad->setMinimum(-10000.000000000000000);
        spinBoxRad->setMaximum(100000.000000000000000);

        gridLayout_3->addWidget(spinBoxRad, 0, 3, 1, 1);

        label_11 = new QLabel(AutoScanerlForm);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout_3->addWidget(label_11, 2, 0, 1, 2);

        label_12 = new QLabel(AutoScanerlForm);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout_3->addWidget(label_12, 3, 0, 1, 2);

        label_10 = new QLabel(AutoScanerlForm);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout_3->addWidget(label_10, 0, 0, 1, 2);

        spinBoxAngle = new QDoubleSpinBox(AutoScanerlForm);
        spinBoxAngle->setObjectName(QString::fromUtf8("spinBoxAngle"));
        spinBoxAngle->setMinimumSize(QSize(120, 28));
        spinBoxAngle->setMaximumSize(QSize(120, 28));
        spinBoxAngle->setDecimals(1);
        spinBoxAngle->setMinimum(-10000.000000000000000);
        spinBoxAngle->setMaximum(100000.000000000000000);

        gridLayout_3->addWidget(spinBoxAngle, 2, 3, 1, 1);


        verticalLayout->addLayout(gridLayout_3);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_5);

        label_ScanInfo = new QLabel(AutoScanerlForm);
        label_ScanInfo->setObjectName(QString::fromUtf8("label_ScanInfo"));

        verticalLayout->addWidget(label_ScanInfo);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_6);

        pushButton = new QPushButton(AutoScanerlForm);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout->addWidget(pushButton);

        pushButton_Check = new QPushButton(AutoScanerlForm);
        pushButton_Check->setObjectName(QString::fromUtf8("pushButton_Check"));

        verticalLayout->addWidget(pushButton_Check);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        pushButton_2 = new QPushButton(AutoScanerlForm);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        horizontalLayout_4->addWidget(pushButton_2);


        verticalLayout->addLayout(horizontalLayout_4);


        retranslateUi(AutoScanerlForm);

        QMetaObject::connectSlotsByName(AutoScanerlForm);
    } // setupUi

    void retranslateUi(QWidget *AutoScanerlForm)
    {
        AutoScanerlForm->setWindowTitle(QCoreApplication::translate("AutoScanerlForm", "Form", nullptr));
        label->setText(QCoreApplication::translate("AutoScanerlForm", "\320\241\320\272\320\260\320\275 \320\264\321\203\320\263\320\270", nullptr));
        label_7->setText(QCoreApplication::translate("AutoScanerlForm", "X", nullptr));
        label_8->setText(QCoreApplication::translate("AutoScanerlForm", "Y", nullptr));
        label_9->setText(QCoreApplication::translate("AutoScanerlForm", "Z", nullptr));
        label_2->setText(QCoreApplication::translate("AutoScanerlForm", "\320\235\320\260\321\207\320\260\320\273\320\276 \321\201\320\272\320\260\320\275\320\270\321\200\320\262\320\276\320\260\320\275\320\270\321\217", nullptr));
        label_5->setText(QCoreApplication::translate("AutoScanerlForm", "Y", nullptr));
        label_4->setText(QCoreApplication::translate("AutoScanerlForm", "X", nullptr));
        label_6->setText(QCoreApplication::translate("AutoScanerlForm", "Z", nullptr));
        label_3->setText(QCoreApplication::translate("AutoScanerlForm", "\320\222\320\265\320\272\321\202\320\276\321\200 \321\201\320\272\320\260\320\275\320\270\321\200\320\262\320\276\320\260\320\275\320\270\321\217", nullptr));
        label_11->setText(QCoreApplication::translate("AutoScanerlForm", "\320\243\320\263\320\276\320\273 \320\262\320\262\320\276\320\264\320\260", nullptr));
        label_12->setText(QCoreApplication::translate("AutoScanerlForm", "\320\241\320\272\320\276\321\200\320\276\321\201\321\202\321\214", nullptr));
        label_10->setText(QCoreApplication::translate("AutoScanerlForm", "\320\240\320\260\320\264\320\270\321\203\321\201 \320\272\321\200\320\270\320\262\321\200\320\270\320\267\320\275\321\213", nullptr));
        label_ScanInfo->setText(QString());
        pushButton->setText(QCoreApplication::translate("AutoScanerlForm", "\320\241\321\202\320\260\321\200\321\202", nullptr));
        pushButton_Check->setText(QCoreApplication::translate("AutoScanerlForm", "\320\237\321\200\320\276\320\262\320\265\321\200\320\272\320\260", nullptr));
        pushButton_2->setText(QCoreApplication::translate("AutoScanerlForm", "\320\241\321\202\320\276\320\277", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AutoScanerlForm: public Ui_AutoScanerlForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTOSCANERLFORM_H
