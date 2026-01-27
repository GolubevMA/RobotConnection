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
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AutoScanerlForm
{
public:

    void setupUi(QWidget *AutoScanerlForm)
    {
        if (AutoScanerlForm->objectName().isEmpty())
            AutoScanerlForm->setObjectName(QString::fromUtf8("AutoScanerlForm"));
        AutoScanerlForm->resize(400, 300);

        retranslateUi(AutoScanerlForm);

        QMetaObject::connectSlotsByName(AutoScanerlForm);
    } // setupUi

    void retranslateUi(QWidget *AutoScanerlForm)
    {
        AutoScanerlForm->setWindowTitle(QCoreApplication::translate("AutoScanerlForm", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AutoScanerlForm: public Ui_AutoScanerlForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTOSCANERLFORM_H
