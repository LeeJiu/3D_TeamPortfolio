#pragma once

#include "cItem.h"
#include "cCamera.h"
#define INVEN_COUNT 6
#define RECT_SIZE 64
// 6 x 6 
 struct stInven
 {
 	cItem* m_Item;                  // 아이템 포인터.
 	unsigned int itemNum;           // 아이템 번호 ( 아이템 번호는 모두 양수)
 	RECT rcSize;					// 스킬 렉트 사각형
 	RECT rcColl;                    // 충돌 할 렉트
 	LPDIRECT3DTEXTURE9 skillImage;	// 이미지
 	float x, y;						// 화면에 그려질 좌표. 
 	bool isPoint;                   // 포인트가 있는지 없는지  
 	//LPDIRECT3DTEXTURE9 emtyImage;
 	int i, j;                        // 인덱스 
 };


 // 6 x 6 


 class cInven
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
	 void update(float timeDelta, cCamera* camera, D3DXVECTOR3& pos);
	 void render();
	 void release();

	 cItem*	GetWeapon() { return weapon.m_Item; }

	 bool GetInvenOn() { return invenOpen; }

	 D3DXVECTOR3 screenPos(int x, int y);


	 LPDIRECT3DTEXTURE9 findIcon(string name);

	 bool invenInputItem(int* row, int* coll, cItem* item, POINT mouse);
	 bool invenSelectRect(int* row, int* coll, POINT mouse);

	 bool weaponSelectRect(POINT mouse);
	 bool weaponInputItem(cItem* item, POINT mouse);

	 bool invenToManager(int* row, int* coll, POINT mouse);
	 bool weaponToManager(POINT mouse);

	 void discard(int* row, int* coll, POINT mouse, D3DXVECTOR3& pos);
	 cInven();
	 ~cInven();
 };

/*
cItem* temp;
temp = weapon.m_Item;
weapon.m_Item = clickItem;
clickItem = temp;

ITEM_MGR->v_item[itemIndex] = temp;
*/