#include <QDebug>

#include "CvvINodePort.h"
#include "CvvINode.h"

/*******************************/
CvvINodePort::CvvINodePort(QObject *parent,
                           bool config,
                           QString name) : QObject(parent) {
    m_node = dynamic_cast<CvvINode*>(parent);
    m_config = config;
    m_type = 0;
    m_name = name;
}

/*******************************/
CvvINodePort::~CvvINodePort() {

}

/*******************************/
void CvvINodePort::setDataType(int type) {
    if (m_config == PORT_CONFIG_DST) {
        m_type = type;
    } else {
        int count = 0;

        for (int i = 0; i < 8*sizeof(int); i++) {
            if (type & (1 << i)) count++;
        }

        if (count == 1) m_type = type;
    }
}

/*******************************/
void CvvINodePort::activate(bool activate) {
    m_isActive = activate;
}

/*******************************/
void CvvINodePort::turnOn(bool fl) {
    m_on = fl;
}

/*******************************/
CvvINode *CvvINodePort::getParentNode() const {
    return m_node;
}

/*******************************/
QString CvvINodePort::getName() const {
    return m_name;
}

/*******************************/
int CvvINodePort::getConfig() const {
    return m_config;
}

/*******************************/
int CvvINodePort::getDataType() const {
    return m_type;
}

/*******************************/
int CvvINodePort::getSelectedDataType() const {
    return m_selectedDataType;
}

/*******************************/
bool CvvINodePort::isActive() const {
    if (m_on) return m_isActive;
    return false;

}

/*******************************/
int CvvINodePort::getDuration() const {
    if (m_config) {
        if (m_srcPort) {
            return m_srcPort->getDuration();
        }
    } else {
        return m_duration;
    }

    return 0;
}

/*******************************/
int CvvINodePort::getTime() const {
    if (m_config) {
        if (m_srcPort) {
            return m_srcPort->getTime();
        }
    } else {
        return m_time;
    }

    return 0;
}

/*******************************/
bool CvvINodePort::isChenged() const {
    return m_isChenged;
}

/*******************************/
void CvvINodePort::printMetaData() {
    QString msg;
    void *adr = this;

    msg = "[Addr: " + QString::number((unsigned int&)adr).toLocal8Bit() + "; ";
    if (m_isActive) {
        msg += "active; ";
    } else {
        msg += "inactive; ";
    }
    msg += "Name: " + m_name + "; Config: ";

    if (m_config) {
        msg += "dst; ";
    } else {
        msg += "src; ";
    }

    msg += "Data types:";
    if (m_type != 0) {
        if (CVV_8C & m_type) {
            msg += " CVV_8C";
        }

        if (CVV_32I & m_type) {
            msg += " CVV_32I";
        }

        if (CVV_32F & m_type) {
            msg += " CVV_32F";
        }

        if (CVV_VEC8C & m_type) {
            msg += " CVV_VEC8C";
        }

        if (CVV_VEC32I & m_type) {
            msg += " CVV_VEC32I";
        }

        if (CVV_VEC32F & m_type) {
            msg += " CVV_VEC32F";
        }

        if (CVV_IMG8C1 & m_type) {
            msg += " CVV_IMG8C1";
        }

        if (CVV_IMG8C2 & m_type) {
            msg += " CVV_IMG8C2";
        }

        if (CVV_IMG8C3 & m_type) {
            msg += " CVV_IMG8C3";
        }

    } else {
        msg += " NoTypeConfig";
    }
    msg += " ; srcPort: ";
    if (m_srcPort) {
        msg += QString(m_srcPort->getName()).toLocal8Bit() + "(" + QString::number((int&)m_srcPort).toLocal8Bit() + ")";
    } else {
        msg += "no";
    }
    msg += "]";

    qDebug() << msg << endl;
}

/*******************************/
bool CvvINodePort::getData(int type, T8C &dat) {
    if (type == CVV_8C && m_selectedDataType == CVV_8C) {
        dat = m_8C;
        m_isChenged = false;
        return true;
    } else return false;
}

/*******************************/
bool CvvINodePort::getData(int type, T32I &dat) {
    if (type == CVV_32I && m_selectedDataType == CVV_32I) {
        dat = m_32I;
        m_isChenged = false;
        return true;
    } else return false;
}

/*******************************/
bool CvvINodePort::getData(int type, T32F &dat) {
    if (type == CVV_32F && m_selectedDataType == CVV_32F) {
        dat = m_32F;
        m_isChenged = false;
        return true;
    } else return false;
}

/*******************************/
bool CvvINodePort::getData(int type, Tvec8C &dat) {
    if (type == CVV_VEC8C && m_selectedDataType == CVV_VEC8C) {
        dat = m_vec8C;
        m_isChenged = false;
        return true;
    } else return false;
}

/*******************************/
bool CvvINodePort::getData(int type, Tvec32I &dat) {
    if (type == CVV_VEC32I && m_selectedDataType == CVV_VEC32I) {
        dat = m_vec32I;
        m_isChenged = false;
        return true;
    } else return false;
}

/*******************************/
bool CvvINodePort::getData(int type, Tvec32F &dat) {
    if (type == CVV_VEC32F && m_selectedDataType == CVV_VEC32F) {
        dat = m_vec32F;
        m_isChenged = false;
        return true;
    } else return false;
}

