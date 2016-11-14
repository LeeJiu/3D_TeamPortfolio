#pragma once

#include "csingletonbase.h"
#include "cBaseObject.h"
#include "cItem.h"
#include <map>
#include <string>
#include <vector>
class cItemManager : public cSingletonBase<cItemManager>
{

public:
	std::map<int, cItem*> m_itemList;
	std::vector<cItem*> v_item;
	cItemManager();
	~cItemManager();

	void init();
	void update();
	void render();
	void createItemList(); // ������ ��� ����� �Լ�. 
};

#define ITEM_MGR cItemManager::GetInstance()