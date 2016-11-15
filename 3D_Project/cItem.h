#pragma once

#include "cBaseObject.h"
#include "cBaseObject.h"
#include <string>


class cItem : public cBaseObject
{
	string m_itemName;
	D3DXVECTOR3 m_basicScale;   // ��ȯ��ų ������
	D3DXQUATERNION m_basicRotation; // ���� ȸ����
	bool m_active;          // Ȱ��ȭ ����
	int m_row, m_coll;         // ��� 
	
	
	unsigned int m_itemNum; // ������ ���� ��ȣ .
	static unsigned int increaseNum; // ������ȣ ���

public:
	float m_lifeTime;       // ������ ���� �ð�. 

	void init(cItem* copyItem);
//void init(cItem copyItem);

	void createList(string name, int row, int coll);
	//cTransform* getTrans(){ return pTransform; }
	unsigned int getItemNum(){ return m_itemNum; }
	cItem();
	~cItem();
	
};

