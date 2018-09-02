#pragma once

#include "..\stdh.h"

template <typename T>
class CSingletonBase
{
protected:
	CSingletonBase(void) {}
	virtual ~CSingletonBase(void)
	{
	}

public:
	static T* getSingleton(void)
	{
		if (m_pInstance == NULL)
			m_pInstance = new T;
		return m_pInstance;
	}

	static void destroy(void)
	{
		if (m_pInstance == NULL)
			return;

		delete m_pInstance;
		m_pInstance = NULL;
	}

	static bool isCreated()
	{
		return (m_pInstance != NULL);
	}

private:
	static T* m_pInstance;
};

template <class T> T* CSingletonBase<T>::m_pInstance = NULL;

