#ifndef CCD_GUI_H
#define CCD_GUI_H

#include <QObject>
#include <CCD/ccd.h>
#include <QLabel>
class CCD_GUI : public QObject
{
    Q_OBJECT
public:
    explicit CCD_GUI(QObject *parent = nullptr);

    CCD_GUI(CCD *_ccd, QLabel *_light, QLabel *_label_SN, QLabel *_label_MAC);

    ~CCD_GUI();

private:

    CCD *ccd;

    QLabel *label_SN, *label_MAC, *light;

private slots:

    void updateGUI(CCD::State _state);
};

#endif // CCD_GUI_H
