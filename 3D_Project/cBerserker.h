#pragma once
#include "cPlayer.h"
#include "cSkill_Swing.h"

#define CONTROL_KEY 5

class cBerserker : public cPlayer
{
private:
	cSkill_Surround*    m_pSurroundSkill;	//�ֺ�����

	//��ų
	int					m_atkCnt;		//��Ÿ�ܰ� ��
	int					m_aniCount;		//�ִϸ��̼� ī����
	float				m_time;			//Ŀ�ǵ�üũ�� Ÿ�̸�
	float				m_fadeOut;		//�ִ� �����½ð�

	//��ų3 
	cSkill_Swing*		m_Swing;		//������ų
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
};

