#pragma once

#include <D3D11.h>
#include <xnamath.h>
#include "Vertex.h"
#include <deque>
#include <D3DX10math.h>
#include <list>
#include "Vertex.h"

struct InstanceType
{
    // Position relative to the parent object
	D3DXVECTOR3 position;
    // Used for moving object
    D3DXVECTOR3 object_position;
    D3DXVECTOR3 rotation;
};



class Block
{
    static const int MAX_BLOCKS = 100;

    ID3D11Device* md3dDevice;
    ID3D11DeviceContext* mCntx;
    int index;
    
    int m_instanceCount;
    ID3D11Buffer* mBoxVB;
	ID3D11Buffer* mBoxIB;
    ID3D11Buffer* m_instanceBuffer;
    Vertex vertexBuffer[4 * MAX_BLOCKS];
    UINT indexBuffer[6 * MAX_BLOCKS];
    int verticesNum;
    std::deque<InstanceType> instances;
    
public:
    void setBuffers(UINT* stride, UINT* offset);
    void CreateBuffers(Vertex *vertices);
    void AddToBuffer(Vertex *vertices);
    
    InstanceType* AddInstance(D3DXVECTOR3 pos);
    inline InstanceType* GetInstance(int index){ return &(instances[index]); }
    inline int InstanceCount(){ return instances.size(); }
    void ApplyTransform();
    Block(ID3D11Device* d3dDevice, ID3D11DeviceContext* cntx, XMFLOAT3 a, XMFLOAT3 b, XMFLOAT3 c, XMFLOAT3 d);
    ~Block(void);
};

