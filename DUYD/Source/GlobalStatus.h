#pragma once
#include "status.h"


class GlobalStatus 
{
public:
	static status& Get() {
		static status instance;
		return instance;
	}
private:
	GlobalStatus() = delete;
};

