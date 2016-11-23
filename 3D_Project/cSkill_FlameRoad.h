#pragma once
#include "cSkill_Front.h"

class cSkill_FlameRoad : public cSkill_Front
{
	cQuadParticleEmitter*  m_flameRoad;
	cQuadParticleEmitter*  m_flameRoad2;
	cPartcleEmitter*       m_flameRoad3;



public:
	cSkill_FlameRoad();
	~cSkill_FlameRoad();

	void Effect_Init();
	void Effect_Update(float timeDelta);
	void Effect_Render();


};

