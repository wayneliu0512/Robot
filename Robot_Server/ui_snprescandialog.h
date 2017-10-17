/********************************************************************************
** Form generated from reading UI file 'snprescandialog.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SNPRESCANDIALOG_H
#define UI_SNPRESCANDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_SNpreScanDialog
{
public:
    QGroupBox *groupBox;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *lineEdit_Tooling_1;
    QLineEdit *lineEdit_Base_1;
    QLineEdit *lineEdit_ModuleBase_1;
    QLineEdit *lineEdit_Module_1;
    QGroupBox *groupBox_2;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLineEdit *lineEdit_Tooling_2;
    QLineEdit *lineEdit_Base_2;
    QLineEdit *lineEdit_ModuleBase_2;
    QLineEdit *lineEdit_Module_2;
    QGroupBox *groupBox_3;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QLineEdit *lineEdit_Tooling_3;
    QLineEdit *lineEdit_Base_3;
    QLineEdit *lineEdit_ModuleBase_3;
    QLineEdit *lineEdit_Module_3;

    void setupUi(QDialog *SNpreScanDialog)
    {
        if (SNpreScanDialog->objectName().isEmpty())
            SNpreScanDialog->setObjectName(QStringLiteral("SNpreScanDialog"));
        SNpreScanDialog->resize(721, 216);
        groupBox = new QGroupBox(SNpreScanDialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(20, 30, 221, 151));
        QFont font;
        font.setPointSize(12);
        groupBox->setFont(font);
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 30, 81, 16));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 60, 81, 16));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 90, 81, 16));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 120, 81, 16));
        lineEdit_Tooling_1 = new QLineEdit(groupBox);
        lineEdit_Tooling_1->setObjectName(QStringLiteral("lineEdit_Tooling_1"));
        lineEdit_Tooling_1->setGeometry(QRect(102, 30, 111, 21));
        lineEdit_Base_1 = new QLineEdit(groupBox);
        lineEdit_Base_1->setObjectName(QStringLiteral("lineEdit_Base_1"));
        lineEdit_Base_1->setGeometry(QRect(100, 60, 113, 21));
        lineEdit_ModuleBase_1 = new QLineEdit(groupBox);
        lineEdit_ModuleBase_1->setObjectName(QStringLiteral("lineEdit_ModuleBase_1"));
        lineEdit_ModuleBase_1->setGeometry(QRect(100, 90, 113, 21));
        lineEdit_Module_1 = new QLineEdit(groupBox);
        lineEdit_Module_1->setObjectName(QStringLiteral("lineEdit_Module_1"));
        lineEdit_Module_1->setGeometry(QRect(100, 120, 113, 21));
        groupBox_2 = new QGroupBox(SNpreScanDialog);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setEnabled(false);
        groupBox_2->setGeometry(QRect(250, 30, 221, 151));
        groupBox_2->setFont(font);
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(10, 30, 81, 16));
        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(10, 60, 81, 16));
        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(10, 90, 81, 16));
        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(10, 120, 81, 16));
        lineEdit_Tooling_2 = new QLineEdit(groupBox_2);
        lineEdit_Tooling_2->setObjectName(QStringLiteral("lineEdit_Tooling_2"));
        lineEdit_Tooling_2->setGeometry(QRect(100, 30, 113, 21));
        lineEdit_Base_2 = new QLineEdit(groupBox_2);
        lineEdit_Base_2->setObjectName(QStringLiteral("lineEdit_Base_2"));
        lineEdit_Base_2->setGeometry(QRect(100, 60, 113, 21));
        lineEdit_ModuleBase_2 = new QLineEdit(groupBox_2);
        lineEdit_ModuleBase_2->setObjectName(QStringLiteral("lineEdit_ModuleBase_2"));
        lineEdit_ModuleBase_2->setGeometry(QRect(100, 90, 113, 21));
        lineEdit_Module_2 = new QLineEdit(groupBox_2);
        lineEdit_Module_2->setObjectName(QStringLiteral("lineEdit_Module_2"));
        lineEdit_Module_2->setGeometry(QRect(100, 120, 113, 21));
        groupBox_3 = new QGroupBox(SNpreScanDialog);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setEnabled(false);
        groupBox_3->setGeometry(QRect(480, 30, 221, 151));
        groupBox_3->setFont(font);
        label_9 = new QLabel(groupBox_3);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(10, 30, 81, 16));
        label_10 = new QLabel(groupBox_3);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(10, 60, 81, 16));
        label_11 = new QLabel(groupBox_3);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(10, 90, 81, 16));
        label_12 = new QLabel(groupBox_3);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(10, 120, 81, 16));
        lineEdit_Tooling_3 = new QLineEdit(groupBox_3);
        lineEdit_Tooling_3->setObjectName(QStringLiteral("lineEdit_Tooling_3"));
        lineEdit_Tooling_3->setGeometry(QRect(100, 30, 113, 21));
        lineEdit_Base_3 = new QLineEdit(groupBox_3);
        lineEdit_Base_3->setObjectName(QStringLiteral("lineEdit_Base_3"));
        lineEdit_Base_3->setGeometry(QRect(100, 60, 113, 21));
        lineEdit_ModuleBase_3 = new QLineEdit(groupBox_3);
        lineEdit_ModuleBase_3->setObjectName(QStringLiteral("lineEdit_ModuleBase_3"));
        lineEdit_ModuleBase_3->setGeometry(QRect(100, 90, 113, 21));
        lineEdit_Module_3 = new QLineEdit(groupBox_3);
        lineEdit_Module_3->setObjectName(QStringLiteral("lineEdit_Module_3"));
        lineEdit_Module_3->setGeometry(QRect(100, 120, 113, 21));
        QWidget::setTabOrder(lineEdit_Tooling_1, lineEdit_Base_1);
        QWidget::setTabOrder(lineEdit_Base_1, lineEdit_ModuleBase_1);
        QWidget::setTabOrder(lineEdit_ModuleBase_1, lineEdit_Module_1);
        QWidget::setTabOrder(lineEdit_Module_1, lineEdit_Tooling_2);
        QWidget::setTabOrder(lineEdit_Tooling_2, lineEdit_Base_2);
        QWidget::setTabOrder(lineEdit_Base_2, lineEdit_ModuleBase_2);
        QWidget::setTabOrder(lineEdit_ModuleBase_2, lineEdit_Module_2);
        QWidget::setTabOrder(lineEdit_Module_2, lineEdit_Tooling_3);
        QWidget::setTabOrder(lineEdit_Tooling_3, lineEdit_Base_3);
        QWidget::setTabOrder(lineEdit_Base_3, lineEdit_ModuleBase_3);
        QWidget::setTabOrder(lineEdit_ModuleBase_3, lineEdit_Module_3);

        retranslateUi(SNpreScanDialog);

        QMetaObject::connectSlotsByName(SNpreScanDialog);
    } // setupUi

    void retranslateUi(QDialog *SNpreScanDialog)
    {
        SNpreScanDialog->setWindowTitle(QApplication::translate("SNpreScanDialog", "Pre Scan Dialog", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        SNpreScanDialog->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        groupBox->setTitle(QApplication::translate("SNpreScanDialog", "Tooling1", Q_NULLPTR));
        label->setText(QApplication::translate("SNpreScanDialog", "Tooling", Q_NULLPTR));
        label_2->setText(QApplication::translate("SNpreScanDialog", "Base", Q_NULLPTR));
        label_3->setText(QApplication::translate("SNpreScanDialog", "Module base", Q_NULLPTR));
        label_4->setText(QApplication::translate("SNpreScanDialog", "Module", Q_NULLPTR));
#ifndef QT_NO_WHATSTHIS
        lineEdit_Tooling_1->setWhatsThis(QApplication::translate("SNpreScanDialog", "<html><head/><body><p>\346\251\237\347\256\261\345\272\217\350\231\237:</p><p>FX-[\347\224\242\345\223\201\345\236\213\350\231\237]-[1~3\344\275\215\346\225\270\345\255\227,\346\265\201\346\260\264\350\231\237]</p><p>PS: \346\255\244\345\272\217\350\231\237\346\234\203\350\267\237Base_Setting.ini\350\243\241\346\257\224\345\260\215,\346\211\276\344\270\215\345\210\260\346\234\203\351\214\257\350\252\244</p><p><br/></p></body></html>", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
#ifndef QT_NO_WHATSTHIS
        lineEdit_Base_1->setWhatsThis(QApplication::translate("SNpreScanDialog", "<html><head/><body><p>\346\251\237\347\256\261\345\256\232\344\275\215\345\272\247\345\272\217\350\231\237</p><p>1~3\344\275\215\346\225\270\345\255\227</p><p>PS:\351\234\200\350\246\201\350\267\237Module base \347\233\270\345\220\214</p></body></html>", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
#ifndef QT_NO_WHATSTHIS
        lineEdit_ModuleBase_1->setWhatsThis(QApplication::translate("SNpreScanDialog", "<html><head/><body><p>\346\250\241\347\265\204\345\272\247\345\272\217\350\231\237:</p><p>1~3\344\275\215\346\225\270\345\255\227</p><p>PS:\351\234\200\350\246\201\350\267\237base \347\233\270\345\220\214</p></body></html>", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
#ifndef QT_NO_WHATSTHIS
        lineEdit_Module_1->setWhatsThis(QApplication::translate("SNpreScanDialog", "<html><head/><body><p>\346\250\241\347\265\204\345\272\217\350\231\237:</p><p>FX-[\347\224\242\345\223\201\345\236\213\350\231\237+M]-[1~3\344\275\215\346\225\270\345\255\227,\346\265\201\346\260\264\350\231\237]</p><p>PS: \346\255\244\345\272\217\350\231\237\346\234\203\347\224\250\347\224\242\345\223\201\345\236\213\350\231\237\350\267\237\346\251\237\347\256\261\347\224\242\345\223\201\345\236\213\350\231\237\344\275\234\346\257\224\345\260\215,\344\270\215\347\233\270\345\220\214\346\234\203\351\214\257\350\252\244</p><p><br/></p></body></html>", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
        groupBox_2->setTitle(QApplication::translate("SNpreScanDialog", "Tooling2", Q_NULLPTR));
        label_5->setText(QApplication::translate("SNpreScanDialog", "Tooling", Q_NULLPTR));
        label_6->setText(QApplication::translate("SNpreScanDialog", "Base", Q_NULLPTR));
        label_7->setText(QApplication::translate("SNpreScanDialog", "Module base", Q_NULLPTR));
        label_8->setText(QApplication::translate("SNpreScanDialog", "Module", Q_NULLPTR));
#ifndef QT_NO_WHATSTHIS
        lineEdit_Tooling_2->setWhatsThis(QApplication::translate("SNpreScanDialog", "<html><head/><body><p>\346\251\237\347\256\261\345\272\217\350\231\237:</p><p>FX-[\347\224\242\345\223\201\345\236\213\350\231\237]-[1~3\344\275\215\346\225\270\345\255\227,\346\265\201\346\260\264\350\231\237]</p><p>PS: \346\255\244\345\272\217\350\231\237\346\234\203\350\267\237Base_Setting.ini\350\243\241\346\257\224\345\260\215,\346\211\276\344\270\215\345\210\260\346\234\203\351\214\257\350\252\244</p><p><br/></p></body></html>", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
#ifndef QT_NO_WHATSTHIS
        lineEdit_Base_2->setWhatsThis(QApplication::translate("SNpreScanDialog", "<html><head/><body><p>\346\251\237\347\256\261\345\256\232\344\275\215\345\272\247\345\272\217\350\231\237</p><p>1~3\344\275\215\346\225\270\345\255\227</p><p>PS:\351\234\200\350\246\201\350\267\237Module base \347\233\270\345\220\214</p></body></html>", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
#ifndef QT_NO_WHATSTHIS
        lineEdit_ModuleBase_2->setWhatsThis(QApplication::translate("SNpreScanDialog", "<html><head/><body><p>\346\250\241\347\265\204\345\272\247\345\272\217\350\231\237:</p><p>1~3\344\275\215\346\225\270\345\255\227</p><p>PS:\351\234\200\350\246\201\350\267\237base \347\233\270\345\220\214</p></body></html>", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
#ifndef QT_NO_WHATSTHIS
        lineEdit_Module_2->setWhatsThis(QApplication::translate("SNpreScanDialog", "<html><head/><body><p>\346\250\241\347\265\204\345\272\217\350\231\237:</p><p>FX-[\347\224\242\345\223\201\345\236\213\350\231\237+M]-[1~3\344\275\215\346\225\270\345\255\227,\346\265\201\346\260\264\350\231\237]</p><p>PS: \346\255\244\345\272\217\350\231\237\346\234\203\347\224\250\347\224\242\345\223\201\345\236\213\350\231\237\350\267\237\346\251\237\347\256\261\347\224\242\345\223\201\345\236\213\350\231\237\344\275\234\346\257\224\345\260\215,\344\270\215\347\233\270\345\220\214\346\234\203\351\214\257\350\252\244</p><p><br/></p></body></html>", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
        groupBox_3->setTitle(QApplication::translate("SNpreScanDialog", "Tooling3", Q_NULLPTR));
        label_9->setText(QApplication::translate("SNpreScanDialog", "Tooling", Q_NULLPTR));
        label_10->setText(QApplication::translate("SNpreScanDialog", "Base", Q_NULLPTR));
        label_11->setText(QApplication::translate("SNpreScanDialog", "Module base", Q_NULLPTR));
        label_12->setText(QApplication::translate("SNpreScanDialog", "Module", Q_NULLPTR));
#ifndef QT_NO_WHATSTHIS
        lineEdit_Tooling_3->setWhatsThis(QApplication::translate("SNpreScanDialog", "<html><head/><body><p>\346\251\237\347\256\261\345\272\217\350\231\237:</p><p>FX-[\347\224\242\345\223\201\345\236\213\350\231\237]-[1~3\344\275\215\346\225\270\345\255\227,\346\265\201\346\260\264\350\231\237]</p><p>PS: \346\255\244\345\272\217\350\231\237\346\234\203\350\267\237Base_Setting.ini\350\243\241\346\257\224\345\260\215,\346\211\276\344\270\215\345\210\260\346\234\203\351\214\257\350\252\244</p><p><br/></p></body></html>", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
#ifndef QT_NO_WHATSTHIS
        lineEdit_Base_3->setWhatsThis(QApplication::translate("SNpreScanDialog", "<html><head/><body><p>\346\251\237\347\256\261\345\256\232\344\275\215\345\272\247\345\272\217\350\231\237</p><p>1~3\344\275\215\346\225\270\345\255\227</p><p>PS:\351\234\200\350\246\201\350\267\237Module base \347\233\270\345\220\214</p></body></html>", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
#ifndef QT_NO_WHATSTHIS
        lineEdit_ModuleBase_3->setWhatsThis(QApplication::translate("SNpreScanDialog", "<html><head/><body><p>\346\250\241\347\265\204\345\272\247\345\272\217\350\231\237:</p><p>1~3\344\275\215\346\225\270\345\255\227</p><p>PS:\351\234\200\350\246\201\350\267\237base \347\233\270\345\220\214</p></body></html>", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
#ifndef QT_NO_WHATSTHIS
        lineEdit_Module_3->setWhatsThis(QApplication::translate("SNpreScanDialog", "<html><head/><body><p>\346\250\241\347\265\204\345\272\217\350\231\237:</p><p>FX-[\347\224\242\345\223\201\345\236\213\350\231\237+M]-[1~3\344\275\215\346\225\270\345\255\227,\346\265\201\346\260\264\350\231\237]</p><p>PS: \346\255\244\345\272\217\350\231\237\346\234\203\347\224\250\347\224\242\345\223\201\345\236\213\350\231\237\350\267\237\346\251\237\347\256\261\347\224\242\345\223\201\345\236\213\350\231\237\344\275\234\346\257\224\345\260\215,\344\270\215\347\233\270\345\220\214\346\234\203\351\214\257\350\252\244</p><p><br/></p></body></html>", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
    } // retranslateUi

};

namespace Ui {
    class SNpreScanDialog: public Ui_SNpreScanDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SNPRESCANDIALOG_H
