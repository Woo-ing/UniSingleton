#pragma execution_character_set("utf-8")

#include "UniSingleton.h"

// static instance of manager
CSingletonMgr CSingletonMgr::ms_instance;

// Clear all singleton instances
void CSingletonMgr::clear()
{
	for (; !m_mapInstances.empty();)
	{
		auto iter = m_mapInstances.begin();
		//TRACE("destroy singleton: %s\n", iter->first);
		CSingletonMgr::PBase* pObj = iter->second;
		m_mapInstances.erase(iter);
		delete pObj;
	}
}

// Remove the instance of _class
// @param lpszType: Specifies the type name of singleton you want to remove
// @param del: If true, delete the instance of singleton
// @return: If the instance is successfully deleted, return ture, otherwise it returns false
bool CSingletonMgr::remove(const char* lpszType, bool del)
{
	std::map<const char*, CSingletonMgr::PBase*>::iterator iter = m_mapInstances.find(lpszType);
	if (iter != m_mapInstances.end())
	{
		//TRACE("destroy singleton: %s\n", iter->first);
		CSingletonMgr::PBase* pObj = iter->second;
		m_mapInstances.erase(iter);
		if (del)
			delete pObj;
		return true;
	}
	return false;
}