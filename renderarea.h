#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QBrush>
#include <QPainter>
#include <QPen>
#include <QWidget>
#include <QMouseEvent>
#include<QImage>
#include<QLabel>
#include<QTimer>

#include <vector>
#include<string>
#include<linkedstructure.h>
#include <window.h>

class RenderArea : public QWidget
{
    Q_OBJECT

public:
    RenderArea(QWidget *parent = 0);

public slots:
    void UpdateMotion();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *) override;

private:
    void SetTimer();
    QTimer * timer;
    VectorXf targetPoint;
    LinkedStructure * linkstructure;
    float scale=10.0f;
    QPoint origin=QPoint(310,90);
    QPoint dollPos;
    int catchState;//0-catching 1-moving to hole
    bool isDollCatched;
    QPoint hole=QPoint(150,350);
};

#endif // RENDERAREA_H
