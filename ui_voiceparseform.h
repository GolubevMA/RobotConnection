/********************************************************************************
** Form generated from reading UI file 'voiceparseform.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VOICEPARSEFORM_H
#define UI_VOICEPARSEFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VoiceParseForm
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_Recognize;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer_4;
    QLabel *label_Status;
    QPlainTextEdit *plainTextEdit_Message;
    QSpacerItem *verticalSpacer_2;
    QLabel *label_ResponseInfo;

    void setupUi(QWidget *VoiceParseForm)
    {
        if (VoiceParseForm->objectName().isEmpty())
            VoiceParseForm->setObjectName(QString::fromUtf8("VoiceParseForm"));
        VoiceParseForm->resize(352, 412);
        QFont font;
        font.setPointSize(12);
        VoiceParseForm->setFont(font);
        verticalLayout = new QVBoxLayout(VoiceParseForm);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        pushButton_Recognize = new QPushButton(VoiceParseForm);
        pushButton_Recognize->setObjectName(QString::fromUtf8("pushButton_Recognize"));
        pushButton_Recognize->setMinimumSize(QSize(120, 120));
        pushButton_Recognize->setMaximumSize(QSize(120, 120));
        pushButton_Recognize->setFont(font);
        pushButton_Recognize->setStyleSheet(QString::fromUtf8("background-color: white;\n"
"     color: balck; 	\n"
"     border-width: 1px;\n"
"     border-radius: 50px;"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/img/micro_off.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_Recognize->setIcon(icon);
        pushButton_Recognize->setIconSize(QSize(50, 50));

        horizontalLayout->addWidget(pushButton_Recognize);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);

        label_Status = new QLabel(VoiceParseForm);
        label_Status->setObjectName(QString::fromUtf8("label_Status"));

        verticalLayout->addWidget(label_Status);

        plainTextEdit_Message = new QPlainTextEdit(VoiceParseForm);
        plainTextEdit_Message->setObjectName(QString::fromUtf8("plainTextEdit_Message"));

        verticalLayout->addWidget(plainTextEdit_Message);

        verticalSpacer_2 = new QSpacerItem(20, 37, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        label_ResponseInfo = new QLabel(VoiceParseForm);
        label_ResponseInfo->setObjectName(QString::fromUtf8("label_ResponseInfo"));

        verticalLayout->addWidget(label_ResponseInfo);


        retranslateUi(VoiceParseForm);

        QMetaObject::connectSlotsByName(VoiceParseForm);
    } // setupUi

    void retranslateUi(QWidget *VoiceParseForm)
    {
        VoiceParseForm->setWindowTitle(QCoreApplication::translate("VoiceParseForm", "Form", nullptr));
        pushButton_Recognize->setText(QString());
        label_Status->setText(QCoreApplication::translate("VoiceParseForm", "TextLabel", nullptr));
        label_ResponseInfo->setText(QCoreApplication::translate("VoiceParseForm", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VoiceParseForm: public Ui_VoiceParseForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VOICEPARSEFORM_H
