#pragma once

#include "csingletonbase.h"
#include "cBoundBox.h"
#include "cBaseObject.h"
#include "cTerrain.h"

class cPhysicManager :public cSingletonBase<cPhysicManager>
{

public:
	cPhysicManager(void);
	~cPhysicManager(void);


	//���̰� �ٿ�忡 �浹�ߴ��� Ȯ��
	bool IsRayHitBound( 
		LPRay Ray,				//����
		cBoundSphere* pBound,	//�ٿ��
		cTransform* pBoundTrans,  //�ٿ���� Transform
		D3DXVECTOR3* pHitPos,     //Hit ��ġ ( NULL �̸� ���� �ȵ� )
		D3DXVECTOR3* pHitNormal	  //Hit �� �븻 ( NULL �̸� ���� �ȵ� )
		);


	//���̰� �ٿ�忡 �浹�ߴ��� Ȯ��
	bool IsRayHitBound( 
		LPRay Ray,				//����
		cBoundBox* pBound,			//�ٿ��
		cTransform* pBoundTrans,	//�ٿ���� Transform
		D3DXVECTOR3* pHitPos,     //Hit ��ġ ( NULL �̸� ���� �ȵ� )
		D3DXVECTOR3* pHitNormal	  //Hit �� �븻 ( NULL �̸� ���� �ȵ� )
		);


	//���̰� ������Ʈ�� �浹�ߴ���....
	bool IsRayHitStaticMeshObject( 
		LPRay pRay,				//����
		cBaseObject* pObject,	//Base Object
		D3DXVECTOR3* pHitPos,     //Hit ��ġ ( NULL �̸� ���� �ȵ� )
		D3DXVECTOR3* pHitNormal	  //Hit �� �븻 ( NULL �̸� ���� �ȵ� )
		);

	//���̰� ������Ʈ�� �浹�ߴ���....
	//�������̵� - ��ȣ�� �ص�.
	bool IsRayHitStaticMeshObject(
		LPRay inRay,				//����
		cBaseObject* pObject,	//Base Object
		cTransform* pTrans,
		D3DXVECTOR3* pHitPos,     //Hit ��ġ ( NULL �̸� ���� �ȵ� )
		D3DXVECTOR3* pHitNormal	  //Hit �� �븻 ( NULL �̸� ���� �ȵ� )
		);


	//���̰� ���� �浹�ߴ��� Ȯ��
	bool IsRayHitSphere(
		LPRay Ray,
		const D3DXVECTOR3* center, 
		float radius, 
		D3DXVECTOR3* pHitPos,     //Hit ��ġ ( NULL �̸� ���� �ȵ� )
		D3DXVECTOR3* pHitNormal	  //Hit �� �븻 ( NULL �̸� ���� �ȵ� )
		);

	bool IsPointSphere(cTransform* pTransA, float radiusA, cTransform* pTransB);
	bool IsPointSphere(cTransform* pTransA, float radiusA, D3DXVECTOR3 centerB);

	bool IsOverlap( cBaseObject* pObjA, cBaseObject* pObjB );
	
	//2���� �ٿ�� ���� �⵿ ������ ��´�.
	bool IsOverlap( cTransform* pTransA, cBoundSphere* pBoundA, cTransform* pTransB, cBoundSphere* pBoundB );
	bool IsOverlap( cTransform* pTransA, cBoundBox* pBoundA, cTransform* pTransB, cBoundBox* pBoundB );
	
	bool IsOverlap( cTransform* pTransA, cBoundSphere* pBoundA, cTransform* pTransB, cBoundBox* pBoundB );
	bool IsOverlap( cTransform* pTransA, cBoundBox* pBoundA, cTransform* pTransB, cBoundSphere* pBoundB );


	bool IsBlocking( cBaseObject* pObjA, cBaseObject* pObjB, float moveFactor = 0.0f );

	//2���� �ٿ�� ���Ǿ���� �⵿�ϰ� ��ġ�� �ʰ� �Ѵ�.
	//moveFactor �� 0 �ϼ��� ��Ĩ�� ���� B �� �����δ�.
	//moveFactor �� 0.5 �̸� ��Ĩ�� ���� A �� B �� �Ȱ��������� �����δ�.
	//moveFactor �� 1 �ϼ��� ��Ĩ�� ���� A �� �����δ�.
	bool IsBlocking( 
		cTransform* pTransA, cBoundSphere* pBoundA, 
		cTransform* pTransB, cBoundSphere* pBoundB ,
		float moveFactor = 0.0f );
	

	bool IsBlocking( 
		cTransform* pTransA, cBoundBox* pBoundA, 
		cTransform* pTransB, cBoundBox* pBoundB ,
		float moveFactor = 0.0f );



	//�� 3���� ���� ����� �����.
	void CreatePlane( LPD3DXPLANE	pOutPlane, const D3DXVECTOR3* p0, const D3DXVECTOR3* p1, const D3DXVECTOR3* p2 );

	//������ �������� �������� �ִܰŸ�
	float PlaneDot( const LPD3DXPLANE pPlane,  const D3DXVECTOR3* point );

	//�������� ����� �浹 ��ġ
	bool IntersectRayToPlane( D3DXVECTOR3* pOut, const LPRay pRay, const LPD3DXPLANE pPlane, bool bCheck2Side = false );

	//��ä�ù����� ����� �浹��ġ. Trans1�� �߽��̰� Trans2�� üũ�� Ÿ���̴�.
	bool intersectSector(const cTransform* Trans1, const cTransform* Trans2, float length, float sight);

	D3DXVECTOR3 getLastHeight(cBaseObject* enumy, Ray* ray, cTerrain* terrain,D3DXVECTOR3* outPos);

	
};


#define PHYSICS_MGR cPhysicManager::GetInstance()


