#pragma once
#include "status.h"
#include "../Library/GameObject.h"

class GlobalStatus : public GameObject
{
public:
	static status& Get() {
		static status instance;
		return instance;
	}
private:
	GlobalStatus() = delete;
};

