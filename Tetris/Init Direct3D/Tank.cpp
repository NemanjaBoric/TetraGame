#include "Tank.h"


Tank::Tank(Block* blck)
    : Figure(blck)
{
    elements.push_back(blck->AddInstance(D3DXVECTOR3(-0.0f, -0.0f, 5.0f)));
    elements.push_back(blck->AddInstance(D3DXVECTOR3(-0.0f, +1.0f, 5.0f)));
    elements.push_back(blck->AddInstance(D3DXVECTOR3(+1.0f, -0.0f, 5.0f)));
    elements.push_back(blck->AddInstance(D3DXVECTOR3(-1.0f, -0.0f, 5.0f)));
}


Tank::~Tank(void)
{
}
