#pragma once

#include "csingletonbase.h"
#include "cBaseObject.h"
#include "cItem.h"
#include <map>
#include <string>

class cItemManager : public cSingletonBase<cItemManager>
{

public:
	std::map<int, cItem> itemList;

	cItemManager();
	~cItemManager();

	void init();
	void update();
	void render();
};

#define ITEM_MGR cItemManager::GetInstance()