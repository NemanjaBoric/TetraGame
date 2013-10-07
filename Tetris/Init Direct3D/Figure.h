#pragma once

#include "Block.h"
#include <vector>

class Figure
{
protected:
    Block* m_blck;
    std::vector<InstanceType*> elements;
public:
    Figure(Block* blck);
    ~Figure(void);

    void move(D3DXVECTOR3 move_vec);
    void rotate(float angle_x);
    D3DXVECTOR3& GetPosition();
};

