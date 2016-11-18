#pragma once

class cTransform;
class cXMesh_Skinned;
class cBoundBox;

class cBaseskill
{
private:
	cTransform*		m_trans;		//Ʈ����
	cXMesh_Skinned*	m_Skinned;		//��Ų��
	cBoundBox*		m_bound;		//�ٿ��

	float			m_timeDelta;	//�����ð�
	float			m_totalTime;	//��Ż�ð�
	bool			isCasting;		//��������

public:
	cBaseskill();
	~cBaseskill();

	virtual void Init();
	virtual void Release();
	virtual void Update(float timeDelta);
	virtual void Render();

	virtual void Execute();
};

