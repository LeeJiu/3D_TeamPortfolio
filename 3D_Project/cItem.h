#pragma once

#include "cBaseObject.h"
#include "cBaseObject.h"
#include <string>

static unsigned int increaseNum; // ������ȣ ���

class cItem : public cBaseObject
{
	static unsigned int increaseNum; // ������ȣ ���


	string m_itemName;
	D3DXVECTOR3 m_basicScale;   // ��ȯ��ų ������
	D3DXQUATERNION m_basicRotation; // ���� ȸ����
	bool m_active;          // Ȱ��ȭ ����
	int m_row, m_coll;         // ��� 
	
	
	unsigned int m_itemNum; // ������ ���� ��ȣ .
	int m_Dmg;				//����
	
public:
	
	float m_lifeTime;       // ������ ���� �ð�. 
	int getRow(){ return m_row; }
	int getColl(){ return m_coll; }

	void init(cItem* copyItem);
	void createList(string name, int row, int coll);
	//cTransform* getTrans(){ return pTransform; }
	unsigned int getItemNum(){ return m_itemNum; }
	D3DXQUATERNION getBasicRotaion(){ return m_basicRotation; }
	string getItemName(){ return m_itemName; }
	void setDmg(int dmg) { m_Dmg = dmg; }
	int getDmg() { return m_Dmg; }
	cItem();
	~cItem();
	
};

