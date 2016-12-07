#include "stdafx.h"
#include "cUI_Map.h"


cUI_Map::cUI_Map()
{
}


cUI_Map::~cUI_Map()
{
}


void cUI_Map::init()
{
	m_Map.x = WINSIZE_X / 3;
	m_Map.y = WINSIZE_Y / 6;
	m_Map.MapImg = RESOURCE_TEXTURE->GetResource("../Resources/UI/UI_Map.tga");
	m_Map.rc = RectMake(0, 0, 512, 512);

	m_IsMapOn = false;

	m_MiniMap.x = WINSIZE_X - 266;
	m_MiniMap.y = 10;
	m_MiniMap.MapImg = RESOURCE_TEXTURE->GetResource("../Resources/UI/UI_MiniMap.tga");
	m_MiniMap.rc = RectMake(0, 0, 256, 256);


	m_PlayerTex = RESOURCE_TEXTURE->GetResource("../Resources/UI/UI_PlayerPosition.bmp");
	m_rcPlayer = RectMake(0, 0, 2, 2);
}


void cUI_Map::update(D3DXVECTOR3 pos)
{
	m_PlayerPos = pos;
	m_PlayerPos.x *= 0.5f;
	m_PlayerPos.z *= -0.4375f;

	m_PlayerPos.x += 127;
	m_PlayerPos.z += 111.125f;

	if (KEY_MGR->IsOnceDown('M'))
	{
		if (m_IsMapOn) m_IsMapOn = false;
		else m_IsMapOn = true;
	}



}


void cUI_Map::uiRender()
{
	SPRITE_MGR->DrawTexture(
		m_Map.MapImg,
		&m_Map.rc,
		m_Map.x, m_Map.y,
		0xffffffff,
		NULL);


}

void cUI_Map::MiniMapRender()
{

	SPRITE_MGR->DrawTexture(
		m_MiniMap.MapImg,
		&m_MiniMap.rc,
		m_MiniMap.x, m_MiniMap.y,
		0xffffffff,
		NULL);

	SPRITE_MGR->DrawTexture(
		m_PlayerTex,
		&m_rcPlayer,
		m_MiniMap.x + m_PlayerPos.x,
		m_MiniMap.y + m_PlayerPos.z + 14,
		0xffffffff,
		NULL);

}