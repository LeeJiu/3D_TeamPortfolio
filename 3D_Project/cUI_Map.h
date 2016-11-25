#pragma once

struct UI_map
{
	RECT rc;
	LPDIRECT3DTEXTURE9 MapImg;
	float x, y;

};


class cUI_Map
{
	UI_map m_Map;
	bool   m_IsMapOn;

	UI_map m_MiniMap;

public:
	cUI_Map();
	~cUI_Map();

	void init();
	void update();
	void uiRender();
	void MiniMapRender();

	UI_map GetUIMAP() { return m_Map; }
	bool   GetIsMapOn(){ return m_IsMapOn; }
};

