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

	vector<D3DXVECTOR3>				m_vWayPoint;
	vector<D3DXVECTOR3>::iterator	m_viWayPoint;

	cTerrain*	m_pTerrain;

public:
	cWayPoint(cTerrain*	pTerrain);
	~cWayPoint();

	void Init(cTransform* trans, float fRadius);
	void Update(cTransform* trans);
};

