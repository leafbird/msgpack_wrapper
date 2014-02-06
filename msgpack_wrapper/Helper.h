#pragma once
class Helper
{
public:
	Helper();
	virtual ~Helper();

	Helper(const Helper&) = delete;
	void operator=(const Helper&) = delete;

private:
};

