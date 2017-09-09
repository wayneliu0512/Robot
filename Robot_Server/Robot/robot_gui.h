#ifndef ROBOT_GUI_H
#define ROBOT_GUI_H

#include <QObject>
#include <QLabel>
#include <Robot/robot.h>

class Robot_GUI : public QObject
{
    Q_OBJECT
public:

    enum Color{ RED, GREEN, YELLOW, GREY };

    explicit Robot_GUI(QObject *parent = nullptr);

    ~Robot_GUI();

    Robot_GUI(Robot* _robot, QLabel *_label, QLabel *_light, QTimer *_flashTimer);

private:

    Robot *robot;

    QLabel *label, *light;

    QTimer *flashTimer;

    void setLight(Color _color, bool _flash);

private slots:

    void updateGUI(Robot::State);

    void flashYellowTimeout();
    void flashGreenTimeout();
    void flashRedTimeout();

};

#endif // ROBOT_GUI_H
