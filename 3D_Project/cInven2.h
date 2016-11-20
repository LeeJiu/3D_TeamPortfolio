#pragma once

#include "cItem.h"
#include "cCamera.h"
#include "cInven.h"
#define INVEN_COUNT 6
#define RECT_SIZE 64
// 6 x 6 


class cInven2 
{
	bool invenOpen; // 인벤이 열렸을때
	bool pickUp;   // 아이템을 들었을 때

	std::vector<cItem*>::iterator item_iter; //아이템 인덱스
	int itemIndex;
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
	void release();

	cItem*	GetWeapon() { return weapon.m_Item; }

	bool GetInvenOn() { return invenOpen; }

	D3DXVECTOR3 screenPos(int x, int y);


	LPDIRECT3DTEXTURE9 findIcon(string name);

	bool invenInputItem(int* row, int* coll, cItem* item,POINT mouse);
	bool invenSelectRect(int* row, int* coll, POINT mouse);
	
	bool weaponSelectRect(POINT mouse);
	bool weaponInputItem(cItem* item, POINT mouse);
	
	bool invenToManager(int* row, int* coll, POINT mouse);
	bool weaponToManager(POINT mouse);

	void discard(int* row, int* coll, POINT mouse);
	cInven2();
	~cInven2();
};

/*
cItem* temp;
temp = weapon.m_Item;
weapon.m_Item = clickItem;
clickItem = temp;

ITEM_MGR->v_item[itemIndex] = temp;
*/