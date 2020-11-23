/********************************************************************************
** Form generated from reading UI file 'ViewportDisplay.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIEWPORTDISPLAY_H
#define UI_VIEWPORTDISPLAY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ViewportDisplay
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *viewport;
    QWidget *widget;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QSlider *slider;
    QHBoxLayout *horizontalLayout;
    QLabel *startTime;
    QSpacerItem *horizontalSpacer;
    QLabel *endTime;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *start;
    QPushButton *pause;
    QPushButton *stop;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QWidget *ViewportDisplay)
    {
        if (ViewportDisplay->objectName().isEmpty())
            ViewportDisplay->setObjectName(QString::fromUtf8("ViewportDisplay"));
        ViewportDisplay->resize(600, 500);
        ViewportDisplay->setMinimumSize(QSize(400, 300));
        verticalLayout_2 = new QVBoxLayout(ViewportDisplay);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        viewport = new QLabel(ViewportDisplay);
        viewport->setObjectName(QString::fromUtf8("viewport"));
        viewport->setStyleSheet(QString::fromUtf8("background-color: black;"));
        viewport->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(viewport);

        widget = new QWidget(ViewportDisplay);
        widget->setObjectName(QString::fromUtf8("widget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        verticalLayout_4 = new QVBoxLayout(widget);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        slider = new QSlider(widget);
        slider->setObjectName(QString::fromUtf8("slider"));
        slider->setOrientation(Qt::Horizontal);

        verticalLayout_3->addWidget(slider);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        startTime = new QLabel(widget);
        startTime->setObjectName(QString::fromUtf8("startTime"));

        horizontalLayout->addWidget(startTime);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        endTime = new QLabel(widget);
        endTime->setObjectName(QString::fromUtf8("endTime"));

        horizontalLayout->addWidget(endTime);


        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        start = new QPushButton(widget);
        start->setObjectName(QString::fromUtf8("start"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(start->sizePolicy().hasHeightForWidth());
        start->setSizePolicy(sizePolicy1);
        start->setMinimumSize(QSize(0, 0));
        start->setBaseSize(QSize(0, 0));
        start->setCursor(QCursor(Qt::PointingHandCursor));
        start->setIconSize(QSize(25, 25));

        horizontalLayout_3->addWidget(start);

        pause = new QPushButton(widget);
        pause->setObjectName(QString::fromUtf8("pause"));
        sizePolicy1.setHeightForWidth(pause->sizePolicy().hasHeightForWidth());
        pause->setSizePolicy(sizePolicy1);
        pause->setCursor(QCursor(Qt::PointingHandCursor));
        pause->setIconSize(QSize(25, 25));

        horizontalLayout_3->addWidget(pause);

        stop = new QPushButton(widget);
        stop->setObjectName(QString::fromUtf8("stop"));
        sizePolicy1.setHeightForWidth(stop->sizePolicy().hasHeightForWidth());
        stop->setSizePolicy(sizePolicy1);
        stop->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout_3->addWidget(stop);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);


        verticalLayout_3->addLayout(horizontalLayout_3);


        verticalLayout_4->addLayout(verticalLayout_3);


        verticalLayout->addWidget(widget);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(ViewportDisplay);

        QMetaObject::connectSlotsByName(ViewportDisplay);
    } // setupUi

    void retranslateUi(QWidget *ViewportDisplay)
    {
        ViewportDisplay->setWindowTitle(QCoreApplication::translate("ViewportDisplay", "Form", nullptr));
        viewport->setText(QString());
        startTime->setText(QCoreApplication::translate("ViewportDisplay", "00:00:00", nullptr));
        endTime->setText(QCoreApplication::translate("ViewportDisplay", "00:00:00", nullptr));
        start->setText(QString());
        pause->setText(QString());
        stop->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ViewportDisplay: public Ui_ViewportDisplay {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIEWPORTDISPLAY_H
