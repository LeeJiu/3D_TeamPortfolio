#pragma once
#include "cBaseObject.h"
#include "moveClass.h"
#include "cInven.h"
#include "cUI_Container.h"

class cTerrain;
class cCamera;
class cMonsterManager;
class cItem;
class cMonster;
class cTrailRender;


class cPlayer : public cBaseObject 
{
protected:

	cUI_Container*  m_UIContainer;

	vector<cMonster*>				m_vMonster;
	vector<cMonster*>::iterator		m_viMonster;

	vector<cBaseObject*>				m_vObject;
	vector<cBaseObject*>					m_vBound;

	ACTOR_STATE			m_state;				//����
	std::string			m_strName;				//�ִϸ��̼� string
	std::map<int, bool> m_InputKeys;			//moveŰ ��

	moveClass*			m_pMove;				//����Ŭ����
	cCamera*			m_camera;				//ī�޶�
	cInven*				m_inven;				//�κ��丮
	cItem*				m_Weapon;				//����
	
	cMonster*			m_target;				//Ÿ�ٸ��� 
	cMonsterManager*	m_pMonMgr;				//���͸Ŵ���

	cTrailRender*		pTrailRender;			//Ʈ���Ϸ���

	float				m_fHP;					//hp
	float				m_currentHp;
	float				m_fSP;
	float				m_currentSp;
	float				m_attackLength;			//���ݰ��ɹ���
	float				m_TextTime;

	int					m_damage;				//������

	float				m_Angle;

	bool				m_isIdle;
	bool				m_isMove;				//�����̴���?
	bool				m_isAttack;				//�����ϴ���?
	bool				m_invenOn;				//�κ�����?
	bool				m_textOn;				//�ؽ�Ʈ ����?
	bool				m_isAutoWalk;			//�ڵ��̵�
	
	bool                m_WeaponCheck;          // ������ ���� �����.
	bool                m_botton;

public:
	cPlayer();
	virtual ~cPlayer();

	virtual void BaseObjectEnable();							//init
	virtual void BaseObjectUpdate(float timeDelta);				//BaseObject �� Update �� ����....
	virtual void BaseObjectRender();							//���� ������Ʈ����
	virtual void BaseSpriteRender();							//��������Ʈ ����
	virtual void BaseFontRender();	
	virtual void BaseObjectBoundBox();

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
	virtual void RangeCheck(float range);						//���� �߽����� ����üũ
	virtual void RangeCircleCheck(D3DXVECTOR3& pos, float range);		//pos�� �߽����� ����üũ
	//virtual void RangeQuardCheck(D3DXVECTOR3& pos, float width, float height);		//pos�� �߽����� ����üũ
	
	virtual void SkillInit();

	virtual void SetBassClass();								//�⺻ Ŭ����

	virtual void SetCamera(cCamera* camera) { m_camera = camera; }
	virtual void SetMonsterManager(cMonsterManager* pMonMgr) { m_pMonMgr = pMonMgr; }
	virtual void SetObjects(std::vector<cBaseObject*> vObj) { m_vObject = vObj; }
	virtual void SetBounds(std::vector<cBaseObject*> vBox) { m_vBound = vBox; }

	cTransform* getTrans(){ return pTransform; }
	moveClass* getMoveClass(){ return m_pMove; }
};

