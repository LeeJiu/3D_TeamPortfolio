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


	//레이가 바운드에 충돌했는지 확인
	bool IsRayHitBound( 
		LPRay Ray,				//레이
		cBoundSphere* pBound,	//바운드
		cTransform* pBoundTrans,  //바운드의 Transform
		D3DXVECTOR3* pHitPos,     //Hit 위치 ( NULL 이면 대입 안됨 )
		D3DXVECTOR3* pHitNormal	  //Hit 의 노말 ( NULL 이면 대입 안됨 )
		);


	//레이가 바운드에 충돌했는지 확인
	bool IsRayHitBound( 
		LPRay Ray,				//레이
		cBoundBox* pBound,			//바운드
		cTransform* pBoundTrans,	//바운드의 Transform
		D3DXVECTOR3* pHitPos,     //Hit 위치 ( NULL 이면 대입 안됨 )
		D3DXVECTOR3* pHitNormal	  //Hit 의 노말 ( NULL 이면 대입 안됨 )
		);


	//레이가 오브젝트와 충돌했는지....
	bool IsRayHitStaticMeshObject( 
		LPRay pRay,				//레이
		cBaseObject* pObject,	//Base Object
		D3DXVECTOR3* pHitPos,     //Hit 위치 ( NULL 이면 대입 안됨 )
		D3DXVECTOR3* pHitNormal	  //Hit 의 노말 ( NULL 이면 대입 안됨 )
		);

	//레이가 오브젝트와 충돌했는지....
	//오버라이딩 - 지호가 해둠.
	bool IsRayHitStaticMeshObject(
		LPRay inRay,				//레이
		cBaseObject* pObject,	//Base Object
		cTransform* pTrans,
		D3DXVECTOR3* pHitPos,     //Hit 위치 ( NULL 이면 대입 안됨 )
		D3DXVECTOR3* pHitNormal	  //Hit 의 노말 ( NULL 이면 대입 안됨 )
		);


	//레이가 구와 충돌했는지 확인
	bool IsRayHitSphere(
		LPRay Ray,
		const D3DXVECTOR3* center, 
		float radius, 
		D3DXVECTOR3* pHitPos,     //Hit 위치 ( NULL 이면 대입 안됨 )
		D3DXVECTOR3* pHitNormal	  //Hit 의 노말 ( NULL 이면 대입 안됨 )
		);

	bool IsPointSphere(cTransform* pTransA, float radiusA, cTransform* pTransB);
	bool IsPointSphere(cTransform* pTransA, float radiusA, D3DXVECTOR3 centerB);

	bool IsOverlap( cBaseObject* pObjA, cBaseObject* pObjB );
	
	//2개의 바운드 대한 출동 정보를 얻는다.
	bool IsOverlap( cTransform* pTransA, cBoundSphere* pBoundA, cTransform* pTransB, cBoundSphere* pBoundB );
	bool IsOverlap( cTransform* pTransA, cBoundBox* pBoundA, cTransform* pTransB, cBoundBox* pBoundB );
	
	bool IsOverlap( cTransform* pTransA, cBoundSphere* pBoundA, cTransform* pTransB, cBoundBox* pBoundB );
	bool IsOverlap( cTransform* pTransA, cBoundBox* pBoundA, cTransform* pTransB, cBoundSphere* pBoundB );


	bool IsBlocking( cBaseObject* pObjA, cBaseObject* pObjB, float moveFactor = 0.0f );

	//2개의 바운드 스피어에대한 출동하고 겹치지 않게 한다.
	//moveFactor 가 0 일수록 겹칩에 대해 B 가 움직인다.
	//moveFactor 가 0.5 이면 겹칩에 대해 A 와 B 가 똑같은량으로 움직인다.
	//moveFactor 가 1 일수록 겹칩에 대해 A 가 움직인다.
	bool IsBlocking( 
		cTransform* pTransA, cBoundSphere* pBoundA, 
		cTransform* pTransB, cBoundSphere* pBoundB ,
		float moveFactor = 0.0f );
	

	bool IsBlocking( 
		cTransform* pTransA, cBoundBox* pBoundA, 
		cTransform* pTransB, cBoundBox* pBoundB ,
		float moveFactor = 0.0f );



	//점 3개로 무한 평면을 만든다.
	void CreatePlane( LPD3DXPLANE	pOutPlane, const D3DXVECTOR3* p0, const D3DXVECTOR3* p1, const D3DXVECTOR3* p2 );

	//임의의 한점에서 평면까지의 최단거리
	float PlaneDot( const LPD3DXPLANE pPlane,  const D3DXVECTOR3* point );

	//반직선과 평면의 충돌 위치
	bool IntersectRayToPlane( D3DXVECTOR3* pOut, const LPRay pRay, const LPD3DXPLANE pPlane, bool bCheck2Side = false );

	//부채꼴범위와 대상의 충돌위치. Trans1이 중심이고 Trans2가 체크할 타겟이다.
	bool intersectSector(const cTransform* Trans1, const cTransform* Trans2, float length, float sight);

	D3DXVECTOR3 getLastHeight(cBaseObject* enumy, Ray* ray, cTerrain* terrain,D3DXVECTOR3* outPos);

	
};


#define PHYSICS_MGR cPhysicManager::GetInstance()


