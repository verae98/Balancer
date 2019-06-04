/********************************************************************************
** Form generated from reading UI file 'coordinate_popup.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COORDINATE_POPUP_H
#define UI_COORDINATE_POPUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QLabel *currently_selected;
    QGroupBox *groupBox_3;
    QLabel *camera_still;
    QLabel *current_coordinates;
    QPushButton *confirm_btn;
    QPushButton *cancel_btn;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLabel *target_system_label;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QStringLiteral("Form"));
        Form->resize(760, 619);
        currently_selected = new QLabel(Form);
        currently_selected->setObjectName(QStringLiteral("currently_selected"));
        currently_selected->setGeometry(QRect(400, 10, 191, 31));
        groupBox_3 = new QGroupBox(Form);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 40, 611, 491));
        camera_still = new QLabel(groupBox_3);
        camera_still->setObjectName(QStringLiteral("camera_still"));
        camera_still->setGeometry(QRect(0, 20, 611, 471));
        current_coordinates = new QLabel(Form);
        current_coordinates->setObjectName(QStringLiteral("current_coordinates"));
        current_coordinates->setGeometry(QRect(600, 10, 121, 31));
        confirm_btn = new QPushButton(Form);
        confirm_btn->setObjectName(QStringLiteral("confirm_btn"));
        confirm_btn->setGeometry(QRect(630, 60, 80, 25));
        cancel_btn = new QPushButton(Form);
        cancel_btn->setObjectName(QStringLiteral("cancel_btn"));
        cancel_btn->setGeometry(QRect(630, 100, 80, 25));
        layoutWidget = new QWidget(Form);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 201, 19));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        target_system_label = new QLabel(layoutWidget);
        target_system_label->setObjectName(QStringLiteral("target_system_label"));

        horizontalLayout->addWidget(target_system_label);


        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QApplication::translate("Form", "Form", nullptr));
        currently_selected->setText(QApplication::translate("Form", "Currently selected coordinates:", nullptr));
        groupBox_3->setTitle(QApplication::translate("Form", "Image:", nullptr));
        camera_still->setText(QString());
        current_coordinates->setText(QString());
        confirm_btn->setText(QApplication::translate("Form", "Confirm", nullptr));
        cancel_btn->setText(QApplication::translate("Form", "Cancel", nullptr));
        label->setText(QApplication::translate("Form", "Select the position of ", nullptr));
        target_system_label->setText(QApplication::translate("Form", "#default", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COORDINATE_POPUP_H
