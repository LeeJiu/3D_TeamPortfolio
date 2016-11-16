#pragma once

#include "cItem.h"
#include "cCamera.h"
#define INVEN_COUNT 6
#define RECT_SIZE 64
// 6 x 6 
struct stInven
{
	cItem* m_Item;                   
	unsigned int itemNum;                    // 아이템 번호 ( 아이템 번호는 모두 양수)
	RECT rcSize;					// 스킬 렉트 사각형
	RECT rcColl;                    // 충돌 할 렉트
	LPDIRECT3DTEXTURE9 skillImage;	//이미지
	float x, y;						//화면에 그려질 좌표. 
	bool isPoint;                   //포인트가 있는지 없는지  
	//LPDIRECT3DTEXTURE9 emtyImage;
	int i, j;                        // 인덱스 
};

class cInven
{
	bool isActive;
	bool pickUp;
	int row;//행 
	int col;//열
	stInven inven[INVEN_COUNT][INVEN_COUNT];
	
	stInven weapon;

	stInven emptyInven;

	cItem* clickItem;
public:

	void init();
	void update(float timeDelta, cCamera* camera);
	void render();
	D3DXVECTOR3 screenPos(int x,int y);

	bool inputItem(int row, int coll,cItem* item);

	cInven();
	~cInven();
};

