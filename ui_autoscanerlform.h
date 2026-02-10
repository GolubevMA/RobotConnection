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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
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
    QSpacerItem *verticalSpacer_5;
    QHBoxLayout *horizontalLayout;
    QLabel *label_12;
    QDoubleSpinBox *spinBoxSpeed;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_13;
    QSpinBox *spinBoxLines;
    QSpacerItem *verticalSpacer;
    QLabel *label_ScanInfo;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *AutoScanerlForm)
    {
        if (AutoScanerlForm->objectName().isEmpty())
            AutoScanerlForm->setObjectName(QString::fromUtf8("AutoScanerlForm"));
        AutoScanerlForm->resize(439, 330);
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

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_5);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_12 = new QLabel(AutoScanerlForm);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        horizontalLayout->addWidget(label_12);

        spinBoxSpeed = new QDoubleSpinBox(AutoScanerlForm);
        spinBoxSpeed->setObjectName(QString::fromUtf8("spinBoxSpeed"));
        spinBoxSpeed->setMinimumSize(QSize(120, 28));
        spinBoxSpeed->setMaximumSize(QSize(120, 28));
        spinBoxSpeed->setDecimals(1);
        spinBoxSpeed->setMinimum(-10000.000000000000000);
        spinBoxSpeed->setMaximum(100000.000000000000000);
        spinBoxSpeed->setValue(50.000000000000000);

        horizontalLayout->addWidget(spinBoxSpeed);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_13 = new QLabel(AutoScanerlForm);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        horizontalLayout_3->addWidget(label_13);

        spinBoxLines = new QSpinBox(AutoScanerlForm);
        spinBoxLines->setObjectName(QString::fromUtf8("spinBoxLines"));
        spinBoxLines->setMinimumSize(QSize(120, 28));
        spinBoxLines->setMaximumSize(QSize(120, 28));
        spinBoxLines->setValue(6);

        horizontalLayout_3->addWidget(spinBoxLines);


        verticalLayout->addLayout(horizontalLayout_3);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        label_ScanInfo = new QLabel(AutoScanerlForm);
        label_ScanInfo->setObjectName(QString::fromUtf8("label_ScanInfo"));

        verticalLayout->addWidget(label_ScanInfo);

        pushButton = new QPushButton(AutoScanerlForm);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(AutoScanerlForm);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        verticalLayout->addWidget(pushButton_2);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);


        retranslateUi(AutoScanerlForm);

        QMetaObject::connectSlotsByName(AutoScanerlForm);
    } // setupUi

    void retranslateUi(QWidget *AutoScanerlForm)
    {
        AutoScanerlForm->setWindowTitle(QCoreApplication::translate("AutoScanerlForm", "Form", nullptr));
        label->setText(QCoreApplication::translate("AutoScanerlForm", "\320\241\320\272\320\260\320\275  \320\264\321\203\320\263\320\270", nullptr));
        label_12->setText(QCoreApplication::translate("AutoScanerlForm", "\320\241\320\272\320\276\321\200\320\276\321\201\321\202\321\214", nullptr));
        label_13->setText(QCoreApplication::translate("AutoScanerlForm", "\320\233\320\270\320\275\320\270\320\271 \321\201\320\272\320\260\320\275\320\270\321\200\320\276\320\262\320\260\320\275\320\270\321\217", nullptr));
        label_ScanInfo->setText(QString());
        pushButton->setText(QCoreApplication::translate("AutoScanerlForm", "\320\241\321\202\320\260\321\200\321\202", nullptr));
        pushButton_2->setText(QCoreApplication::translate("AutoScanerlForm", "\320\241\321\202\320\276\320\277", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AutoScanerlForm: public Ui_AutoScanerlForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTOSCANERLFORM_H
