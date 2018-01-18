#include "ik.h"

IK::IK(vector<Link> links)
{
    CalcInverse(links);
}

void IK::CalcInverse(vector<Link> links)
{
    MatrixXf j = Jacobian(links);
    MatrixXf jjtInv = (j * j.transpose());
    jjtInv = jjtInv.inverse();
    j_inverse = j.transpose() * jjtInv;
}

MatrixXf IK::Jacobian(vector<Link> links){
    MatrixXf j = MatrixXf::Zero(2,links.size());

    for (int col = 0; col < links.size(); col++)
    {
        float angle = 0;
        for (int i = 0; i < links.size(); i++)
        {
            angle += links[i].mAngle;
            if (i >= col)
            {
                j(0, col) -= (links[i].length*sin(angle));
                j(1, col) += (links[i].length*cos(angle));
            }
        }
    }

    return j;
}
