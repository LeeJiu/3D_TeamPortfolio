#pragma once

#include "cBaseObject.h"
#include "cBaseObject.h"
#include <string>


class cItem : public cBaseObject
{
	static unsigned int increaseNum; // ������ȣ ���
	string m_itemName;
	D3DXVECTOR3 m_basicScale;   // ��ȯ��ų ������
	D3DXQUATERNION m_basicRotation; // ���� ȸ����
	float m_lifeTime;       // ������ ���� �ð�. 
	bool m_active;          // Ȱ��ȭ ����
	int m_row, m_coll;         // ��� 
	unsigned int m_itemNum; // ������ ���� ��ȣ .

public:
	void init(cItem* copyItem);
	void init(cItem copyItem);

	void createList(string name, int row, int coll);
	//cTransform* getTrans(){ return pTransform; }
	unsigned int getItemNum(){ return m_itemNum; }
	cItem();
	~cItem();
};

