#pragma once

/**
*
*/

template <typename T>
class TSingleton
{
public:
	virtual ~TSingleton()
	{
	}

	static T* GetInstance()
	{
		if (_instance == nullptr)
			_instance = new T();

		return _instance;
	}

	static void ReleaseInstance()
	{
		if (_instance != nullptr)
		{
			delete _instance;
			_instance = nullptr;
		}
	}

protected:
	static T* _instance;
};

template<typename T> T* TSingleton<T>::_instance = nullptr;