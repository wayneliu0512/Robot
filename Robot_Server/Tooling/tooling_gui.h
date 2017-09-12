#ifndef TOOLING_GUI_H
#define TOOLING_GUI_H

#include <QObject>
#include <QLabel>
#include <QTimer>
#include <QTime>
#include <Tooling/tooling.h>
#include <QLCDNumber>
#include <QListWidget>
class Tooling_GUI : public QObject
{
    Q_OBJECT
public:

    enum Color{ RED, GREEN, YELLOW, GREY };

    explicit Tooling_GUI(QObject *parent = nullptr);

    ~Tooling_GUI();

    Tooling_GUI(Tooling *_tooling, QListWidget* _list, QLabel* _light, QLCDNumber* _clock, QTimer* _flashTimer);

private:

    Tooling* tooling;

    QLabel *light;

    QListWidget *list;

    QTimer *flashTimer, *clockTimer;

    QTime clockTime = QTime(0,0);

    QLCDNumber *clock;

    void initializeClock();

    void setLight(Color _color, bool _flash);

private slots:

    void updateGUI(Tooling::State _state);
    void update_GUI_Message(QString _str);

    void flashYellowTimeout();
    void flashGreenTimeout();
    void flashRedTimeout();

    void clockTimeUpdate();

};

#endif // TOOLING_GUI_H
