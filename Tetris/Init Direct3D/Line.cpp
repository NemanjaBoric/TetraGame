#include "Line.h"


Line::Line(Block* blck):
    m_blck(blck)
{
   
    elements.push_back(blck->AddInstance(D3DXVECTOR3(-1.5f, -0.0f, 5.0f)));
    elements.push_back(blck->AddInstance(D3DXVECTOR3(-0.5f, -0.0f, 5.0f)));
    elements.push_back(blck->AddInstance(D3DXVECTOR3(+0.5f, -0.0f, 5.0f)));
    elements.push_back(blck->AddInstance(D3DXVECTOR3(+1.5f, -0.0f, 5.0f)));
}

void Line::move(D3DXVECTOR3 move_vec)
{
    for(std::vector<InstanceType*>::iterator i = elements.begin(); i != elements.end(); i++)
    {
        InstanceType* t = *i;
        t->object_position += move_vec;
    }
}

Line::~Line(void)
{
    // FIX ME
}
