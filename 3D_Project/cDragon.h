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
	cBoundBox m_bound[COLLISION];       //뼈에 들어갈 바운스
	cTransform* m_pBoneTrans[COLLISION]; //뼈에 들어갈 트렌스

	D3DXVECTOR3 m_collPos[8];
	cTransform* m_pCollTrans[5];           //충돌체크에 쓸 트렌스

	stSphere m_spone;                     // 스폰에 쓰일 꺼. 
	stSphere m_basicAttack;               // 평타 사정 거리

	string m_nowAni;                      // 애니메이션
	
	
	bool isMove;                          // 움직이는중?
	bool isBattle;                        // 전투중?
	bool isBasicAttack;                   // 평타중?
	
	bool isBreath;                        // 브레스중?
	bool isEarthquake;                    // 지진중?
	bool isHeadAtt;                       // 머리 치기
	
	bool isNoneBasicAttack;               // 평타이외의 스킬.( 쓸지 안쓸지 모르겠음 )
	int skillChance;                      // 스킬 발동확률

	float skillCoolTime;                 // 스킬 쿨타임
	float tempCoolTime;                  // 스킬 쿨타이밍에 계산 할 거
public:
	cDragon();
	~cDragon();
	
	void BaseObjectEnable();					//SetActive(true)하면 실행됨 -> 초기화 함수
	void BaseObjectUpdate(float timeDelta);		//BaseObject 가 Update 때 실행....
	void BaseObjectBoundBox();					//SetMesh() 하면 ComputeBoundBox() 실행되면서 실행됨
	void BaseObjectRender();
	
	//==========이곳에 함수 추가==========
	void Damage(float fDamage);		//cMonster로 부를 수 있는 순수 가상 함수 / 반드시 override
	void MoveToPlayer();
	
	//========= collTrans 값 갱신 =======
	void collPosUpdate();
	//========= update 로직에 들어갈 함수 =====
	bool battleRange();
	bool basicRange();
	//========= 처음 몬스터 만났을때 쓸 함수 ====
	void spawn();
	// 스킬 업데이트 함수  
	void basicAttackUpdate();
	void breathUpdate();
	void earthUpate();
	void HeadAttUpate();
	// 상태값 초기화.
	void stateInit();
	// 몬스터 회전 시키게 하는 함수
	void LookPos(D3DXVECTOR3 target);
	// 애니메이션 관리 해주는 함수
	void aniManager();
	//플레이어 링크
	void SetPlayer(cPlayer* pPlayer) { m_pPlayer = pPlayer; }


};

