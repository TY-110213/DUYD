#pragma once
#include "status.h"


class GlobalStatus 
{
public:
	static status& Get() {
		static status instance;
		return instance;
	}
	static void Reset() {
		Get() = status();
	}
private:
	GlobalStatus() = delete;
};

