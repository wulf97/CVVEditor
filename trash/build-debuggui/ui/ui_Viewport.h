/********************************************************************************
** Form generated from reading UI file 'Viewport.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIEWPORT_H
#define UI_VIEWPORT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Viewport
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *viewport;

    void setupUi(QWidget *Viewport)
    {
        if (Viewport->objectName().isEmpty())
            Viewport->setObjectName(QString::fromUtf8("Viewport"));
        Viewport->resize(550, 400);
        Viewport->setMinimumSize(QSize(500, 300));
        Viewport->setBaseSize(QSize(500, 300));
        Viewport->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_2 = new QVBoxLayout(Viewport);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        viewport = new QLabel(Viewport);
        viewport->setObjectName(QString::fromUtf8("viewport"));
        viewport->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));

        verticalLayout->addWidget(viewport);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(Viewport);

        QMetaObject::connectSlotsByName(Viewport);
    } // setupUi

    void retranslateUi(QWidget *Viewport)
    {
        Viewport->setWindowTitle(QApplication::translate("Viewport", "Form", nullptr));
        viewport->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Viewport: public Ui_Viewport {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIEWPORT_H
