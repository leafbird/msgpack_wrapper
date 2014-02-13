#pragma once

template <typename T>
void Delete(T*& ptr)
{
	delete ptr;
	ptr = nullptr;
}