#pragma once
template<typename T>
class singletonBase
{
public:
	static void Create()
	{
		if (!instance) instance = new T();
	}

	static void Delete()
	{

		if (instance)
		{
			delete instance;
			instance = nullptr;
		}
	}

	static T* Get()
	{
		return instance;
	}

protected:
	static T* instance;
};

template<typename T> T* singletonBase<T>::instance = nullptr;