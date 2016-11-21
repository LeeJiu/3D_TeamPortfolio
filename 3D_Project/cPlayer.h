#pragma once
#include "cBaseObject.h"
#include "moveClass.h"
#include "cInven.h"

class cTerrain;
class cCamera;
class cMonsterManager;
class cItem;
class cMonster;

class cPlayer : public cBaseObject 
{
protected:
	vector<cMonster*>				m_vMonster;
	vector<cMonster*>::iterator		m_viMonster;

	ACTOR_STATE			m_state;				//상태
	std::string			m_strName;				//애니메이션 string
	std::map<int, bool> m_InputKeys;			//move키 맵

	moveClass*			m_pMove;				//무브클래스
	cCamera*			m_camera;				//카메라
	cInven*				m_inven;				//인벤토리
	cItem*				m_Weapon;				//무기
	
	cMonster*			m_target;				//타겟몬스터 
	cMonsterManager*	m_pMonMgr;				//몬스터매니저

	float				m_Angle;				//카메라랑 앵글
	float				m_Distance;				//카메라와의 거리
	float				MaxZoomIn;
	float				MaxZoomOut;
	float				Zoom;
	//status
	float				m_fHP;					//hp
	float				m_sp;					//skill point
	float				m_attackLength;			//공격가능범위
	int					m_damage;				//데미지

	bool				m_isMove;				//움직이는중?
	bool				m_isAttack;				//공격하는중?
	bool				m_invenOn;				//인벤켜진?

	bool                m_WeaponCheck;          // 아이템 장착 됬는지.
	bool                m_botton;

public:
	cPlayer();
	virtual ~cPlayer();

	virtual void BaseObjectEnable();							//init
	virtual void BaseObjectUpdate(float timeDelta);				//BaseObject 가 Update 때 실행....
	virtual void BaseObjectRender();							//기존 오브젝트랜더
	virtual void BaseSpriteRender();							//스프라이트 랜더

	virtual void CamControl(float timeDelta);
	
	virtual void UiUpdate(float timeDelta, cCamera* camera);	//ui업데이트 전반
	virtual void UiURender();									//ui랜더전반

	virtual void Move(float timeDelta);							//무브업데이트
	virtual void Monster_pick();								//타겟몬스터 집음

	//====순수가상함수======
	virtual void Attack01() = 0;								//기본공격1
	virtual void Attack02() = 0;								//기본공격2
	virtual void Attack03() = 0;								//기본공격3
																
	virtual void SKILL01() = 0;									//스킬1
	virtual void SKILL02() = 0;									//스킬2
	virtual void SKILL03() = 0;									//스킬3
	virtual void SKILL04() = 0;									//스킬4
	
	virtual void Damage(float damage) = 0;						//데미지입음
	//=====================
	
	virtual bool LengthCheck();									//타겟된 몬스터랑 거리
	virtual void RangeCheck(float range);						//범위체크

	virtual void SetBassClass();								//기본 클래스
	
	virtual void SetCamera(cCamera* camera) { m_camera = camera; }
	virtual void SetMonsterManager(cMonsterManager* pMonMgr) { m_pMonMgr = pMonMgr; }
};

