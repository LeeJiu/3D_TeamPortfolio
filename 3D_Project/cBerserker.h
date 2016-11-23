#pragma once
#include "cPlayer.h"

#define CONTROL_KEY 5

class cBerserker : public cPlayer
{
private:
	//��ų
	int					m_atkCnt;		//��Ÿ�ܰ� ��
	float				m_time;			//Ŀ�ǵ�üũ�� Ÿ�̸�
	float				m_fadeOut;		//�ִ� �����½ð�

	//��ų3 
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

	void SKILL01();			//��Ÿ
	void SKILL02();			//�������	(Ÿ��, ������)
	void SKILL03();			//������ (���� ������)
	void SKILL04();			//������
};

