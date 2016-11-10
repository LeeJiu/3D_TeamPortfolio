#include "stdafx.h"
#include "cMonster.h"
#include "cWayPoint.h"
#include "cTransform.h"
#include "cTerrain.h"


cMonster::cMonster()
{
}


cMonster::~cMonster()
{
}

void cMonster::BaseObjectEnable()
{
	pTransform->SetWorldPosition(3, pTerrain->GetHeight(0, 0), 3);
	pSkinned->Play("Walk");

	m_pWayPoint = new cWayPoint(pTerrain);
	m_pWayPoint->Init(pTransform, 10.0f);

}

void cMonster::BaseObjectUpdate(float timeDelta)
{
	m_pWayPoint->Update(pTransform);
}