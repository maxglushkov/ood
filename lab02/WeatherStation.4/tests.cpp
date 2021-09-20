#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "WeatherData.h"

class CLoggingObserver : public IObserver<SWeatherInfo>
{
public:
	static std::string GetLog()
	{
		return m_log.str();
	}

private:
	static std::stringstream m_log;

	void Update(SWeatherInfo const& data) override
	{
		m_log << data.location << std::endl;
	}
};

std::stringstream CLoggingObserver::m_log;

TEST_CASE("Observing several data sources")
{
	CWeatherData wdIn("in");
	CWeatherData wdOut("out");

	CLoggingObserver loggingObserver;
	wdIn.RegisterObserver(loggingObserver);
	wdOut.RegisterObserver(loggingObserver);
	REQUIRE(loggingObserver.GetLog().empty());

	wdOut.SetMeasurements(1.85, 1, 720);
	wdIn.SetMeasurements(16.85, 0.9, 720);
	wdIn.SetMeasurements(16.85, 0.9, 730);
	wdOut.SetMeasurements(6.85, 0.98, 730);
	REQUIRE(loggingObserver.GetLog() == "out\nin\nin\nout\n");
}
