/********************************************************************************
** Form generated from reading UI file 'VideoSettings.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIDEOSETTINGS_H
#define UI_VIDEOSETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VideoSettings
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *videoPathLineEdit;
    QPushButton *addVideoButton;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_3;
    QSpinBox *spinBox;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *rangeSliderLayout;
    QHBoxLayout *horizontalLayout_5;
    QLabel *startTime;
    QSpacerItem *horizontalSpacer;
    QLabel *endTime;
    QHBoxLayout *horizontalLayout_4;
    QLabel *startFrame;
    QLabel *endFrame;
    QLabel *currentFrame;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *VideoSettings)
    {
        if (VideoSettings->objectName().isEmpty())
            VideoSettings->setObjectName(QString::fromUtf8("VideoSettings"));
        VideoSettings->resize(430, 720);
        VideoSettings->setMinimumSize(QSize(430, 0));
        verticalLayout_2 = new QVBoxLayout(VideoSettings);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        videoPathLineEdit = new QLineEdit(VideoSettings);
        videoPathLineEdit->setObjectName(QString::fromUtf8("videoPathLineEdit"));

        horizontalLayout_2->addWidget(videoPathLineEdit);

        addVideoButton = new QPushButton(VideoSettings);
        addVideoButton->setObjectName(QString::fromUtf8("addVideoButton"));

        horizontalLayout_2->addWidget(addVideoButton);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        groupBox = new QGroupBox(VideoSettings);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        horizontalLayout_3 = new QHBoxLayout(groupBox);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        spinBox = new QSpinBox(groupBox);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setEnabled(false);
        spinBox->setMaximum(70);

        horizontalLayout_3->addWidget(spinBox);


        horizontalLayout->addWidget(groupBox);


        verticalLayout->addLayout(horizontalLayout);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        rangeSliderLayout = new QHBoxLayout();
        rangeSliderLayout->setObjectName(QString::fromUtf8("rangeSliderLayout"));

        verticalLayout_6->addLayout(rangeSliderLayout);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        startTime = new QLabel(VideoSettings);
        startTime->setObjectName(QString::fromUtf8("startTime"));

        horizontalLayout_5->addWidget(startTime);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);

        endTime = new QLabel(VideoSettings);
        endTime->setObjectName(QString::fromUtf8("endTime"));

        horizontalLayout_5->addWidget(endTime);


        verticalLayout_6->addLayout(horizontalLayout_5);


        verticalLayout->addLayout(verticalLayout_6);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        startFrame = new QLabel(VideoSettings);
        startFrame->setObjectName(QString::fromUtf8("startFrame"));
        startFrame->setMinimumSize(QSize(200, 200));
        startFrame->setAutoFillBackground(false);
        startFrame->setStyleSheet(QString::fromUtf8("background-color: black;"));
        startFrame->setAlignment(Qt::AlignCenter);

        horizontalLayout_4->addWidget(startFrame);

        endFrame = new QLabel(VideoSettings);
        endFrame->setObjectName(QString::fromUtf8("endFrame"));
        endFrame->setMinimumSize(QSize(200, 200));
        endFrame->setStyleSheet(QString::fromUtf8("background-color: black;"));
        endFrame->setAlignment(Qt::AlignCenter);

        horizontalLayout_4->addWidget(endFrame);


        verticalLayout->addLayout(horizontalLayout_4);


        verticalLayout_2->addLayout(verticalLayout);

        currentFrame = new QLabel(VideoSettings);
        currentFrame->setObjectName(QString::fromUtf8("currentFrame"));
        currentFrame->setMinimumSize(QSize(0, 300));
        currentFrame->setStyleSheet(QString::fromUtf8("background-color: black;"));
        currentFrame->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(currentFrame);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        retranslateUi(VideoSettings);

        QMetaObject::connectSlotsByName(VideoSettings);
    } // setupUi

    void retranslateUi(QWidget *VideoSettings)
    {
        VideoSettings->setWindowTitle(QCoreApplication::translate("VideoSettings", "Form", nullptr));
        addVideoButton->setText(QCoreApplication::translate("VideoSettings", "Add video", nullptr));
        groupBox->setTitle(QCoreApplication::translate("VideoSettings", "Fps", nullptr));
        startTime->setText(QCoreApplication::translate("VideoSettings", "00:00:00", nullptr));
        endTime->setText(QCoreApplication::translate("VideoSettings", "00:00:00", nullptr));
        startFrame->setText(QString());
        endFrame->setText(QString());
        currentFrame->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class VideoSettings: public Ui_VideoSettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIDEOSETTINGS_H
