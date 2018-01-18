#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <stdio.h>
#include <renderarea.h>

class QLabel;
class QPushButton;
class QSpinBox;
class QSlider;
class QComboBox;
class QMainWindow;

class RenderArea;

class Window : public QWidget
{
    Q_OBJECT

public:
    Window();
    RenderArea * renderArea;
    QPushButton * startButton;

};

#endif // WINDOW_H
