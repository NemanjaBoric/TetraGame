#include "Block.h"
#include <D3D11.h>
#include <xnamath.h>
#include "Vertex.h"
#include "d3dx11Effect.h"
#include "MathHelper.h"
#include <d3dUtil.h>

ID3D11Buffer* Block::mBoxVB = 0;
ID3D11Buffer* Block::mBoxIB = 0;
int verticesNum = 0;

Vertex Block::vertexBuffer[4 * MAX_BLOCKS];
UINT Block::indexBuffer[6 * MAX_BLOCKS];

Block::Block(ID3D11Device* d3dDevice, ID3D11DeviceContext* cntx, XMFLOAT3 a, XMFLOAT3 b, XMFLOAT3 c, XMFLOAT3 d)
{
    md3dDevice = d3dDevice;
    mCntx = cntx;
    
    Vertex tmp[] = {
		/*{ XMFLOAT3(0.0f, 0.0f, 0.0f), (const float*)&Colors::White   },
		{ XMFLOAT3(0.0f, -0.5f, 0.0f), (const float*)&Colors::Red   },
		{ XMFLOAT3(0.5f, 0.0f, 0.0f), (const float*)&Colors::Blue   },
		{ XMFLOAT3(0.5f, -0.5f, 0.0f), (const float*)&Colors::Green   },*/
        { a, (const float*)&Colors::White   },
		{ b, (const float*)&Colors::Black   },
		{ c, (const float*)&Colors::Red     },
		{ d, (const float*)&Colors::Green   },
    };

    memcpy((vertexBuffer + 4 * verticesNum++), tmp, sizeof(Vertex) * 4);

     UINT indices[] = {
		// front face
		0 + 4 * (verticesNum - 1), 1 + 4 * (verticesNum - 1), 2 + 4 * (verticesNum - 1),
        0 + 4 * (verticesNum - 1), 2 + 4 * (verticesNum - 1), 3 + 4 * (verticesNum - 1)
	};

    memcpy((indexBuffer + 6 * (verticesNum - 1)), indices, sizeof(UINT) * 6);

    if(mBoxVB == NULL)
         CreateBuffers(tmp, indices);

    AddToBuffer(tmp, indices);
}

void Block::AddToBuffer(Vertex *vertices, UINT* indices)
{
    D3D11_MAPPED_SUBRESOURCE inst;

    mCntx->Map(mBoxVB, 0, D3D11_MAP_WRITE_DISCARD, 0, &inst);
    memcpy(inst.pData, vertexBuffer, sizeof(Vertex) * 4 * MAX_BLOCKS);
    mCntx->Unmap(mBoxVB, 0);

    mCntx->Map(mBoxIB, 0, D3D11_MAP_WRITE_DISCARD, 0, &inst);
    memcpy(inst.pData, indexBuffer, sizeof(UINT) * 6 * MAX_BLOCKS);
    mCntx->Unmap(mBoxIB, 0);
}

void Block::CreateBuffers(Vertex *vertices, UINT* indices)
{
    D3D11_BUFFER_DESC vbd;
    vbd.Usage = D3D11_USAGE_DYNAMIC ;
    vbd.ByteWidth = sizeof(Vertex) * 4 * MAX_BLOCKS;
    vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    vbd.MiscFlags = 0;
	vbd.StructureByteStride = 0;
    D3D11_SUBRESOURCE_DATA vinitData;
    vinitData.pSysMem = vertices;
    md3dDevice->CreateBuffer(&vbd, &vinitData, &mBoxVB);


	// Create the index buffer

	

	D3D11_BUFFER_DESC ibd;
    ibd.Usage = D3D11_USAGE_DYNAMIC ;
    ibd.ByteWidth = sizeof(UINT) * 6 * MAX_BLOCKS;
    ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
    ibd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    ibd.MiscFlags = 0;
	ibd.StructureByteStride = 0;
    D3D11_SUBRESOURCE_DATA iinitData;
    iinitData.pSysMem = indices;
    md3dDevice->CreateBuffer(&ibd, &iinitData, &mBoxIB);
}

void Block::setBuffers(UINT* stride, UINT* offset)
{


    mCntx->IASetVertexBuffers(0, 1, &mBoxVB, stride, offset);
	mCntx->IASetIndexBuffer(mBoxIB, DXGI_FORMAT_R32_UINT, 0);
}

Block::~Block(void)
{
    ReleaseCOM(mBoxVB);
	ReleaseCOM(mBoxIB);
}
