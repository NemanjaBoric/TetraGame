#include "Line.h"


Line::Line(Block* blck):
    m_blck(blck)
{
   
    blck->AddInstance(D3DXVECTOR3(-1.5f, -0.0f, 5.0f));
    blck->AddInstance(D3DXVECTOR3(-0.5f, -0.0f, 5.0f));
    blck->AddInstance(D3DXVECTOR3(+0.5f, -0.0f, 5.0f));
    blck->AddInstance(D3DXVECTOR3(+1.5f, -0.0f, 5.0f));
}


Line::~Line(void)
{
}
