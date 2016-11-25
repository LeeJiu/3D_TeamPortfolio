#include "stdafx.h"
#include "cUI_MenuBar.h"


cUI_MenuBar::cUI_MenuBar()
{
}


cUI_MenuBar::~cUI_MenuBar()
{
}


void cUI_MenuBar::init()
{



	for (int i = 0; i < MENUBARNUM; i++)
	{

		m_menuBtn[i].x = 20 + 51 * i;
		m_menuBtn[i].y = 10;
		m_menuBtn[i].rc = RectMake(0, 0, 32, 32);
		m_menuBtn[i].rcColl = RectMake(m_menuBtn[i].x, m_menuBtn[i].y, 32, 32);
		m_menuBtn[i].isClick = false;
	}

	m_menuBtn[0].img = RESOURCE_TEXTURE->GetResource("../Resources/UI/UI_up_Option.tga");
	m_menuBtn[1].img = RESOURCE_TEXTURE->GetResource("../Resources/UI/UI_Up_playerInfo.tga");
	m_menuBtn[2].img = RESOURCE_TEXTURE->GetResource("../Resources/UI/UI_Up_SkillInfo.tga");
	m_menuBtn[3].img = RESOURCE_TEXTURE->GetResource("../Resources/UI/UI_Up_Inven.tga");
	m_menuBtn[4].img = RESOURCE_TEXTURE->GetResource("../Resources/UI/UI_Up_Map.tga");


}

void cUI_MenuBar::update()
{
	for (int i = 0; i < MENUBARNUM; i++)
	{
		POINT ptMousePos = GetMousePos();
		D3DXVECTOR2 screenPos(ptMousePos.x, ptMousePos.y);

		if (PtInRect(&m_menuBtn[i].rcColl, ptMousePos))
		{
			if (KEY_MGR->IsOnceDown(VK_LBUTTON))
			{
				if (m_menuBtn[i].isClick) m_menuBtn[i].isClick = false;
				else m_menuBtn[i].isClick = true;
			}

			
		}

		

	}
}

void cUI_MenuBar::uiRender()
{
	for (int i = 0; i < MENUBARNUM; i++)
	{
		SPRITE_MGR->DrawTexture(
			m_menuBtn[i].img,
			&m_menuBtn[i].rc,
			m_menuBtn[i].x, m_menuBtn[i].y,
			0xffffffff,
			NULL);
	}
}