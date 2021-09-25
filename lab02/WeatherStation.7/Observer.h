#pragma once
#include <bitset>
#include <map>

/*
Шаблонный интерфейс IObserver. Его должен реализовывать класс, 
желающий получать уведомления от соответствующего IObservable
Параметром шаблона является тип аргумента,
передаваемого Наблюдателю в метод Update
*/
template <typename T, size_t N>
class IObserver
{
public:
	using Events = std::bitset<N>;

	virtual void Update(Events const& events, T const& data) = 0;
	virtual ~IObserver() = default;
};

/*
Шаблонный интерфейс IObservable. Позволяет подписаться и отписаться на оповещения, а также
инициировать рассылку уведомлений зарегистрированным наблюдателям.
*/
template <typename T, size_t N>
class IObservable
{
public:
	using Events = typename IObserver<T, N>::Events;

	virtual ~IObservable() = default;
	virtual void RegisterObserver(IObserver<T, N> & observer, Events const& events) = 0;
	virtual void NotifyObservers(Events const& events) = 0;
	virtual void UnregisterObserver(IObserver<T, N> & observer, Events const& events) = 0;
};

// Реализация интерфейса IObservable
template <class T, size_t N>
class CObservable : public IObservable<T, N>
{
public:
	typedef IObserver<T, N> ObserverType;
	typedef typename ObserverType::Events Events;

	void RegisterObserver(ObserverType & observer, Events const& events) override
	{
		auto [it, isInserted] = m_observers.try_emplace(&observer, events);
		if (!isInserted)
		{
			it->second |= events;
		}
	}

	void NotifyObservers(Events const& events) override
	{
		T data = GetChangedData();
		for (auto & [observer, registeredEvents] : std::map(m_observers))
		{
			const auto relevantEvents = registeredEvents & events;
			if (relevantEvents.any())
			{
				observer->Update(relevantEvents, data);
			}
		}
	}

	void UnregisterObserver(ObserverType & observer, Events const& events) override
	{
		auto it = m_observers.find(&observer);
		if (it != m_observers.end())
		{
			if ((it->second &= ~events).none())
			{
				m_observers.erase(it);
			}
		}
	}

protected:
	// Классы-наследники должны перегрузить данный метод, 
	// в котором возвращать информацию об изменениях в объекте
	virtual T GetChangedData()const = 0;

private:
	std::map<ObserverType *, Events> m_observers;
};
