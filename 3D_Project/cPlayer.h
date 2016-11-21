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

	ACTOR_STATE			m_state;				//����
	std::string			m_strName;				//�ִϸ��̼� string
	std::map<int, bool> m_InputKeys;			//moveŰ ��

	moveClass*			m_pMove;				//����Ŭ����
	cCamera*			m_camera;				//ī�޶�
	cInven*				m_inven;				//�κ��丮
	cItem*				m_Weapon;				//����
	
	cMonster*			m_target;				//Ÿ�ٸ��� 
	cMonsterManager*	m_pMonMgr;				//���͸Ŵ���

	float				m_Angle;				//ī�޶�� �ޱ�
	float				m_Distance;				//ī�޶���� �Ÿ�
	float				MaxZoomIn;
	float				MaxZoomOut;
	float				Zoom;
	//status
	float				m_fHP;					//hp
	float				m_sp;					//skill point
	float				m_attackLength;			//���ݰ��ɹ���
	int					m_damage;				//������

	bool				m_isMove;				//�����̴���?
	bool				m_isAttack;				//�����ϴ���?
	bool				m_invenOn;				//�κ�����?

	bool                m_WeaponCheck;          // ������ ���� �����.
	bool                m_botton;

public:
	cPlayer();
	virtual ~cPlayer();

	virtual void BaseObjectEnable();							//init
	virtual void BaseObjectUpdate(float timeDelta);				//BaseObject �� Update �� ����....
	virtual void BaseObjectRender();							//���� ������Ʈ����
	virtual void BaseSpriteRender();							//��������Ʈ ����

	virtual void CamControl(float timeDelta);
	
	virtual void UiUpdate(float timeDelta, cCamera* camera);	//ui������Ʈ ����
	virtual void UiURender();									//ui��������

	virtual void Move(float timeDelta);							//���������Ʈ
	virtual void Monster_pick();								//Ÿ�ٸ��� ����

	//====���������Լ�======
	virtual void Attack01() = 0;								//�⺻����1
	virtual void Attack02() = 0;								//�⺻����2
	virtual void Attack03() = 0;								//�⺻����3
																
	virtual void SKILL01() = 0;									//��ų1
	virtual void SKILL02() = 0;									//��ų2
	virtual void SKILL03() = 0;									//��ų3
	virtual void SKILL04() = 0;									//��ų4
	
	virtual void Damage(float damage) = 0;						//����������
	//=====================
	
	virtual bool LengthCheck();									//Ÿ�ٵ� ���Ͷ� �Ÿ�
	virtual void RangeCheck(float range);						//����üũ

	virtual void SetBassClass();								//�⺻ Ŭ����
	
	virtual void SetCamera(cCamera* camera) { m_camera = camera; }
	virtual void SetMonsterManager(cMonsterManager* pMonMgr) { m_pMonMgr = pMonMgr; }
};

