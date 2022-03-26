#pragma once
#include <list>

#include "Gun.h"

struct BaseInventory
{
	std::list<UGun*> OwnedGuns;

	UGun* GetNextGun(UGun* current)
	{
		UGun* FoundGun;
		std::find(OwnedGuns.front(), OwnedGuns.back(), FoundGun);
		
	}
};
