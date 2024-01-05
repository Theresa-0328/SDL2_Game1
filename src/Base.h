#pragma once

class Base
{
public:
	Base();
	~Base();
	void setCanInput(bool isCanInput);
	bool getCanInput();
private:
	bool canInput{ true };
};