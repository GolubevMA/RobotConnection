/********************************************************************************
** Form generated from reading UI file 'tmainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TMAINWINDOW_H
#define UI_TMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TMainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout;
    QLabel *label_6;
    QLabel *label_5;
    QLabel *label_3;
    QLabel *label_4;
    QSpinBox *spinBox_3;
    QLabel *label_2;
    QSpinBox *spinBox_5;
    QSpinBox *spinBox_JT1;
    QSpinBox *spinBox_2;
    QLabel *label;
    QSpinBox *spinBox;
    QSpinBox *spinBox_4;
    QGridLayout *gridLayout_2;
    QPushButton *pushButton_x_plus;
    QLabel *label_7;
    QPushButton *pushButton_x_minus;
    QPushButton *pushButton_y_plus;
    QLabel *label_8;
    QPushButton *pushButton_y_minus;
    QPushButton *pushButton_z_plus;
    QLabel *label_9;
    QPushButton *pushButton_z_minus;
    QPushButton *pushButton_rx_plus;
    QLabel *label_10;
    QPushButton *pushButton_rx_minus;
    QPushButton *pushButton_ry_plus;
    QLabel *label_11;
    QPushButton *pushButton_ry_minus;
    QPushButton *pushButton_rz_plus;
    QLabel *label_12;
    QPushButton *pushButton_rz_minus;
    QLabel *label_Pos;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *TMainWindow)
    {
        if (TMainWindow->objectName().isEmpty())
            TMainWindow->setObjectName(QStringLiteral("TMainWindow"));
        TMainWindow->resize(689, 541);
        QFont font;
        font.setPointSize(12);
        TMainWindow->setFont(font);
        centralWidget = new QWidget(TMainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout->addWidget(label_6, 0, 0, 1, 1);

        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 1, 0, 1, 1);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 3, 0, 1, 1);

        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 2, 0, 1, 1);

        spinBox_3 = new QSpinBox(centralWidget);
        spinBox_3->setObjectName(QStringLiteral("spinBox_3"));
        spinBox_3->setMinimumSize(QSize(100, 0));
        spinBox_3->setMaximum(360);

        gridLayout->addWidget(spinBox_3, 3, 1, 1, 1);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 4, 0, 1, 1);

        spinBox_5 = new QSpinBox(centralWidget);
        spinBox_5->setObjectName(QStringLiteral("spinBox_5"));
        spinBox_5->setMinimumSize(QSize(100, 0));
        spinBox_5->setMaximum(360);

        gridLayout->addWidget(spinBox_5, 6, 1, 1, 1);

        spinBox_JT1 = new QSpinBox(centralWidget);
        spinBox_JT1->setObjectName(QStringLiteral("spinBox_JT1"));
        spinBox_JT1->setMinimumSize(QSize(100, 0));
        spinBox_JT1->setMinimum(-180);
        spinBox_JT1->setMaximum(180);

        gridLayout->addWidget(spinBox_JT1, 0, 1, 1, 1);

        spinBox_2 = new QSpinBox(centralWidget);
        spinBox_2->setObjectName(QStringLiteral("spinBox_2"));
        spinBox_2->setMinimumSize(QSize(100, 0));
        spinBox_2->setMaximum(360);

        gridLayout->addWidget(spinBox_2, 2, 1, 1, 1);

        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(100, 0));
        label->setFont(font);

        gridLayout->addWidget(label, 6, 0, 1, 1);

        spinBox = new QSpinBox(centralWidget);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setMinimumSize(QSize(100, 0));
        spinBox->setMinimum(-180);
        spinBox->setMaximum(180);

        gridLayout->addWidget(spinBox, 1, 1, 1, 1);

        spinBox_4 = new QSpinBox(centralWidget);
        spinBox_4->setObjectName(QStringLiteral("spinBox_4"));
        spinBox_4->setMinimumSize(QSize(100, 0));
        spinBox_4->setMaximum(360);

        gridLayout->addWidget(spinBox_4, 4, 1, 1, 1);


        horizontalLayout->addLayout(gridLayout);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        pushButton_x_plus = new QPushButton(centralWidget);
        pushButton_x_plus->setObjectName(QStringLiteral("pushButton_x_plus"));
        pushButton_x_plus->setMinimumSize(QSize(40, 40));
        pushButton_x_plus->setMaximumSize(QSize(40, 40));

        gridLayout_2->addWidget(pushButton_x_plus, 0, 0, 1, 1);

        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setFont(font);
        label_7->setStyleSheet(QStringLiteral("background-color:white"));
        label_7->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_7, 0, 1, 1, 1);

        pushButton_x_minus = new QPushButton(centralWidget);
        pushButton_x_minus->setObjectName(QStringLiteral("pushButton_x_minus"));
        pushButton_x_minus->setMinimumSize(QSize(40, 40));
        pushButton_x_minus->setMaximumSize(QSize(40, 40));

        gridLayout_2->addWidget(pushButton_x_minus, 0, 2, 1, 1);

        pushButton_y_plus = new QPushButton(centralWidget);
        pushButton_y_plus->setObjectName(QStringLiteral("pushButton_y_plus"));
        pushButton_y_plus->setMinimumSize(QSize(40, 40));
        pushButton_y_plus->setMaximumSize(QSize(40, 40));

        gridLayout_2->addWidget(pushButton_y_plus, 1, 0, 1, 1);

        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setFont(font);
        label_8->setStyleSheet(QStringLiteral("background-color:white"));
        label_8->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_8, 1, 1, 1, 1);

        pushButton_y_minus = new QPushButton(centralWidget);
        pushButton_y_minus->setObjectName(QStringLiteral("pushButton_y_minus"));
        pushButton_y_minus->setMinimumSize(QSize(40, 40));
        pushButton_y_minus->setMaximumSize(QSize(40, 40));

        gridLayout_2->addWidget(pushButton_y_minus, 1, 2, 1, 1);

        pushButton_z_plus = new QPushButton(centralWidget);
        pushButton_z_plus->setObjectName(QStringLiteral("pushButton_z_plus"));
        pushButton_z_plus->setMinimumSize(QSize(40, 40));
        pushButton_z_plus->setMaximumSize(QSize(40, 40));

        gridLayout_2->addWidget(pushButton_z_plus, 2, 0, 1, 1);

        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setFont(font);
        label_9->setStyleSheet(QStringLiteral("background-color:white"));
        label_9->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_9, 2, 1, 1, 1);

        pushButton_z_minus = new QPushButton(centralWidget);
        pushButton_z_minus->setObjectName(QStringLiteral("pushButton_z_minus"));
        pushButton_z_minus->setMinimumSize(QSize(40, 40));
        pushButton_z_minus->setMaximumSize(QSize(40, 40));

        gridLayout_2->addWidget(pushButton_z_minus, 2, 2, 1, 1);

        pushButton_rx_plus = new QPushButton(centralWidget);
        pushButton_rx_plus->setObjectName(QStringLiteral("pushButton_rx_plus"));
        pushButton_rx_plus->setMinimumSize(QSize(40, 40));
        pushButton_rx_plus->setMaximumSize(QSize(40, 40));

        gridLayout_2->addWidget(pushButton_rx_plus, 3, 0, 1, 1);

        label_10 = new QLabel(centralWidget);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setFont(font);
        label_10->setStyleSheet(QStringLiteral("background-color:white"));
        label_10->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_10, 3, 1, 1, 1);

        pushButton_rx_minus = new QPushButton(centralWidget);
        pushButton_rx_minus->setObjectName(QStringLiteral("pushButton_rx_minus"));
        pushButton_rx_minus->setMinimumSize(QSize(40, 40));
        pushButton_rx_minus->setMaximumSize(QSize(40, 40));

        gridLayout_2->addWidget(pushButton_rx_minus, 3, 2, 1, 1);

        pushButton_ry_plus = new QPushButton(centralWidget);
        pushButton_ry_plus->setObjectName(QStringLiteral("pushButton_ry_plus"));
        pushButton_ry_plus->setMinimumSize(QSize(40, 40));
        pushButton_ry_plus->setMaximumSize(QSize(40, 40));

        gridLayout_2->addWidget(pushButton_ry_plus, 4, 0, 1, 1);

        label_11 = new QLabel(centralWidget);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setFont(font);
        label_11->setStyleSheet(QStringLiteral("background-color:white"));
        label_11->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_11, 4, 1, 1, 1);

        pushButton_ry_minus = new QPushButton(centralWidget);
        pushButton_ry_minus->setObjectName(QStringLiteral("pushButton_ry_minus"));
        pushButton_ry_minus->setMinimumSize(QSize(40, 40));
        pushButton_ry_minus->setMaximumSize(QSize(40, 40));

        gridLayout_2->addWidget(pushButton_ry_minus, 4, 2, 1, 1);

        pushButton_rz_plus = new QPushButton(centralWidget);
        pushButton_rz_plus->setObjectName(QStringLiteral("pushButton_rz_plus"));
        pushButton_rz_plus->setMinimumSize(QSize(40, 40));
        pushButton_rz_plus->setMaximumSize(QSize(40, 40));

        gridLayout_2->addWidget(pushButton_rz_plus, 5, 0, 1, 1);

        label_12 = new QLabel(centralWidget);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setFont(font);
        label_12->setStyleSheet(QStringLiteral("background-color:white"));
        label_12->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_12, 5, 1, 1, 1);

        pushButton_rz_minus = new QPushButton(centralWidget);
        pushButton_rz_minus->setObjectName(QStringLiteral("pushButton_rz_minus"));
        pushButton_rz_minus->setMinimumSize(QSize(40, 40));
        pushButton_rz_minus->setMaximumSize(QSize(40, 40));

        gridLayout_2->addWidget(pushButton_rz_minus, 5, 2, 1, 1);


        horizontalLayout->addLayout(gridLayout_2);


        verticalLayout->addLayout(horizontalLayout);

        label_Pos = new QLabel(centralWidget);
        label_Pos->setObjectName(QStringLiteral("label_Pos"));
        label_Pos->setMinimumSize(QSize(0, 100));
        label_Pos->setMaximumSize(QSize(16777215, 100));
        label_Pos->setFont(font);
        label_Pos->setStyleSheet(QLatin1String("background-color:white\n"
""));
        label_Pos->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_Pos);

        TMainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(TMainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 689, 21));
        TMainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(TMainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        TMainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(TMainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        TMainWindow->setStatusBar(statusBar);

        retranslateUi(TMainWindow);

        QMetaObject::connectSlotsByName(TMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *TMainWindow)
    {
        TMainWindow->setWindowTitle(QApplication::translate("TMainWindow", "TMainWindow", nullptr));
        label_6->setText(QApplication::translate("TMainWindow", "JT1", nullptr));
        label_5->setText(QApplication::translate("TMainWindow", "JT2", nullptr));
        label_3->setText(QApplication::translate("TMainWindow", "JT4", nullptr));
        label_4->setText(QApplication::translate("TMainWindow", "JT3", nullptr));
        label_2->setText(QApplication::translate("TMainWindow", "JT5", nullptr));
        label->setText(QApplication::translate("TMainWindow", "JT6", nullptr));
        pushButton_x_plus->setText(QApplication::translate("TMainWindow", "+", nullptr));
        label_7->setText(QApplication::translate("TMainWindow", "1/x", nullptr));
        pushButton_x_minus->setText(QApplication::translate("TMainWindow", "-", nullptr));
        pushButton_y_plus->setText(QApplication::translate("TMainWindow", "+", nullptr));
        label_8->setText(QApplication::translate("TMainWindow", "2/y", nullptr));
        pushButton_y_minus->setText(QApplication::translate("TMainWindow", "-", nullptr));
        pushButton_z_plus->setText(QApplication::translate("TMainWindow", "+", nullptr));
        label_9->setText(QApplication::translate("TMainWindow", "3/z", nullptr));
        pushButton_z_minus->setText(QApplication::translate("TMainWindow", "-", nullptr));
        pushButton_rx_plus->setText(QApplication::translate("TMainWindow", "+", nullptr));
        label_10->setText(QApplication::translate("TMainWindow", "4/rx", nullptr));
        pushButton_rx_minus->setText(QApplication::translate("TMainWindow", "-", nullptr));
        pushButton_ry_plus->setText(QApplication::translate("TMainWindow", "+", nullptr));
        label_11->setText(QApplication::translate("TMainWindow", "5/ry", nullptr));
        pushButton_ry_minus->setText(QApplication::translate("TMainWindow", "-", nullptr));
        pushButton_rz_plus->setText(QApplication::translate("TMainWindow", "+", nullptr));
        label_12->setText(QApplication::translate("TMainWindow", "6/rz", nullptr));
        pushButton_rz_minus->setText(QApplication::translate("TMainWindow", "-", nullptr));
        label_Pos->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class TMainWindow: public Ui_TMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TMAINWINDOW_H
