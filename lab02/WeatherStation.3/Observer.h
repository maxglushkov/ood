#pragma once

#include <map>
#include <set>

/*
Шаблонный интерфейс IObserver. Его должен реализовывать класс, 
желающий получать уведомления от соответствующего IObservable
Параметром шаблона является тип аргумента,
передаваемого Наблюдателю в метод Update
*/
template <typename T>
class IObserver
{
public:
	virtual void Update(T const& data) = 0;
	virtual ~IObserver() = default;
};

/*
Шаблонный интерфейс IObservable. Позволяет подписаться и отписаться на оповещения, а также
инициировать рассылку уведомлений зарегистрированным наблюдателям.
*/
template <typename T>
class IObservable
{
public:
	virtual ~IObservable() = default;
	virtual void RegisterObserver(IObserver<T> & observer, int priority = 0) = 0;
	virtual void NotifyObservers() = 0;
	virtual void RemoveObserver(IObserver<T> & observer) = 0;
};

// Реализация интерфейса IObservable
template <class T>
class CObservable : public IObservable<T>
{
public:
	typedef IObserver<T> ObserverType;

	void RegisterObserver(ObserverType & observer, int priority = 0) override
	{
		auto [it, isInserted] = m_observerPriorityMap.try_emplace(&observer, priority);
		if (isInserted)
		{
			try
			{
				m_observers.emplace(&observer, priority);
			}
			catch (...)
			{
				m_observerPriorityMap.erase(it);
				throw;
			}
		}
	}

	void NotifyObservers() override
	{
		T data = GetChangedData();
		for (auto & observer : std::set(m_observers))
		{
			observer.observer->Update(data);
		}
	}

	void RemoveObserver(ObserverType & observer) override
	{
		auto it = m_observerPriorityMap.find(&observer);
		if (it != m_observerPriorityMap.end())
		{
			m_observers.erase(ObserverPriority(*it));
			m_observerPriorityMap.erase(it);
		}
	}

protected:
	// Классы-наследники должны перегрузить данный метод, 
	// в котором возвращать информацию об изменениях в объекте
	virtual T GetChangedData()const = 0;

private:
	struct ObserverPriority
	{
		ObserverType *const observer;
		const int priority;

		constexpr ObserverPriority(ObserverType * observer, int priority)
			: observer(observer)
			, priority(priority)
		{
		}
		constexpr ObserverPriority(std::pair<ObserverType *, int> const& pair)
			: observer(pair.first)
			, priority(pair.second)
		{
		}

		bool operator >(ObserverPriority const& other)const
		{
			return priority != other.priority ? priority > other.priority : observer < other.observer;
		}
	};

	std::set<ObserverPriority, std::greater<ObserverPriority>> m_observers;
	std::map<ObserverType *, int> m_observerPriorityMap;
};
