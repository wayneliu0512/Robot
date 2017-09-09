/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QGroupBox *groupBox_2;
    QLabel *pixmap_Box1;
    QLabel *label_Box1;
    QLCDNumber *lcdNumber_Box1;
    QGroupBox *groupBox_3;
    QLabel *label_Box2;
    QLabel *pixmap_Box2;
    QLCDNumber *lcdNumber_Box2;
    QGroupBox *groupBox_4;
    QLabel *pixmap_Box3;
    QLabel *label_Box3;
    QLCDNumber *lcdNumber_Box3;
    QGroupBox *groupBox;
    QLabel *label_RobotTarget;
    QLabel *pixmap_Robot;
    QTableWidget *tableWidget_1;
    QTableWidget *tableWidget_3;
    QTableWidget *tableWidget_2;
    QComboBox *comboBox;
    QWidget *gridLayoutWidget_3;
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox_5;
    QLabel *pixmap_Barcode;
    QLabel *label_5;
    QLabel *label_7;
    QLabel *label_SN;
    QLabel *label_MAC;
    QPushButton *Button_Start;
    QPushButton *Button_Stop;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(681, 611);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Widget->sizePolicy().hasHeightForWidth());
        Widget->setSizePolicy(sizePolicy);
        gridLayoutWidget = new QWidget(Widget);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(20, 170, 631, 111));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        groupBox_2 = new QGroupBox(gridLayoutWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        QFont font;
        font.setPointSize(15);
        groupBox_2->setFont(font);
        pixmap_Box1 = new QLabel(groupBox_2);
        pixmap_Box1->setObjectName(QStringLiteral("pixmap_Box1"));
        pixmap_Box1->setGeometry(QRect(10, 40, 51, 51));
        QFont font1;
        font1.setPointSize(15);
        font1.setStyleStrategy(QFont::PreferAntialias);
        pixmap_Box1->setFont(font1);
        pixmap_Box1->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/IMG_Grey.png")));
        pixmap_Box1->setScaledContents(true);
        label_Box1 = new QLabel(groupBox_2);
        label_Box1->setObjectName(QStringLiteral("label_Box1"));
        label_Box1->setGeometry(QRect(80, 80, 101, 20));
        QFont font2;
        font2.setPointSize(10);
        font2.setStyleStrategy(QFont::PreferAntialias);
        label_Box1->setFont(font2);
        lcdNumber_Box1 = new QLCDNumber(groupBox_2);
        lcdNumber_Box1->setObjectName(QStringLiteral("lcdNumber_Box1"));
        lcdNumber_Box1->setGeometry(QRect(90, 30, 91, 31));
        lcdNumber_Box1->setSegmentStyle(QLCDNumber::Flat);
        lcdNumber_Box1->setProperty("intValue", QVariant(0));

        gridLayout->addWidget(groupBox_2, 1, 0, 1, 1);

        groupBox_3 = new QGroupBox(gridLayoutWidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setFont(font);
        label_Box2 = new QLabel(groupBox_3);
        label_Box2->setObjectName(QStringLiteral("label_Box2"));
        label_Box2->setGeometry(QRect(80, 80, 121, 21));
        label_Box2->setFont(font2);
        pixmap_Box2 = new QLabel(groupBox_3);
        pixmap_Box2->setObjectName(QStringLiteral("pixmap_Box2"));
        pixmap_Box2->setGeometry(QRect(10, 40, 51, 51));
        pixmap_Box2->setFont(font1);
        pixmap_Box2->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/IMG_Grey.png")));
        pixmap_Box2->setScaledContents(true);
        lcdNumber_Box2 = new QLCDNumber(groupBox_3);
        lcdNumber_Box2->setObjectName(QStringLiteral("lcdNumber_Box2"));
        lcdNumber_Box2->setGeometry(QRect(90, 30, 91, 31));
        lcdNumber_Box2->setSegmentStyle(QLCDNumber::Flat);

        gridLayout->addWidget(groupBox_3, 1, 1, 1, 1);

        groupBox_4 = new QGroupBox(gridLayoutWidget);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setFont(font);
        pixmap_Box3 = new QLabel(groupBox_4);
        pixmap_Box3->setObjectName(QStringLiteral("pixmap_Box3"));
        pixmap_Box3->setGeometry(QRect(10, 40, 51, 51));
        pixmap_Box3->setFont(font1);
        pixmap_Box3->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/IMG_Grey.png")));
        pixmap_Box3->setScaledContents(true);
        label_Box3 = new QLabel(groupBox_4);
        label_Box3->setObjectName(QStringLiteral("label_Box3"));
        label_Box3->setGeometry(QRect(60, 80, 131, 20));
        label_Box3->setFont(font2);
        lcdNumber_Box3 = new QLCDNumber(groupBox_4);
        lcdNumber_Box3->setObjectName(QStringLiteral("lcdNumber_Box3"));
        lcdNumber_Box3->setGeometry(QRect(90, 30, 91, 31));
        lcdNumber_Box3->setSegmentStyle(QLCDNumber::Flat);

        gridLayout->addWidget(groupBox_4, 1, 2, 1, 1);

        groupBox = new QGroupBox(Widget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(20, 290, 641, 271));
        groupBox->setFont(font1);
        label_RobotTarget = new QLabel(groupBox);
        label_RobotTarget->setObjectName(QStringLiteral("label_RobotTarget"));
        label_RobotTarget->setGeometry(QRect(90, 40, 241, 31));
        label_RobotTarget->setFont(font1);
        pixmap_Robot = new QLabel(groupBox);
        pixmap_Robot->setObjectName(QStringLiteral("pixmap_Robot"));
        pixmap_Robot->setGeometry(QRect(10, 30, 51, 51));
        pixmap_Robot->setFont(font1);
        pixmap_Robot->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/IMG_Grey.png")));
        pixmap_Robot->setScaledContents(true);
        tableWidget_1 = new QTableWidget(groupBox);
        if (tableWidget_1->columnCount() < 3)
            tableWidget_1->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_1->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_1->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget_1->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidget_1->setObjectName(QStringLiteral("tableWidget_1"));
        tableWidget_1->setGeometry(QRect(10, 90, 201, 171));
        tableWidget_3 = new QTableWidget(groupBox);
        if (tableWidget_3->columnCount() < 3)
            tableWidget_3->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(1, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(2, __qtablewidgetitem5);
        tableWidget_3->setObjectName(QStringLiteral("tableWidget_3"));
        tableWidget_3->setGeometry(QRect(430, 90, 201, 171));
        tableWidget_2 = new QTableWidget(groupBox);
        if (tableWidget_2->columnCount() < 3)
            tableWidget_2->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(0, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(1, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(2, __qtablewidgetitem8);
        tableWidget_2->setObjectName(QStringLiteral("tableWidget_2"));
        tableWidget_2->setGeometry(QRect(220, 90, 201, 171));
        comboBox = new QComboBox(groupBox);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(91, 30, 141, 22));
        gridLayoutWidget_3 = new QWidget(Widget);
        gridLayoutWidget_3->setObjectName(QStringLiteral("gridLayoutWidget_3"));
        gridLayoutWidget_3->setGeometry(QRect(20, 20, 421, 141));
        gridLayout_3 = new QGridLayout(gridLayoutWidget_3);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        groupBox_5 = new QGroupBox(gridLayoutWidget_3);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        groupBox_5->setFont(font);
        pixmap_Barcode = new QLabel(groupBox_5);
        pixmap_Barcode->setObjectName(QStringLiteral("pixmap_Barcode"));
        pixmap_Barcode->setGeometry(QRect(10, 60, 51, 51));
        pixmap_Barcode->setFont(font1);
        pixmap_Barcode->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/IMG_Grey.png")));
        pixmap_Barcode->setScaledContents(true);
        label_5 = new QLabel(groupBox_5);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(90, 50, 51, 21));
        label_5->setMinimumSize(QSize(0, 0));
        label_5->setMaximumSize(QSize(100, 16777215));
        QFont font3;
        font3.setPointSize(12);
        font3.setStyleStrategy(QFont::PreferAntialias);
        label_5->setFont(font3);
        label_7 = new QLabel(groupBox_5);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(90, 80, 51, 21));
        label_7->setMinimumSize(QSize(0, 0));
        label_7->setFont(font3);
        label_SN = new QLabel(groupBox_5);
        label_SN->setObjectName(QStringLiteral("label_SN"));
        label_SN->setGeometry(QRect(150, 50, 161, 21));
        label_SN->setMinimumSize(QSize(0, 0));
        label_SN->setMaximumSize(QSize(200, 16777215));
        label_SN->setFont(font3);
        label_MAC = new QLabel(groupBox_5);
        label_MAC->setObjectName(QStringLiteral("label_MAC"));
        label_MAC->setGeometry(QRect(150, 80, 161, 21));
        label_MAC->setMinimumSize(QSize(0, 0));
        label_MAC->setMaximumSize(QSize(200, 16777215));
        label_MAC->setFont(font3);

        gridLayout_3->addWidget(groupBox_5, 0, 0, 1, 1);

        Button_Start = new QPushButton(Widget);
        Button_Start->setObjectName(QStringLiteral("Button_Start"));
        Button_Start->setEnabled(true);
        Button_Start->setGeometry(QRect(150, 570, 151, 28));
        Button_Start->setFont(font1);
        Button_Stop = new QPushButton(Widget);
        Button_Stop->setObjectName(QStringLiteral("Button_Stop"));
        Button_Stop->setEnabled(true);
        Button_Stop->setGeometry(QRect(380, 570, 151, 28));
        Button_Stop->setFont(font1);

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Arm_Server", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("Widget", "Tooling1", Q_NULLPTR));
        pixmap_Box1->setText(QString());
        label_Box1->setText(QString());
        groupBox_3->setTitle(QApplication::translate("Widget", "Tooling2", Q_NULLPTR));
        label_Box2->setText(QString());
        pixmap_Box2->setText(QString());
        groupBox_4->setTitle(QApplication::translate("Widget", "Tooling3", Q_NULLPTR));
        pixmap_Box3->setText(QString());
        label_Box3->setText(QString());
        groupBox->setTitle(QApplication::translate("Widget", "Robot", Q_NULLPTR));
        label_RobotTarget->setText(QString());
        pixmap_Robot->setText(QString());
        QTableWidgetItem *___qtablewidgetitem = tableWidget_1->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("Widget", "Target", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_1->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("Widget", "TargetID", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_1->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("Widget", "Command", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_3->horizontalHeaderItem(0);
        ___qtablewidgetitem3->setText(QApplication::translate("Widget", "Target", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget_3->horizontalHeaderItem(1);
        ___qtablewidgetitem4->setText(QApplication::translate("Widget", "TargetID", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget_3->horizontalHeaderItem(2);
        ___qtablewidgetitem5->setText(QApplication::translate("Widget", "Command", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget_2->horizontalHeaderItem(0);
        ___qtablewidgetitem6->setText(QApplication::translate("Widget", "Target", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget_2->horizontalHeaderItem(1);
        ___qtablewidgetitem7->setText(QApplication::translate("Widget", "TargetID", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget_2->horizontalHeaderItem(2);
        ___qtablewidgetitem8->setText(QApplication::translate("Widget", "Command", Q_NULLPTR));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("Widget", "toScanSN", Q_NULLPTR)
         << QApplication::translate("Widget", "toScanMAC", Q_NULLPTR)
         << QApplication::translate("Widget", "toTooling", Q_NULLPTR)
         << QApplication::translate("Widget", "toPASS", Q_NULLPTR)
         << QApplication::translate("Widget", "toFAIL", Q_NULLPTR)
        );
        groupBox_5->setTitle(QApplication::translate("Widget", "BarcodeScanner", Q_NULLPTR));
        pixmap_Barcode->setText(QString());
        label_5->setText(QApplication::translate("Widget", "SN:", Q_NULLPTR));
        label_7->setText(QApplication::translate("Widget", "MAC:", Q_NULLPTR));
        label_SN->setText(QString());
        label_MAC->setText(QString());
        Button_Start->setText(QApplication::translate("Widget", "Start Robot", Q_NULLPTR));
        Button_Stop->setText(QApplication::translate("Widget", "Stop", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
