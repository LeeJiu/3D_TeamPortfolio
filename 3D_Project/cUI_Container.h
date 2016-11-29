#pragma once
#include "cUI_Map.h"
#include "cUI_CharacterBar.h"
#include "cUI_SkillDeck.h"
#include "cUI_MenuBar.h"

class cUI_Container
{
	//팝업형 UI들을 관리하는 최종 UI컨테이너

	cUI_MenuBar*      m_MenuBar;
	cUI_Map*          m_Map;
	cUI_CharacterBar* m_CharacterBar;
	cUI_SkillDeck*    m_SkillDeck;

public:
	cUI_Container();
	~cUI_Container();

	void UI_Init();
	void UI_Update();
	void UI_Render();
	void UI_Release();
};

