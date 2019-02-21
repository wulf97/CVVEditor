#include "GUIManager.h"

GUIManager::GUIManager(QObject *parent) : QObject(parent) {

}

void GUIManager::setCore(QObject *core) {
    m_core = core;
}