/*******************************/
bool CvvINodePort::getData(int type, Timg &dat) {
    if (type == CVV_IMG8C1 && m_selectedDataType == CVV_IMG8C1) {
        dat = m_img;
        m_isChenged = false;
        return true;
    } else if (type == CVV_IMG8C2 && m_selectedDataType == CVV_IMG8C2) {
        dat = m_img;
        m_isChenged = false;
        return true;
    } else if (type == CVV_IMG8C3 && m_selectedDataType == CVV_IMG8C3) {
        dat = m_img;
        m_isChenged = false;
        return true;
    }

    return false;
}


/* Слоты */
/*******************************/
void CvvINodePort::updateConnection(QObject *port, bool fl) {
    CvvINodePort *srcPort = dynamic_cast<CvvINodePort*>(port);
    int srcType = srcPort->getDataType();

    if (fl) {
        connect(srcPort, SIGNAL(setDurationSignal(int)), this, SLOT(setDuration(int)));
        connect(srcPort, SIGNAL(setTimeSignal(int)), this, SLOT(setTime(int)));
        if (m_type & srcType) {
            m_srcPort = srcPort;
            m_selectedDataType = m_srcPort->getDataType();
            switch (srcType) {
            case CVV_8C:
                connect(srcPort, SIGNAL(sendData(T8C)), this, SLOT(setData(T8C)));
                m_selectedDataType = CVV_8C;
                break;
            case CVV_32I:
                connect(srcPort, SIGNAL(sendData(T32I)), this, SLOT(setData(T32I)));
                m_selectedDataType = CVV_32I;
                break;
            case CVV_32F:
                connect(srcPort, SIGNAL(sendData(T32F)), this, SLOT(setData(T32F)));
                m_selectedDataType = CVV_32F;
                break;
            case CVV_VEC8C:
                connect(srcPort, SIGNAL(sendData(Tvec8C)), this, SLOT(setData(Tvec8C)));
                m_selectedDataType = CVV_VEC8C;
                break;
            case CVV_VEC32I:
                connect(srcPort, SIGNAL(sendData(Tvec32I)), this, SLOT(setData(Tvec32I)));
                m_selectedDataType = CVV_VEC32I;
                break;
            case CVV_VEC32F:
                connect(srcPort, SIGNAL(sendData(Tvec32F)), this, SLOT(setData(Tvec32F)));
                m_selectedDataType = CVV_VEC32F;
                break;
            case CVV_IMG8C1:
                connect(srcPort, SIGNAL(sendData(Timg)), this, SLOT(setData(Timg)));
                m_selectedDataType = CVV_IMG8C1;
                break;
            case CVV_IMG8C2:
                connect(srcPort, SIGNAL(sendData(Timg)), this, SLOT(setData(Timg)));
                m_selectedDataType = CVV_IMG8C2;
                break;
            case CVV_IMG8C3:
                connect(srcPort, SIGNAL(sendData(Timg)), this, SLOT(setData(Timg)));
                m_selectedDataType = CVV_IMG8C3;
                break;
            }
        }

        m_node->init();
    } else {
        srcPort->disconnect(this);
        m_srcPort = nullptr;
    }
}

/*******************************/
void CvvINodePort::setDuration(int duration) {
    m_duration = duration;

    if (!m_config) {
        emit setDurationSignal(duration);
    } else {
        m_node->init();
    }
}

/*******************************/
void CvvINodePort::setTime(int time) {
    m_time = time;

    if (!m_config) {
        emit setTimeSignal(time);
    }
}

/*******************************/
void CvvINodePort::setData(T8C dat) {
    m_8C = dat;
    m_isChenged = true;

    if (m_config == PORT_CONFIG_SRC)
        emit sendData(dat);

//    qDebug() << dat;
}

/*******************************/
void CvvINodePort::setData(T32I dat) {
    m_32I = dat;
    m_isChenged = true;

    if (m_config == PORT_CONFIG_SRC)
        emit sendData(dat);
//    else
//        getParentNode()->updateNode();

//    qDebug() << dat;
}

/*******************************/
void CvvINodePort::setData(T32F dat) {
    m_32F = dat;
    m_isChenged = true;

    if (m_config == PORT_CONFIG_SRC)
        emit sendData(dat);
//    qDebug() << dat;
}

/*******************************/
void CvvINodePort::setData(Tvec8C dat) {
    m_vec8C = dat;
    m_isChenged = true;

    if (m_config == PORT_CONFIG_SRC)
        emit sendData(dat);
//    qDebug() << dat;
}

/*******************************/
void CvvINodePort::setData(Tvec32I dat) {
    m_vec32I = dat;
    m_isChenged = true;

    if (m_config == PORT_CONFIG_SRC)
        emit sendData(dat);
//    qDebug() << dat;
}

/*******************************/
void CvvINodePort::setData(Tvec32F dat) {
    m_vec32F = dat;
    m_isChenged = true;

    if (m_config == PORT_CONFIG_SRC)
        emit sendData(dat);
//    qDebug() << dat;
}

/*******************************/
void CvvINodePort::setData(Timg dat) {
    m_img = dat;
    m_isChenged = true;

    if (m_config == PORT_CONFIG_SRC)
        emit sendData(dat);
//    qDebug() << dat;
}


