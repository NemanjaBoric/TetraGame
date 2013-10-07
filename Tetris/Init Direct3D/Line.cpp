#include "Line.h"


Line::Line(Block* blck):
    Figure(blck)
{
    elements.push_back(blck->AddInstance(D3DXVECTOR3(-1.5f, -0.0f, 5.0f)));
    elements.push_back(blck->AddInstance(D3DXVECTOR3(-0.5f, -0.0f, 5.0f)));
    elements.push_back(blck->AddInstance(D3DXVECTOR3(+0.5f, -0.0f, 5.0f)));
    elements.push_back(blck->AddInstance(D3DXVECTOR3(+1.5f, -0.0f, 5.0f)));
}



Line::~Line(void)
{
    // FIX ME
}
