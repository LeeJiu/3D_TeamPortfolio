#pragma once
#include "cPlayer.h"
#include "cSkill_Swing.h"
#include "cSkill_Howling.h"
#include "cSkill_Burserk.h"
#include "cSkill_AmorCrash.h"
#include "cTickFunc.h"

#define CONTROL_KEY 5
#define BK_TICKMAX 3

enum BK_SKILL //ƽ Ŭ�������� ����. 
{
	BK_HOWL, BK_SWING, BK_ACCEL
};

class cViewDamage;
class cShowDamage;

class cBerserker : public cPlayer
{
private:
	//cViewDamage*        m_ViewDamage;
	cShowDamage*		m_ShowDamage;
	cSkill_Surround*    m_pSurroundSkill;	//�ֺ�����
	
	cTickFunc*			m_tick[BK_TICKMAX];	//ƽ������

	//��ų
	int					m_atkCnt;		//��Ÿ�ܰ� ��
	int					m_aniCount;		//�ִϸ��̼� ī����
	float				m_time;			//Ŀ�ǵ�üũ�� Ÿ�̸�
	float				m_fadeOut;		//�ִ� �����½ð�

	//��ų2
	cSkill_Howling*		m_Howling;		//�Ͽ︵

	//��ų3 
	cSkill_Swing*		m_Swing;		//������ų

	//��ų5
	cSkill_Burserk*		m_Burserk;		//����ũ���

	cSkill_AmorCrash*   m_ArmorCrash;

	int					m_SwingCnt;

	float				m_testtime;		//�αש��¿� Ÿ�̸�

public:
	cBerserker();
	~cBerserker();

	void BaseObjectEnable();
	void BaseObjectUpdate(float timeDelta);			//BaseObject �� Update �� ����....
	void BaseObjectRender();
	void BaseSpriteRender();
	void BaseObjectBoundBox();

private:
	void Damage(float damage);

	void Attack01();
	void Attack02();
	void Attack03();

	void SkillInit();

	void SKILL01();			//��Ÿ
	void SKILL02();			//�������	(Ÿ��, ������)
	void SKILL03();			//������ (���� ������)
	void SKILL04();			//������

	void BasixWeaponSet();
	void SetTickCount();
	void UiUpdate(float timeDelta, cCamera* camera);		//����Ŀ������
};

