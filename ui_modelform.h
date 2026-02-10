/********************************************************************************
** Form generated from reading UI file 'modelform.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MODELFORM_H
#define UI_MODELFORM_H

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

class Ui_ModelForm
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QSpacerItem *horizontalSpacer_3;
    QGridLayout *gridLayout_3;
    QDoubleSpinBox *spinBoxRad;
    QLabel *label_10;
    QLabel *label_11;
    QDoubleSpinBox *spinBoxAngle;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_12;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer_4;
    QGridLayout *gridLayout_2;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QDoubleSpinBox *spinBoxStartX;
    QDoubleSpinBox *spinBoxStartY;
    QDoubleSpinBox *spinBoxStartZ;
    QLabel *label_2;
    QGridLayout *gridLayout;
    QDoubleSpinBox *spinBoxEndY;
    QLabel *label_4;
    QLabel *label_6;
    QLabel *label_3;
    QLabel *label_5;
    QDoubleSpinBox *spinBoxEndX;
    QDoubleSpinBox *spinBoxEndZ;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButton;

    void setupUi(QWidget *ModelForm)
    {
        if (ModelForm->objectName().isEmpty())
            ModelForm->setObjectName(QString::fromUtf8("ModelForm"));
        ModelForm->resize(401, 537);
        QFont font;
        font.setPointSize(12);
        ModelForm->setFont(font);
        verticalLayout = new QVBoxLayout(ModelForm);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        label = new QLabel(ModelForm);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font1;
        font1.setPointSize(14);
        label->setFont(font1);

        horizontalLayout_2->addWidget(label);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout_2);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        spinBoxRad = new QDoubleSpinBox(ModelForm);
        spinBoxRad->setObjectName(QString::fromUtf8("spinBoxRad"));
        spinBoxRad->setMinimumSize(QSize(120, 28));
        spinBoxRad->setMaximumSize(QSize(120, 28));
        spinBoxRad->setDecimals(1);
        spinBoxRad->setMinimum(-10000.000000000000000);
        spinBoxRad->setMaximum(100000.000000000000000);

        gridLayout_3->addWidget(spinBoxRad, 0, 3, 1, 1);

        label_10 = new QLabel(ModelForm);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout_3->addWidget(label_10, 0, 0, 1, 2);

        label_11 = new QLabel(ModelForm);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout_3->addWidget(label_11, 2, 0, 1, 2);

        spinBoxAngle = new QDoubleSpinBox(ModelForm);
        spinBoxAngle->setObjectName(QString::fromUtf8("spinBoxAngle"));
        spinBoxAngle->setMinimumSize(QSize(120, 28));
        spinBoxAngle->setMaximumSize(QSize(120, 28));
        spinBoxAngle->setDecimals(1);
        spinBoxAngle->setMinimum(-10000.000000000000000);
        spinBoxAngle->setMaximum(100000.000000000000000);

        gridLayout_3->addWidget(spinBoxAngle, 2, 3, 1, 1);


        verticalLayout->addLayout(gridLayout_3);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        label_12 = new QLabel(ModelForm);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setFont(font1);

        horizontalLayout_3->addWidget(label_12);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout_3);

        verticalSpacer_4 = new QSpacerItem(20, 34, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_4);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_7 = new QLabel(ModelForm);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setMinimumSize(QSize(80, 0));
        label_7->setMaximumSize(QSize(80, 16777215));

        gridLayout_2->addWidget(label_7, 1, 0, 1, 1);

        label_8 = new QLabel(ModelForm);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setMinimumSize(QSize(80, 0));
        label_8->setMaximumSize(QSize(80, 16777215));

        gridLayout_2->addWidget(label_8, 2, 0, 1, 1);

        label_9 = new QLabel(ModelForm);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setMinimumSize(QSize(80, 0));
        label_9->setMaximumSize(QSize(80, 16777215));

        gridLayout_2->addWidget(label_9, 3, 0, 1, 1);

        spinBoxStartX = new QDoubleSpinBox(ModelForm);
        spinBoxStartX->setObjectName(QString::fromUtf8("spinBoxStartX"));
        spinBoxStartX->setMinimumSize(QSize(120, 28));
        spinBoxStartX->setMaximumSize(QSize(120, 28));
        spinBoxStartX->setDecimals(1);
        spinBoxStartX->setMinimum(-10000.000000000000000);
        spinBoxStartX->setMaximum(100000.000000000000000);

        gridLayout_2->addWidget(spinBoxStartX, 1, 1, 1, 1);

        spinBoxStartY = new QDoubleSpinBox(ModelForm);
        spinBoxStartY->setObjectName(QString::fromUtf8("spinBoxStartY"));
        spinBoxStartY->setMinimumSize(QSize(120, 28));
        spinBoxStartY->setMaximumSize(QSize(120, 28));
        spinBoxStartY->setDecimals(1);
        spinBoxStartY->setMinimum(-10000.000000000000000);
        spinBoxStartY->setMaximum(100000.000000000000000);
        spinBoxStartY->setValue(480.000000000000000);

        gridLayout_2->addWidget(spinBoxStartY, 2, 1, 1, 1);

        spinBoxStartZ = new QDoubleSpinBox(ModelForm);
        spinBoxStartZ->setObjectName(QString::fromUtf8("spinBoxStartZ"));
        spinBoxStartZ->setMinimumSize(QSize(120, 28));
        spinBoxStartZ->setMaximumSize(QSize(120, 28));
        spinBoxStartZ->setDecimals(1);
        spinBoxStartZ->setMinimum(-10000.000000000000000);
        spinBoxStartZ->setMaximum(100000.000000000000000);
        spinBoxStartZ->setValue(-340.000000000000000);

        gridLayout_2->addWidget(spinBoxStartZ, 3, 1, 1, 1);

        label_2 = new QLabel(ModelForm);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font1);

        gridLayout_2->addWidget(label_2, 0, 0, 1, 2);


        verticalLayout->addLayout(gridLayout_2);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        spinBoxEndY = new QDoubleSpinBox(ModelForm);
        spinBoxEndY->setObjectName(QString::fromUtf8("spinBoxEndY"));
        spinBoxEndY->setMinimumSize(QSize(120, 28));
        spinBoxEndY->setMaximumSize(QSize(120, 28));
        spinBoxEndY->setDecimals(1);
        spinBoxEndY->setMinimum(-10000.000000000000000);
        spinBoxEndY->setMaximum(100000.000000000000000);
        spinBoxEndY->setValue(400.000000000000000);

        gridLayout->addWidget(spinBoxEndY, 4, 1, 1, 1);

        label_4 = new QLabel(ModelForm);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setMinimumSize(QSize(80, 0));
        label_4->setMaximumSize(QSize(80, 16777215));

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        label_6 = new QLabel(ModelForm);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setMinimumSize(QSize(80, 0));
        label_6->setMaximumSize(QSize(80, 16777215));

        gridLayout->addWidget(label_6, 5, 0, 1, 1);

        label_3 = new QLabel(ModelForm);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font1);

        gridLayout->addWidget(label_3, 1, 0, 1, 2);

        label_5 = new QLabel(ModelForm);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setMinimumSize(QSize(80, 0));
        label_5->setMaximumSize(QSize(80, 16777215));

        gridLayout->addWidget(label_5, 4, 0, 1, 1);

        spinBoxEndX = new QDoubleSpinBox(ModelForm);
        spinBoxEndX->setObjectName(QString::fromUtf8("spinBoxEndX"));
        spinBoxEndX->setMinimumSize(QSize(120, 28));
        spinBoxEndX->setMaximumSize(QSize(120, 28));
        spinBoxEndX->setDecimals(1);
        spinBoxEndX->setMinimum(-10000.000000000000000);
        spinBoxEndX->setMaximum(100000.000000000000000);

        gridLayout->addWidget(spinBoxEndX, 3, 1, 1, 1);

        spinBoxEndZ = new QDoubleSpinBox(ModelForm);
        spinBoxEndZ->setObjectName(QString::fromUtf8("spinBoxEndZ"));
        spinBoxEndZ->setMinimumSize(QSize(120, 28));
        spinBoxEndZ->setMaximumSize(QSize(120, 28));
        spinBoxEndZ->setDecimals(1);
        spinBoxEndZ->setMinimum(-10000.000000000000000);
        spinBoxEndZ->setMaximum(100000.000000000000000);
        spinBoxEndZ->setValue(-340.000000000000000);

        gridLayout->addWidget(spinBoxEndZ, 5, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        pushButton = new QPushButton(ModelForm);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout->addWidget(pushButton);


        retranslateUi(ModelForm);

        QMetaObject::connectSlotsByName(ModelForm);
    } // setupUi

    void retranslateUi(QWidget *ModelForm)
    {
        ModelForm->setWindowTitle(QCoreApplication::translate("ModelForm", "Form", nullptr));
        label->setText(QCoreApplication::translate("ModelForm", "\320\234\320\276\320\264\320\265\320\273\321\214", nullptr));
        label_10->setText(QCoreApplication::translate("ModelForm", "\320\240\320\260\320\264\320\270\321\203\321\201 \320\272\321\200\320\270\320\262\321\200\320\270\320\267\320\275\321\213", nullptr));
        label_11->setText(QCoreApplication::translate("ModelForm", "\320\243\320\263\320\276\320\273 \320\262\320\262\320\276\320\264\320\260", nullptr));
        label_12->setText(QCoreApplication::translate("ModelForm", "\320\240\320\260\321\201\320\277\320\276\320\273\320\276\320\266\320\265\320\275\320\270\320\265 \320\274\320\276\320\264\320\265\320\273\320\270", nullptr));
        label_7->setText(QCoreApplication::translate("ModelForm", "X", nullptr));
        label_8->setText(QCoreApplication::translate("ModelForm", "Y", nullptr));
        label_9->setText(QCoreApplication::translate("ModelForm", "Z", nullptr));
        label_2->setText(QCoreApplication::translate("ModelForm", "\320\235\320\260\321\207\320\260\320\273\320\276 \321\201\320\272\320\260\320\275\320\270\321\200\320\262\320\276\320\260\320\275\320\270\321\217", nullptr));
        label_4->setText(QCoreApplication::translate("ModelForm", "X", nullptr));
        label_6->setText(QCoreApplication::translate("ModelForm", "Z", nullptr));
        label_3->setText(QCoreApplication::translate("ModelForm", "\320\222\320\265\320\272\321\202\320\276\321\200 \321\201\320\272\320\260\320\275\320\270\321\200\320\262\320\276\320\260\320\275\320\270\321\217", nullptr));
        label_5->setText(QCoreApplication::translate("ModelForm", "Y", nullptr));
        pushButton->setText(QCoreApplication::translate("ModelForm", "\320\230\320\267\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ModelForm: public Ui_ModelForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODELFORM_H
