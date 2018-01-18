#ifndef LINK_H
#define LINK_H
#define Threshold 0.5
#define PI 3.14
#include <Eigen/Dense>

using namespace Eigen;

class Link{
public:
    Link(float l,float angle){
        length=l;
        mAngle=angle;//counter clockwise //in radian
        position=VectorXf::Zero(2,1);
        wAngle=0;
    }
    float length;
    float mAngle;
    VectorXf position;
    float wAngle;
};

#endif // LINK_H
