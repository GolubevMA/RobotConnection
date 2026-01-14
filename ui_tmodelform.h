/********************************************************************************
** Form generated from reading UI file 'tmodelform.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TMODELFORM_H
#define UI_TMODELFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_TModelForm
{
public:

    void setupUi(QDialog *TModelForm)
    {
        if (TModelForm->objectName().isEmpty())
            TModelForm->setObjectName(QString::fromUtf8("TModelForm"));
        TModelForm->resize(400, 300);

        retranslateUi(TModelForm);

        QMetaObject::connectSlotsByName(TModelForm);
    } // setupUi

    void retranslateUi(QDialog *TModelForm)
    {
        TModelForm->setWindowTitle(QCoreApplication::translate("TModelForm", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TModelForm: public Ui_TModelForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TMODELFORM_H
