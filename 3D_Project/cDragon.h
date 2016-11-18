#pragma once
#include "cMonster.h"


class cDragon : public cMonster
{
private:
	


public:
	cDragon();
	~cDragon();

	void BaseObjectEnable();					//SetActive(true)하면 실행됨 -> 초기화 함수
	void BaseObjectUpdate(float timeDelta);		//BaseObject 가 Update 때 실행....
	void BaseObjectBoundBox();					//SetMesh() 하면 ComputeBoundBox() 실행되면서 실행됨

	
	//==========이곳에 함수 추가==========
	void Damage(float fDamage);		//cMonster로 부를 수 있는 순수 가상 함수 / 반드시 override



	//플레이어 링크
	void SetPlayer(cPlayer* pPlayer) { m_pPlayer = pPlayer; }
};

