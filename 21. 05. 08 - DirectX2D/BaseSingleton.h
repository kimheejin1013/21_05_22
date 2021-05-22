#pragma once

template <typename T>
class BaseSingleton
{
protected:
	static T* instance;

public:
	static T* Get();

	void Release();
};

template <typename T>
T* BaseSingleton<T>::instance = nullptr;

template <typename T>
T* BaseSingleton<T>::Get()
{
	if (!instance) instance = new T();
	return instance;
}

template <typename T>
void BaseSingleton<T>::Release()
{
	if (instance) {
		delete instance;
		instance = nullptr;
	}
}