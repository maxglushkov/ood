#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "WeatherData.h"

class CCallbackObserver : public IObserver<SWeatherInfo>
{
public:
	using Callback = std::function<void(IObservable<SWeatherInfo> const*)>;

	CCallbackObserver(Callback callback)
		: m_callback(callback)
	{
	}
private:
	Callback m_callback;

	void Update(IObservable<SWeatherInfo> const& sender, SWeatherInfo const& data) override
	{
		m_callback(&sender);
	}
};

TEST_CASE("Observing several data sources")
{
	CWeatherData wds[2];
	std::vector<IObservable<SWeatherInfo> const*> log;

	CCallbackObserver observer(
		[&](auto sender)
		{
			log.push_back(sender);
		}
	);
	for (auto & wd : wds)
	{
		wd.RegisterObserver(observer);
	}
	REQUIRE(log.empty());

	wds[1].SetMeasurements(1.85, 1, 720);
	wds[0].SetMeasurements(16.85, 0.9, 720);
	wds[0].SetMeasurements(16.85, 0.9, 730);
	wds[1].SetMeasurements(6.85, 0.98, 730);
	REQUIRE(
		log == std::vector<IObservable<SWeatherInfo> const*>
		{
			&wds[1],
			&wds[0],
			&wds[0],
			&wds[1]
		}
	);
}
