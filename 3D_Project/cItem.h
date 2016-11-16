#pragma once

#include "cBaseObject.h"
#include <string>


class cItem
{
	static unsigned int increaseNum; // ������ȣ ���

	string m_itemName;
	cBaseObject m_itemObj; // ������ ������Ʈ
	D3DXVECTOR3 m_scale;   // ���̿� ������
	D3DXVECTOR3 m_base_scale;   // ���� �����ϰ�.

	float m_lifeTime;       // ������ ���� �ð�. 
	bool m_active;          // Ȱ��ȭ ����
	int m_row,m_coll;         // ��� 
	unsigned int m_itemNum; // ������ ���� ��ȣ .

public:
	void init();
	void createList(string name,cBaseObject item,D3DXVECTOR3 scale
		,int row,int coll );

	cItem();
	~cItem();
};

