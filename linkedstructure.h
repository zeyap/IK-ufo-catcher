#ifndef LINKEDSTRUCTURE_H
#define LINKEDSTRUCTURE_H
#include<link.h>
#include<ik.h>
#include<vector>
using namespace std;

class LinkedStructure
{
public:
    LinkedStructure();
    void UpdateMotion();
    bool isTargetReached(float threshold);
    void setTarget(VectorXf newTarget);
    std::vector<Link> getLinks(){return links;}
    float distToEndPos(VectorXf point){
        VectorXf diff=point-endPos;
        return sqrt(diff(0)*diff(0)+diff(1)*diff(1));
    }
private:
    std::vector<Link> links;
    void InitLinks();
    void CalcEndPosition();
    void initEndPosition();
    void calcLinksAndMoveBy(float dx,float dy);
    VectorXf endPos;
    VectorXf currTargetPos;

    float motionStep=0.1f;
    void Rotate(Link & subj,int i,float rAngle);
};

#endif // LINKEDSTRUCTURE_H
