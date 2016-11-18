#pragma once

class cTransform;
class cXMesh_Skinned;
class cBoundBox;

class cBaseskill
{
private:
	cTransform*		m_trans;		//트랜스
	cXMesh_Skinned*	m_Skinned;		//스킨드
	cBoundBox*		m_bound;		//바운드

	float			m_timeDelta;	//시전시간
	float			m_totalTime;	//토탈시간
	bool			isCasting;		//시전여부

public:
	cBaseskill();
	~cBaseskill();

	virtual void Init();
	virtual void Release();
	virtual void Update(float timeDelta);
	virtual void Render();

	virtual void Execute();
};

