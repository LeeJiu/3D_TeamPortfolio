#pragma once
#define SKILLNUM 5
struct stUi
{
	RECT rcSize;					// 스킬 렉트 사각형
	RECT rcColl;                    // 충돌 할 렉트
	LPDIRECT3DTEXTURE9 skillImage;	//이미지
	float x, y;						//화면에 그려질 좌표. 
	
	//LPDIRECT3DTEXTURE9 emtyImage;
};

class cSkillUi
{
	stUi skillBotton[SKILLNUM];
	
	stUi emtyBotton;


	//LPDIRECT3DTEXTURE9 emtyImage;


public:
	cSkillUi();
	~cSkillUi();
	
	void init();
	void update();

	void uiRender();

};

