#include "linkedstructure.h"

LinkedStructure::LinkedStructure()
{
    InitLinks();
    CalcEndPosition();
    setTarget(endPos);
}

void LinkedStructure::InitLinks(){
    links.push_back(Link(10,-160.0f/180*PI));
    links.push_back(Link(8,140.0f/180*PI));
    links.push_back(Link(8,-140.0f/180*PI));
    links.push_back(Link(4,140.0f/180*PI));
    links.push_back(Link(4,-70.0f/180*PI));
//    links.push_back(Link(8,0));
}

void LinkedStructure::CalcEndPosition(){
    float angle=0;
    endPos=VectorXf::Zero(2,1);
    for(int i=0;i<links.size();i++){
        angle+=links[i].mAngle;
        endPos(0)+=links[i].length*cos(angle);
        endPos(1)-=links[i].length*sin(angle);
        links[i].position=endPos;
        links[i].wAngle=angle;
    }

}

void LinkedStructure::setTarget(VectorXf newTarget){
    float x=newTarget(0);
    float y=newTarget(1);
    float l=sqrt(x*x+y*y);
    float maxlen=0;
    for(int i=0;i<links.size();i++){
        maxlen+=links[i].length;
    }
    if(l<maxlen)
        currTargetPos=newTarget;

}

void LinkedStructure::UpdateMotion(){
    if(!isTargetReached(Threshold)){
        float x_t,y_t;
        x_t=(currTargetPos(0)-endPos(0)>0.5)?motionStep:-motionStep;
        y_t=(currTargetPos(1)-endPos(1)>0.5)?-motionStep:motionStep;
        calcLinksAndMoveBy(x_t,y_t);
    }
}

bool LinkedStructure::isTargetReached(float threshold){
    if(fabs(currTargetPos(0)-endPos(0))<threshold&&fabs(currTargetPos(1)-endPos(1))<threshold){
        return true;
    }
    else{
        return false;
    }
}

void LinkedStructure::calcLinksAndMoveBy(float dx,float dy){
    VectorXf dAngles=VectorXf::Zero(links.size(),1);
    VectorXf dPosition=VectorXf::Zero(2,1);
    dPosition(0)=dx;
    dPosition(1)=dy;
    IK ik(links);
    dAngles=ik.j_inverse*dPosition;
    for(int i=0;i<links.size();i++){
        links[i].mAngle+=dAngles(i);
    }
    CalcEndPosition();
}
