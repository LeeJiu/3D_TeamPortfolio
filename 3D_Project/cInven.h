#pragma once

#include "cItem.h"
#include "cCamera.h"
#define INVEN_COUNT 6
#define RECT_SIZE 64
// 6 x 6 
struct stInven
{
	cItem* m_Item;                   
	unsigned int itemNum;                    // ������ ��ȣ ( ������ ��ȣ�� ��� ���)
	RECT rcSize;					// ��ų ��Ʈ �簢��
	RECT rcColl;                    // �浹 �� ��Ʈ
	LPDIRECT3DTEXTURE9 skillImage;	//�̹���
	float x, y;						//ȭ�鿡 �׷��� ��ǥ. 
	bool isPoint;                   //����Ʈ�� �ִ��� ������  
	//LPDIRECT3DTEXTURE9 emtyImage;
	int i, j;                        // �ε��� 
};

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
	void update(float timeDelta, cCamera* camera);
	void render();
	void release();
	D3DXVECTOR3 screenPos(int x,int y);

	bool inputItem(int row, int coll,cItem* item);
	void invenItemClick();
	void putItem();

	int findItemNum();    // ������ ��ȣ ã�°� .
	stInven* findInven(cItem* item);
	LPDIRECT3DTEXTURE9 findIcon(string name);

	bool selctRect(int* row, int* coll, POINT mouse);

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