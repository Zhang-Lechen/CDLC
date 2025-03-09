/********************************************************************************
** Form generated from reading UI file 'Navidisplay.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NAVIDISPLAY_H
#define UI_NAVIDISPLAY_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QLabel *label;
    QLabel *label_2;
    QPushButton *addpushButton;
    QLabel *label_7;
    QLabel *label_8;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_4;
    QLabel *label_3;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QStringLiteral("Form"));
        Form->resize(508, 231);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Form->sizePolicy().hasHeightForWidth());
        Form->setSizePolicy(sizePolicy);
        Form->setStyleSheet(QStringLiteral("background-color: rgb(255, 202, 117);"));
        label = new QLabel(Form);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 20, 72, 15));
        label_2 = new QLabel(Form);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 110, 72, 15));
        addpushButton = new QPushButton(Form);
        addpushButton->setObjectName(QStringLiteral("addpushButton"));
        addpushButton->setGeometry(QRect(370, 50, 71, 31));
        label_7 = new QLabel(Form);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(120, 60, 16, 16));
        QFont font;
        font.setFamily(QStringLiteral("Agency FB"));
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        label_7->setFont(font);
        label_8 = new QLabel(Form);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(230, 50, 21, 16));
        label_8->setFont(font);
        lineEdit = new QLineEdit(Form);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(30, 50, 71, 31));
        lineEdit->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        lineEdit_2 = new QLineEdit(Form);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(140, 50, 71, 31));
        lineEdit_2->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        lineEdit_3 = new QLineEdit(Form);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setEnabled(false);
        lineEdit_3->setGeometry(QRect(260, 50, 71, 31));
        lineEdit_3->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        lineEdit_4 = new QLineEdit(Form);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));
        lineEdit_4->setEnabled(false);
        lineEdit_4->setGeometry(QRect(30, 140, 411, 41));
        label_3 = new QLabel(Form);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(290, 100, 151, 21));
        QFont font1;
        font1.setPointSize(16);
        font1.setBold(true);
        font1.setWeight(75);
        label_3->setFont(font1);

        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QApplication::translate("Form", "Form", 0));
        label->setText(QApplication::translate("Form", "\346\216\245\345\217\243\346\265\213\350\257\225", 0));
        label_2->setText(QApplication::translate("Form", "\347\253\257\345\217\243\346\265\213\350\257\225", 0));
        addpushButton->setText(QApplication::translate("Form", "\345\207\217\346\263\225\350\256\241\347\256\227", 0));
        label_7->setText(QApplication::translate("Form", "-", 0));
        label_8->setText(QApplication::translate("Form", "=", 0));
        label_3->setText(QApplication::translate("Form", "Navidisplay", 0));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NAVIDISPLAY_H
