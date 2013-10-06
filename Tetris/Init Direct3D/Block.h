#pragma once

#include <D3D11.h>
#include <xnamath.h>
#include "Vertex.h"
#include <vector>
#include <D3DX10math.h>

struct InstanceType
	{
		D3DXVECTOR3 position;
	};

class Block
{
    static const int MAX_BLOCKS = 100;

    ID3D11Device* md3dDevice;
    ID3D11DeviceContext* mCntx;
    int index;
    
    static int m_instanceCount;
    static ID3D11Buffer* mBoxVB;
	static ID3D11Buffer* mBoxIB;
    static ID3D11Buffer* m_instanceBuffer;
    static Vertex vertexBuffer[4 * MAX_BLOCKS];
    static UINT indexBuffer[6 * MAX_BLOCKS];

    static std::vector<InstanceType> instances;
    
public:
    void setBuffers(UINT* stride, UINT* offset);
    void CreateBuffers(Vertex *vertices);
    void AddToBuffer(Vertex *vertices);
    
    void AddInstance(D3DXVECTOR3 pos);
    inline static InstanceType* GetInstance(int index){ return &(instances[index]); }
    inline static int InstanceCount(){ return instances.size(); }
    void ApplyTransform();
    Block(ID3D11Device* d3dDevice, ID3D11DeviceContext* cntx, XMFLOAT3 a, XMFLOAT3 b, XMFLOAT3 c, XMFLOAT3 d);
    ~Block(void);
};

