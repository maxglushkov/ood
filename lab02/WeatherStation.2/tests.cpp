#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "WeatherData.h"

class CCallbackObserver : public IObserver<SWeatherInfo>
{
public:
	using Callback = std::function<void(CCallbackObserver *)>;

	CCallbackObserver(Callback callback)
		: m_callback(callback)
	{
	}
private:
	Callback m_callback;

	void Update(SWeatherInfo const& data) override
	{
		m_callback(this);
	}
};

TEST_CASE("Removing observers on call to IObserver<T>::Update()")
{
	CWeatherData wd;
	std::vector<CCallbackObserver *> log;

	CCallbackObserver observers[3] = {
		CCallbackObserver(
			[&](auto observer)
			{
				REQUIRE(observer == &observers[0]);
				wd.RemoveObserver(observers[0]);
				log.push_back(observer);
			}
		),
		CCallbackObserver(
			[&](auto observer)
			{
				REQUIRE(observer == &observers[1]);
				wd.RemoveObserver(observers[2]);
				log.push_back(observer);
			}
		),
		CCallbackObserver(
			[&](auto observer)
			{
				REQUIRE(observer == &observers[2]);
				wd.RemoveObserver(observers[1]);
				log.push_back(observer);
			}
		)
	};
	for (auto & observer : observers)
	{
		wd.RegisterObserver(observer);
	}
	REQUIRE(log.empty());

	REQUIRE_NOTHROW(wd.SetMeasurements(26.85, 0.5, 760));
	REQUIRE(
		log == std::vector
		{
			&observers[0],
			&observers[1],
			&observers[2]
		}
	);

	log.clear();
	REQUIRE_NOTHROW(wd.SetMeasurements(26.85, 0.7, 760));
	REQUIRE(log.empty());
}
