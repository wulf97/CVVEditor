#include <QDebug>

#include "CvvINodePort.h"
#include "CvvINode.h"

/*******************************/
CvvINodePort::CvvINodePort(QObject *parent,
                                bool config,
                                QString name) : QObject(parent) {
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
CvvINode *CvvINodePort::getParentNode() const {
    return dynamic_cast<CvvINode*>(parent());
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
void CvvINodePort::printMetaData() {
    QString msg;
    void *adr = this;

    msg = "[Addr: " + QString::number((int&)adr).toLocal8Bit() + "; ";
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
void CvvINodePort::setData(T8C dat) {
    m_8C = dat;

    if (m_config == PORT_CONFIG_SRC)
        emit sendData(dat);

    qDebug() << dat;
}

/*******************************/
void CvvINodePort::updateConnection(QObject *port, bool fl) {
    CvvINodePort *srcPort = dynamic_cast<CvvINodePort*>(port);
    int srcType = srcPort->getDataType();

    if (fl) {
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
                connect(srcPort, SIGNAL(sendData(Tvec8C*)), this, SLOT(setData(Tvec8C*)));
                m_selectedDataType = CVV_VEC8C;
                break;
            case CVV_VEC32I:
                connect(srcPort, SIGNAL(sendData(Tvec32I*)), this, SLOT(setData(Tvec32I*)));
                m_selectedDataType = CVV_VEC32I;
                break;
            case CVV_VEC32F:
                connect(srcPort, SIGNAL(sendData(Tvec32F*)), this, SLOT(setData(Tvec32F*)));
                m_selectedDataType = CVV_VEC32F;
                break;
            }
        }
    } else {
        m_srcPort = nullptr;
    }
}

/*******************************/
bool CvvINodePort::getData(int type, T8C &dat) const {
    if (type == CVV_8C && m_selectedDataType == CVV_8C) {
        dat = m_8C;
        return true;
    } else return false;
}

/*******************************/
bool CvvINodePort::getData(int type, T32I &dat) const {
    if (type == CVV_32I && m_selectedDataType == CVV_32I) {
        dat = m_32I;
        return true;
    } else return false;
}

/*******************************/
bool CvvINodePort::getData(int type, T32F &dat) const {
    if (type == CVV_32F && m_selectedDataType == CVV_32F) {
        dat = m_32F;
        return true;
    } else return false;
}

/*******************************/
bool CvvINodePort::getData(int type, Tvec8C *&dat) const {
    if (type == CVV_VEC8C && m_selectedDataType == CVV_VEC8C) {
        dat = m_vec8C;
        return true;
    } else return false;
}

/*******************************/
bool CvvINodePort::getData(int type, Tvec32I *&dat) const {
    if (type == CVV_VEC32I && m_selectedDataType == CVV_VEC32I) {
        dat = m_vec32I;
        return true;
    } else return false;
}

/*******************************/
bool CvvINodePort::getData(int type, Tvec32F *&dat) const {
    if (type == CVV_VEC32F && m_selectedDataType == CVV_VEC32F) {
        dat = m_vec32F;
        return true;
    } else return false;
}

/* Слоты */
/*******************************/
void CvvINodePort::setData(T32I dat) {
    m_32I = dat;

    if (m_config == PORT_CONFIG_SRC)
        emit sendData(dat);

    qDebug() << dat;
}

/*******************************/
void CvvINodePort::setData(T32F dat) {
    m_32F = dat;

    if (m_config == PORT_CONFIG_SRC)
        emit sendData(dat);
    qDebug() << dat;
}

/*******************************/
void CvvINodePort::setData(Tvec8C *dat) {
    m_vec8C = dat;

    if (m_config == PORT_CONFIG_SRC)
        emit sendData(dat);
    qDebug() << dat;
}

/*******************************/
void CvvINodePort::setData(Tvec32I *dat) {
    m_vec32I = dat;

    if (m_config == PORT_CONFIG_SRC)
        emit sendData(dat);
    qDebug() << dat;
}

/*******************************/
void CvvINodePort::setData(Tvec32F *dat) {
    m_vec32F = dat;

    if (m_config == PORT_CONFIG_SRC)
        emit sendData(dat);
    qDebug() << dat;
}
