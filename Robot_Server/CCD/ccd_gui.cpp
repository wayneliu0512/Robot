#include "ccd_gui.h"
#include <QLabel>

CCD_GUI::CCD_GUI(QObject *parent) : QObject(parent)
{
}

CCD_GUI::CCD_GUI(CCD *_ccd, QLabel *_light, QLabel *_label_SN, QLabel *_label_MAC)
{
    ccd = _ccd;
    light = _light;
    label_MAC = _label_MAC;
    label_SN = _label_SN;

    connect(ccd, SIGNAL(updateGUI(CCD::State)), this, SLOT(updateGUI(CCD::State)));
    //connect CCD update GUI
}

CCD_GUI::~CCD_GUI()
{
}

void CCD_GUI::updateGUI(CCD::State _state)
{
    switch(_state)
    {
    case CCD::ONLINE:
        light->setPixmap(QPixmap(":/new/prefix1/IMG_Green.png"));
        break;
    case CCD::OFFLINE:
        light->setPixmap(QPixmap(":/new/prefix1/IMG_Grey.png"));
        break;
    case CCD::TAKING_SHOT:
        light->setPixmap(QPixmap(":/new/prefix1/IMG_Yellow.png"));
        break;
    case CCD::FINISH_SHOT:
        light->setPixmap(QPixmap(":/new/prefix1/IMG_Green.png"));
        label_SN->setText(CCD::SN);
        label_MAC->setText(CCD::MAC);
        break;
    }
}


