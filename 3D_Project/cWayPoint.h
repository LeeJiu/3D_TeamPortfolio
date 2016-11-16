#pragma once

class cTransform;
class cTerrain;

class cWayPoint
{
private:
	int			m_nIndex;
	int			m_nPointNum;
	bool		m_bStart;
	bool		m_bEnd;

	Ray					m_ray;

	D3DXVECTOR3			m_prePos;
	D3DXVECTOR3			m_currentPos;


	vector<D3DXVECTOR3>				m_vWayPoint;
	vector<D3DXVECTOR3>::iterator	m_viWayPoint;

	cTerrain*						m_pTerrain;
	
	//오브젝트 체크를 위한 변수
	Ray								m_objCheckRay;
	std::vector<cBaseObject*>		m_vObjects;
	cBaseObject*					m_pTarget;
	float				m_fNearest;
	bool				m_bHit;

public:
	cWayPoint(cTerrain*	pTerrain);
	~cWayPoint();

	void Init(cTransform* trans, float fRadius);
	void Update(cTransform* trans);

	bool HitObjects(cTransform* trans);

	void SetBoundObjects(vector<cBaseObject*> vObjects) { m_vObjects = vObjects; }
};

