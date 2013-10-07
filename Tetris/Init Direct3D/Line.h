#pragma once
#include "Block.h"
#include <D3D11.h>

class Line
{
    Block* m_blck;
public:
    Line(Block* blck);
    ~Line(void);
};

