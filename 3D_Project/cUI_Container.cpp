#include "stdafx.h"
#include "cUI_Container.h"


cUI_Container::cUI_Container()
{
}


cUI_Container::~cUI_Container()
{
}

void cUI_Container::UI_Init(float maxHp, float maxSp, CHARAC_TYPE cType)
{


	m_Map = new cUI_Map;
	m_Map->init();

	m_CharacterBar = new cUI_CharacterBar;
	m_CharacterBar->init(maxHp, maxSp);

	m_SkillDeck = new cUI_SkillDeck;
	m_SkillDeck->init(cType);

	m_MenuBar = new cUI_MenuBar;
	m_MenuBar->init();

}

void cUI_Container::UI_Release()
{
	SAFE_DELETE(m_Map);
	SAFE_DELETE(m_CharacterBar);
	SAFE_DELETE(m_SkillDeck);
	SAFE_DELETE(m_MenuBar);

}

void cUI_Container::UI_Update(float m_currentHp, float m_currentSp, D3DXVECTOR3 pos)
{
	m_Map->update(pos);
	m_CharacterBar->update(m_currentHp, m_currentSp);
	m_SkillDeck->update();
	m_MenuBar->update();

}


void cUI_Container::UI_Render()
{
	
	m_CharacterBar->uiRender();
	m_SkillDeck->uiRender();

	if (m_MenuBar->GetIsMapClick() || m_Map->GetIsMapOn())
	{
		m_Map->uiRender();
	}
	
	m_Map->MiniMapRender();

	m_MenuBar->uiRender();

	
}

void cUI_Container::UI_fontRender()
{
	m_CharacterBar->fontRender();
}
