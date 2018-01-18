#include "renderarea.h"

RenderArea::RenderArea(QWidget *parent)
    : QWidget(parent)
{
    linkstructure=new LinkedStructure;
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
    SetTimer();
    vector<Link> links=linkstructure->getLinks();
    Link end=links[links.size()-1];
    targetPoint=end.position;

    catchState=1;
    isDollCatched=true;

    dollPos=QPoint(targetPoint(0),targetPoint(1));
}

void RenderArea::SetTimer(){

    timer = new QTimer(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(UpdateMotion()));
    timer->start(10);//interval
}

void RenderArea::UpdateMotion(){

    if(!linkstructure->isTargetReached(Threshold))
    {
        linkstructure->UpdateMotion();
        update();
    }else{
        if(catchState==0){
            isDollCatched=true;
            update();
        }
    }
}

void RenderArea::mousePressEvent(QMouseEvent *event){
    //float x = event->pos().x()-origin.x();
    //float y = event->pos().y()-origin.y();
    if(linkstructure->isTargetReached(Threshold)){
        if(catchState==0){
            catchState=1;
        }else if(catchState==1){
            catchState=0;
        }
    }

    float x,y;
    if(catchState==0){
        x=620*(0.4+0.35*rand()/(RAND_MAX+1.0))-origin.x();
        y=620*(0.5+0.05*rand()/(RAND_MAX+1.0))-origin.y();
        dollPos=QPoint(x,y);
        isDollCatched=false;
    }
    if(catchState==1){
        x=hole.x()-origin.x();
        y=hole.y()-origin.y();//hole
    }
    targetPoint(0)=x/scale;
    targetPoint(1)=y/scale;

    linkstructure->setTarget(targetPoint);
}


void RenderArea::paintEvent(QPaintEvent *){
    QColor cPoint=QColor(0,0,255);
    QColor cLine=QColor(0,0,255);
    QBrush brush;

    QPainter painter(this);

    painter.setPen(QPen(cPoint,0));

    vector<Link> currLinks=linkstructure->getLinks();

    //points

    for(int i=0;i<currLinks.size();i++){
        QPoint currp=origin+QPoint(scale*currLinks[i].position(0),scale*currLinks[i].position(1));
        painter.drawEllipse(currp,3,3);
    }

    painter.setPen(QPen(cLine,0));
    QPainterPath path;
    path.lineTo(origin);
    for(int i=0;i<currLinks.size();i++){
        QPoint currp=origin+QPoint(scale*currLinks[i].position(0),scale*currLinks[i].position(1));
        path.lineTo(currp);
    }
    painter.drawPath(path);

    QPixmap background;
    background.load(":\\image\\bg.png");
    painter.drawPixmap(0,0,600,625,background);
    QPixmap arm;
    arm.load(":\\image\\arm1.png");
    float r=arm.height()/2;
    QPixmap doll;
    doll.load(":\\image\\doll.png");

    QPoint linkEnd=scale*QPoint(currLinks[currLinks.size()-1].position(0),currLinks[currLinks.size()-1].position(1));
    QTransform trans_doll;
    if(!isDollCatched&&catchState==0){
        trans_doll.translate(origin.x()+dollPos.x(),origin.y()+dollPos.y());
    }else{
        trans_doll.translate(origin.x()+linkEnd.x(),origin.y()+linkEnd.y());
    }
    trans_doll.translate(-doll.width()/2,-doll.height()/4);
    painter.setWorldTransform(trans_doll);
    painter.drawPixmap(0,0,doll);
    for(int i=currLinks.size()-1;i>=0;i--){
        QTransform trans;
        QPoint rotCenter;
        qreal rot=0;
        if(i==0){
            arm.load(":\\image\\arm1.png");
        }else if(i>=1&&i<=2){
            arm.load(":\\image\\arm2.png");
        }else if(i==3){
            arm.load(":\\image\\arm3.png");
        }else{
            if(isDollCatched){
                arm.load(":\\image\\catcher.png");
            }else{
                arm.load(":\\image\\catcher_0.png");
            }

        }

        if(i>0){
            rotCenter=scale*QPoint(currLinks[i-1].position(0),currLinks[i-1].position(1));
        }
        else if(i==0){
            rotCenter=QPoint(0,0);
        }
        trans.translate(origin.x(),origin.y());
        trans.translate(rotCenter.x(),rotCenter.y());
        rot=-currLinks[i].wAngle/PI*180;
        trans.rotate(rot);
        trans.translate(-r,-r);
        //
        painter.setWorldTransform(trans);

        painter.drawPixmap(0,0,arm);
    }

    QPixmap base;
    base.load(":\\image\\base.png");
    QTransform trans_base;
    trans_base.translate(origin.x()-base.width()/2,origin.y()-2*r);
    painter.setWorldTransform(trans_base);

    painter.drawPixmap(0,0,base);

}
