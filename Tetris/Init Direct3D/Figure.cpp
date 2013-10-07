#include "Figure.h"

#define PI 3.1415926535

Figure::Figure(Block* blck)
    : m_blck(blck)
{
}


Figure::~Figure(void)
{
}
void Figure::move(D3DXVECTOR3 move_vec)
{
    for(std::vector<InstanceType*>::iterator i = elements.begin(); i != elements.end(); i++)
    {
        InstanceType* t = *i;
        t->object_position += move_vec;
    }
}

void Figure::rotate(float angle_x_deg)
{
    for(std::vector<InstanceType*>::iterator i = elements.begin(); i != elements.end(); i++)
    {
        InstanceType* t = *i;
        t->rotation.x += angle_x_deg * PI / 180.0;
    }
}