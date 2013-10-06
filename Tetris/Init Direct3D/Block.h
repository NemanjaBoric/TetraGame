#pragma once

#include <D3D11.h>
#include <xnamath.h>
#include "Vertex.h"



class Block
{
    static const int MAX_BLOCKS = 100;

    ID3D11Device* md3dDevice;
    ID3D11DeviceContext* mCntx;

    static ID3D11Buffer* mBoxVB;
	static ID3D11Buffer* mBoxIB;

    static Vertex vertexBuffer[4 * MAX_BLOCKS];
    static UINT indexBuffer[6 * MAX_BLOCKS];
public:
    void setBuffers(UINT* stride, UINT* offset);
    void CreateBuffers(Vertex *vertices, UINT* indices);
    void AddToBuffer(Vertex *vertices, UINT* indices);
    
    Block(ID3D11Device* d3dDevice, ID3D11DeviceContext* cntx, XMFLOAT3 a, XMFLOAT3 b, XMFLOAT3 c, XMFLOAT3 d);
    ~Block(void);
};

