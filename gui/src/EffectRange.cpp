#include "ui_EffectRange.h"
#include "EffectRange.h"
#include "GUIManager.h"
#include "RangeSlider.h"

EffectRange::EffectRange(QWidget *parent, int endTime) :
                         QWidget(parent),
                         ui(new Ui::EffectRange) {
    m_parent = dynamic_cast<GUIManager*>(parent);
    ui->setupUi(this);
    m_RangeSlider = new RangeSlider();
    ui->horizontalLayout_5->addWidget(m_RangeSlider);
    ui->endTime->setText(intTimeToStringTime(endTime));

    connect(m_RangeSlider,SIGNAL(lowerValueChanged(int)), this, SLOT(onLowerValueChanged(int)));
    connect(m_RangeSlider,SIGNAL(upperValueChanged(int)), this, SLOT(onUpperValueChanged(int)));

    setMaximumValue(endTime);

}

EffectRange::~EffectRange() {
    delete ui;
}


void EffectRange::setMaximumValue(int max)
{
    m_RangeSlider->setMaximum(max);
    upperValue = max;
}

int EffectRange::getMaximumValue()
{
    return upperValue;
}

void EffectRange::setMinimumValue(int min)
{
    m_RangeSlider->setMinimum(min);
    lowerValue = min;
}

int EffectRange::getMinimumValue()
{
    return lowerValue;
}

void EffectRange::setNumInList(int num)
{
    numInList = num;
}

int EffectRange::getNumInList()
{
    return numInList;
}


void EffectRange::setConnection() {
}

void EffectRange::updateEndTime(int time)
{
    setMaximumValue(time);
    setMinimumValue(0);
    ui->endTime->setText(intTimeToStringTime(time));

}

QString EffectRange::intTimeToStringTime(int length)
{
    int seconds;
    int minutes;
    int hours;
    QString second;
    QString minute;
    QString hour;
    QString lengthOfFilm;

    seconds = (length/1000)%60;
    minutes = ((length/1000)/60)%60;
    hours = ((length/1000)/60)/60;
    if(QString::number(seconds).length() == 1) {
        second = "0" + QString::number(seconds);
    } else {
        second = QString::number(seconds);
    }

    if(QString::number(minutes).length() == 1) {
        minute = "0" + QString::number(minutes);
    } else {
        minute = QString::number(minutes);
    }

    if(QString::number(hours).length() == 1) {
        hour = "0" + QString::number(hours);
    } else {
        hour = QString::number(hours);
    }

    if (hours == 0) {
        if (minutes == 0){
            lengthOfFilm = "00:00:" + second;
        } else {
            lengthOfFilm = "00:" + minute + ':' + second;
        }
    } else {
        lengthOfFilm = hour +':' + minute + ':' + second;
    }
    return lengthOfFilm;
}

void EffectRange::onLowerValueChanged(int aLowerValue)
{
    qDebug()<<aLowerValue;
    lowerValue = aLowerValue;
    emit setStartTime(lowerValue);
}

void EffectRange::onUpperValueChanged(int aUpperValue)
{
    qDebug()<<aUpperValue;
    upperValue = aUpperValue;
    emit setEndTime(upperValue);
}
