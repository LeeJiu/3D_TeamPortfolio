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

	m_MiniMap.x= WINSIZE_X - 220;
	m_MiniMap.y = 10;
	m_MiniMap.MapImg = RESOURCE_TEXTURE->GetResource("../Resources/UI/UI_MiniMap.tga");
	m_MiniMap.rc = RectMake(0, 0, 256, 256);

}


void cUI_Map::update()
{

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

}