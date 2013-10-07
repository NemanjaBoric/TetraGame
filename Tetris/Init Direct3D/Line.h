#pragma once
#include "Block.h"
#include <D3D11.h>
#include <vector>
#include "Figure.h"

class Line: public Figure
{

public:
    Line(Block* blck);
    ~Line(void);


};

