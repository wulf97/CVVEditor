#ifndef EFFECTVIEWPORT_H
#define EFFECTVIEWPORT_H

#include <QWidget>

class GUIManager;
class QBoxLayout;

namespace Ui {
class EffectViewport;
}

class EffectViewport : public QWidget {
    Q_OBJECT

public:
    explicit EffectViewport(QWidget *parent = nullptr);
    ~EffectViewport();

    QBoxLayout *getDisplayLayout();
public slots:
    void updateFrame(QImage*);
private:
    Ui::EffectViewport *ui;
    GUIManager *m_gui;
};

#endif // EFFECTVIEWPORT_H
