#pragma once
#include <boost/signals2/signal.hpp>
namespace bs2 = boost::signals2;

/*
Шаблонный интерфейс IObservable. Позволяет подписаться и отписаться на оповещения, а также
инициировать рассылку уведомлений зарегистрированным наблюдателям.
*/
template <typename T>
class IObservable
{
public:
	using Signal = bs2::signal<void(IObservable const& sender, T const& data)>;
	using Slot = typename Signal::slot_type;

	virtual ~IObservable() = default;
	virtual bs2::connection RegisterObserver(Slot const& slot) = 0;
	virtual void NotifyObservers() = 0;
};

// Реализация интерфейса IObservable
template <class T>
class CObservable : public IObservable<T>
{
public:
	typedef typename IObservable<T>::Signal Signal;
	typedef typename IObservable<T>::Slot Slot;

	bs2::connection RegisterObserver(Slot const& slot) override
	{
		return m_signal.connect(slot);
	}

	void NotifyObservers() override
	{
		m_signal(*this, GetChangedData());
	}

protected:
	// Классы-наследники должны перегрузить данный метод, 
	// в котором возвращать информацию об изменениях в объекте
	virtual T GetChangedData()const = 0;

private:
	Signal m_signal;
};
