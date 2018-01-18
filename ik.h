#ifndef JACOBIAN_H
#define JACOBIAN_H

#include <link.h>
#include <vector>

using namespace std;

class IK
{
public:
    IK(std::vector<Link> links);
    MatrixXf j_inverse;
private:
    void CalcInverse(std::vector<Link> links);
    MatrixXf Jacobian(std::vector<Link> links);
};

#endif // JACOBIAN_H
