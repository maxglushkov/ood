#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "WeatherData.h"

template <typename T>
class COneshotObserver : public IObserver<T>
{
public:
	COneshotObserver(IObservable<T> & observable)
		: m_observable(&observable)
	{
		m_observable->RegisterObserver(*this);
	}

	~COneshotObserver()
	{
		if (m_observable)
		{
			m_observable->RemoveObserver(*this);
		}
	}

	COneshotObserver(COneshotObserver const&) = delete;
	COneshotObserver(COneshotObserver &&) = delete;
	COneshotObserver & operator =(COneshotObserver const&) = delete;
	COneshotObserver & operator =(COneshotObserver &&) = delete;

	operator bool()const
	{
		return m_observable;
	}

private:
	IObservable<T> * m_observable;

	void Update(T const& data) override
	{
		m_observable->RemoveObserver(*this);
		m_observable = nullptr;
	}
};

TEST_CASE("Removing itself from observers on call to IObserver<T>::Update()")
{
	CWeatherData wd;

	COneshotObserver oneshotObserver(wd);
	REQUIRE(oneshotObserver);

	REQUIRE_NOTHROW(wd.SetMeasurements(26.85, 0.5, 760));
	REQUIRE_FALSE(oneshotObserver);

	REQUIRE_NOTHROW(wd.SetMeasurements(26.85, 0.7, 760));
}
