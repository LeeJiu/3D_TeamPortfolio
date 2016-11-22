#pragma once
#include "cMonster.h"
#include "cBoundBox.h"

#define COLLISION 4
/*
   전투를 걸어야 전투가 시작됨.
   도망 치려면 전투 범위에서 벗어나야됨.
*/
struct stSphere
{
	D3DXVECTOR3 worldCenter;
	float radius;
};

class cDragon : public cMonster
{
private:
	int m_collCount;                    //포문 돌릴때 가져다 쓰셈
	cBoundBox m_Bound[COLLISION];       //뼈에 들어갈 바운스
	cTransform* m_boneTrans[COLLISION]; //뼈에 들어갈 트렌스

	D3DXVECTOR3 collPos[8];
	cTransform* collTrans[5];           //충돌체크에 쓸 트렌스

	stSphere spone;      // 스폰에 쓰일 꺼. 

public:
	cDragon();
	~cDragon();
	
	void BaseObjectEnable();					//SetActive(true)하면 실행됨 -> 초기화 함수
	void BaseObjectUpdate(float timeDelta);		//BaseObject 가 Update 때 실행....
	void BaseObjectBoundBox();					//SetMesh() 하면 ComputeBoundBox() 실행되면서 실행됨
	void BaseObjectRender();
	
	//==========이곳에 함수 추가==========
	void Damage(float fDamage);		//cMonster로 부를 수 있는 순수 가상 함수 / 반드시 override

	//========= collTrans 값 갱신 =======
	void collPosUpdate();
	bool battleRange();

	//플레이어 링크
	void SetPlayer(cPlayer* pPlayer) { m_pPlayer = pPlayer; }
};

