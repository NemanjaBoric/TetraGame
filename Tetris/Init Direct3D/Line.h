#pragma once
#include "Block.h"
#include <D3D11.h>
#include <vector>

class Line
{
    Block* m_blck;
    std::vector<InstanceType*> elements;
public:
    Line(Block* blck);
    ~Line(void);

    void move(D3DXVECTOR3 move_vec);
};

