#include "stdafx.h"
#include "cPlayer.h"
#include "cTerrain.h"
#include "cCamera.h"
#include "cInputHandler.h"


cPlayer::cPlayer()
{

}


cPlayer::~cPlayer()
{
}

void cPlayer::BaseObjectEnable()
{
	//ĳ������ �׷��� ��ġ�� ����
	pTransform->SetWorldPosition(0, pTerrain->GetHeight(0, 0), 0);
}

void cPlayer::BaseObjectUpdate(float timeDelta)
{
	
}

void cPlayer::BaseObjectRender()
{
	this->pSkinned->Render(this->pTransform);
}