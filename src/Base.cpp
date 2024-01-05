#include "Base.h"

Base::Base()
{
}

Base::~Base()
{
}

bool Base::getCanInput()
{
	return canInput;
}

void Base::setCanInput(bool isCanInput)
{
	canInput = isCanInput;
}