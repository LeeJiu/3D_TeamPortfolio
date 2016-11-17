#pragma once
#include "cPlayer.h"
#include "moveClass.h"

#define CONTROL_KEY 5

class cBerserker : public cPlayer
{
private:
	ACTOR_STATE			m_state;
	std::string			m_strName;
	std::map<int, bool> m_InputKeys;
	bool				m_isMove;

	//������Ʈ�� �޾��ش�.
	moveClass*			m_pMove;
	D3DXVECTOR3			m_mousePos;

	//��ų
	bool				m_isAttack;

	int					m_atkCnt;		//��Ÿ�ܰ� ��
	float				m_time;			//Ŀ�ǵ�üũ�� Ÿ�̸�
	float				m_fadeOut;		//�ִ� �����½ð�


	//status
	float				m_fHP;
	float				m_sp;
	float				m_attackLength;//���ݰ��ɹ���
	int					m_damage;

	float				m_testtime;		//�αש��¿� Ÿ�̸�

public:
	cBerserker();
	~cBerserker();

	void BaseObjectEnable();
	void BaseObjectUpdate(float timeDelta);			//BaseObject �� Update �� ����....
	void BaseObjectRender();

	//void SetMonsters(std::vector<cMonster*>	vmon) { m_Vmon = vmon; }

private:
	void Damage(float damage);
	bool LengthCheck();

	void Attack01();
	void Attack02();
	void Attack03();
};

