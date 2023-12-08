#pragma execution_character_set("utf-8")
#pragma once

#include <assert.h>
#include <map>
#include <typeinfo>

// Manager for singleton instances
class CSingletonMgr {

public:
    // Base class for singleton ptr container
	struct PBase{
		virtual ~PBase()
		{}
	};

    // Container for any singletons
	template <typename _class>
	struct P :public PBase{
		P(_class* p)
			:ptr(p)
		{}
		virtual ~P(){
			delete ptr;
		}

		void operator = (_class* p) {
			ptr = p;
		}

		operator _class*(){
			return ptr;
		}

		_class* ptr;
	};

public:
	CSingletonMgr(){}
	~CSingletonMgr()
    {
		clear();
	}

    // Clear all singleton instances
	void clear();

    // Add a singleton instance
	template <typename _class>
	void add(_class* pObj)
	{
		const char* lpszType = typeid(_class).name();
		assert(m_mapInstances.find(lpszType) == m_mapInstances.end());
		P<_class> *p = new P<_class>(pObj);
		m_mapInstances[lpszType] = p;
	}

    // Find the singleton's instance of _class
	template <typename _class>
	P<_class>* find()
	{
		const char* lpszType = typeid(_class).name();
		std::map<const char*, PBase*>::iterator iter = m_mapInstances.find(lpszType);
		if (iter != m_mapInstances.end())
		{
			return dynamic_cast<P<_class>*>(iter->second);
		}
		return nullptr;
	}

    // Find the singleton's instance of _class
    // @param lpszType: Specifies the type name of singleton to find
	PBase* find(const char* lpszType)
	{
		std::map<const char*, PBase*>::iterator iter = m_mapInstances.find(lpszType);
		if (iter != m_mapInstances.end())
		{
			return iter->second;
		}
		return nullptr;
	}
	
    // Remove the instance of _class
    // parameters:
    // @param del: If true, delete the instance of singleton
    // @return: If the instance is successfully deleted, return ture, otherwise it returns false
	template <typename _class>
	bool remove(bool del = false)
	{
		return remove(typeid(_class).name(), del);
	}

    // Remove the instance by specifies a type name
    // @param lpszType: Specifies the type name of singleton you want to remove
    // @param del: If true, delete the instance of singleton
    // @return: If the instance is successfully deleted, return ture, otherwise it returns false
	bool remove(const char* lpszType, bool del = false);

    // Instance of Manager
	static CSingletonMgr ms_instance;
private:
	std::map<const char*, PBase*> m_mapInstances;
};

#define singletonMgr CSingletonMgr::ms_instance


// Encapsulates a normal class into a singleton class
template<typename _class>
class TSingleton :public _class
{
private:
	TSingleton()
		:_class()
	{
		++instanceCount();
		singletonMgr.add(this);
	}
public:
	virtual ~TSingleton() {
		singletonMgr.remove<TSingleton>(false);
		--instanceCount();
	}

	static TSingleton<_class>& instance() {
		static TSingleton<_class>* instance = new TSingleton<_class>();
		return *instance;
	}

	static int& instanceCount() {
		static int ms_nInstanceCount = 0;
		return ms_nInstanceCount;
	}
};


// Check if the instance() function is available in the class
template<typename T>
struct THasInstanceFunc{
	template<typename U>
	static auto check(int) -> decltype(std::declval<U>().instance(), std::true_type());
	template<typename U>
	static std::false_type check(...);
	enum { has = std::is_same<decltype(check<T>(0)), std::true_type>::value };
	typedef decltype(check<T>(0)) hasType;
};


// Get the singleton instance of _class without instance() function
template <typename _class, typename hasInstance>
struct instanceOf
{
	static _class& get() {
		static _class* instance = nullptr;
		if (instance) {
			return *instance;
		}
		instance = new _class;
		singletonMgr.add(instance);
		return *instance;
	}
};

// Get the singleton instance of _class with instance() function
template <typename _class>
struct instanceOf<_class, std::true_type>
{
	static _class& get() {
		return _class::instance();
	}
};

// Get the singleton instance of _class
#define the(_class) instanceOf<_class,THasInstanceFunc<_class>::hasType>::get()

// Check if there is a singleton (you need to pre-define the instanceCount() static function in the class)
#define has(_class) (_class::instanceCount() > 0)

// Get the singleton instance from the singleton manager
#define getThe(_class) (singletonMgr.find<_class>())

// Delete the singleton instance
#define delThe(_class) (singletonMgr.remove<_class>(true))

