#include "Block.h"
#include <D3D11.h>
#include <xnamath.h>
#include "Vertex.h"
#include "d3dx11Effect.h"
#include "MathHelper.h"
#include <d3dUtil.h>
#include <D3DX10math.h>

std::vector<InstanceType> Block::instances;
ID3D11Buffer* Block::m_instanceBuffer = 0;
ID3D11Buffer* Block::mBoxVB = 0;
ID3D11Buffer* Block::mBoxIB = 0;
int Block::m_instanceCount = 0;

int verticesNum = 0;

Vertex Block::vertexBuffer[4 * MAX_BLOCKS];
UINT Block::indexBuffer[6 * MAX_BLOCKS];

void Block::AddInstance(D3DXVECTOR3 pos)
{
    InstanceType ins;
    ins.position = pos;
    instances.push_back(ins);

    InstanceType* tmp = new InstanceType[instances.size()];

    std::vector<InstanceType>::iterator i;
    int j;

    for(i = instances.begin(), j = 0; i != instances.end(); i++, j++)
    {
        *(tmp + j) = *i;
    }


    D3D11_MAPPED_SUBRESOURCE inst;
    mCntx->Map(m_instanceBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &inst);
    memcpy(inst.pData, tmp, sizeof(InstanceType) * instances.size());
    mCntx->Unmap(m_instanceBuffer, 0);


    delete [] tmp;
}

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
		{ a, (const float*)&Colors::White   },
		{ c, (const float*)&Colors::Red     },
		{ d, (const float*)&Colors::Green   },
    };

    memcpy((vertexBuffer + 6 * verticesNum++), tmp, sizeof(Vertex) * 6);

    if(mBoxVB == NULL)
         CreateBuffers(tmp);

    index = verticesNum - 1;
}

void Block::ApplyTransform()
{
   
}



void Block::AddToBuffer(Vertex *vertices)
{
   /* D3D11_MAPPED_SUBRESOURCE inst;

    mCntx->Map(mBoxVB, 0, D3D11_MAP_WRITE_DISCARD, 0, &inst);
    memcpy(inst.pData, vertexBuffer, sizeof(Vertex) * 4 * MAX_BLOCKS);
    mCntx->Unmap(mBoxVB, 0);

    mCntx->Map(mBoxIB, 0, D3D11_MAP_WRITE_DISCARD, 0, &inst);
    memcpy(inst.pData, indexBuffer, sizeof(UINT) * 6 * MAX_BLOCKS);
    mCntx->Unmap(mBoxIB, 0);*/
}

void Block::CreateBuffers(Vertex *vertices)
{
    D3D11_BUFFER_DESC vbd;
    vbd.Usage = D3D11_USAGE_DEFAULT ;
    vbd.ByteWidth = sizeof(Vertex) * 6 ;
    vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vbd.CPUAccessFlags = 0;
    vbd.MiscFlags = 0;
	vbd.StructureByteStride = 0;
    D3D11_SUBRESOURCE_DATA vinitData;
    vinitData.pSysMem = vertexBuffer;
    md3dDevice->CreateBuffer(&vbd, &vinitData, &mBoxVB);


	// Create the index buffer

	
    D3D11_SUBRESOURCE_DATA vertexData, instanceData;

    D3D11_BUFFER_DESC instanceBufferDesc;

	// Set up the description of the instance buffer.
	instanceBufferDesc.Usage =  D3D11_USAGE_DYNAMIC  ;

	instanceBufferDesc.ByteWidth = sizeof(InstanceType) * MAX_BLOCKS;
	instanceBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	instanceBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	instanceBufferDesc.MiscFlags = 0;
	instanceBufferDesc.StructureByteStride = 0;

	// Create the instance buffer.
	HRESULT result = md3dDevice->CreateBuffer(&instanceBufferDesc, NULL, &m_instanceBuffer);

}

void Block::setBuffers(UINT* stride, UINT* offset)
{
    unsigned int strides[2];
	unsigned int offsets[2];
	ID3D11Buffer* bufferPointers[2];

// The instance buffer is just a second vertex buffer containing different information 
// so it is set on the device at the same time using the same call as the vertex buffer.
// So instead of how we previously sent in a single stride, offset, and buffer we now send 
// an array of strides, offsets, and buffers to the IASetVertexBuffers call.

// First we set the two strides to the size of the VertexType and InstanceType.

	// Set the buffer strides.
	strides[0] = sizeof(Vertex); 
	strides[1] = sizeof(InstanceType); 

    // We then set the offsets for both the vertex and instance buffer.

	// Set the buffer offsets.
	offsets[0] = 0;
	offsets[1] = 0;

    // Next we create an array that holds the pointers to the vertex buffer and the instance buffer.

	// Set the array of pointers to the vertex and instance buffers.
	bufferPointers[0] = mBoxVB;	
	bufferPointers[1] = m_instanceBuffer;

    // Finally we set both the vertex buffer and the instance buffer on the device context in the same call.

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	mCntx->IASetVertexBuffers(0, 2, bufferPointers, strides, offsets);
    mCntx->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

}

Block::~Block(void)
{
    ReleaseCOM(mBoxVB);
	ReleaseCOM(mBoxIB);
}
