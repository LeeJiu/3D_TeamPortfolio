#pragma once

class cTransform;
class cXMesh_Skinned;
class cBoundBox;

class cBaseskill
{
private:
	cTransform*		m_trans;
	cXMesh_Skinned*	m_Skinned;
	cBoundBox*		m_bound;

public:
	cBaseskill();
	~cBaseskill();
};

