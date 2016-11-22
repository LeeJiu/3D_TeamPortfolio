#pragma once

#include "cItem.h"
#include "cCamera.h"
#define INVEN_COUNT 6
#define RECT_SIZE 64
// 6 x 6 
 struct stInven
 {
 	cItem* m_Item;                  // ������ ������.
 	unsigned int itemNum;           // ������ ��ȣ ( ������ ��ȣ�� ��� ���)
 	RECT rcSize;					// ��ų ��Ʈ �簢��
 	RECT rcColl;                    // �浹 �� ��Ʈ
 	LPDIRECT3DTEXTURE9 skillImage;	// �̹���
 	float x, y;						// ȭ�鿡 �׷��� ��ǥ. 
 	bool isPoint;                   // ����Ʈ�� �ִ��� ������  
 	//LPDIRECT3DTEXTURE9 emtyImage;
 	int i, j;                        // �ε��� 
 };


 // 6 x 6 


 class cInven
 {
	 bool invenOpen; // �κ��� ��������
	 bool pickUp;   // �������� ����� ��

	 std::vector<cItem*>::iterator item_iter; //������ �ε���
	 int itemIndex;
	 int row;//�� 
	 int col;//��
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