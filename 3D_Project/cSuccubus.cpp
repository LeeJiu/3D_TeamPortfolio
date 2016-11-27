#include "stdafx.h"
#include "cSuccubus.h"
#include "cPlayer.h"


cSuccubus::cSuccubus()
{
}


cSuccubus::~cSuccubus()
{
}

void cSuccubus::BaseObjectEnable()
{
}

void cSuccubus::BaseObjectUpdate(float timeDelta)
{
}

void cSuccubus::BaseObjectBoundBox()
{
	BoundBox.SetBound(&D3DXVECTOR3(0, 1.0f, 0), &D3DXVECTOR3(0.5f, 1.0f, 0.5f));
}

void cSuccubus::BaseObjectRender()
{
	this->pSkinned->Render(this->pTransform);
	this->pTransform->RenderGimozo();
	this->BoundBox.RenderGizmo(this->pTransform);
}

void cSuccubus::Damage(float fDamage)
{
}