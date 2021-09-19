#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "WeatherData.h"

template <typename T>
class CLoggingObserver : public IObserver<T>
{
public:
	static std::vector<CLoggingObserver<T> *> const& GetLog()
	{
		return m_log;
	}

	static void ResetLog()
	{
		m_log.clear();
	}

private:
	static std::vector<CLoggingObserver<T> *> m_log;

	void Update(T const& data) override
	{
		m_log.push_back(this);
	}
};

template <typename T>
std::vector<CLoggingObserver<T> *> CLoggingObserver<T>::m_log;

TEST_CASE("Testing observers' priorities")
{
	CWeatherData wd;

	CLoggingObserver<SWeatherInfo> loggingObserver[3];
	wd.RegisterObserver(loggingObserver[0], 0);
	wd.RegisterObserver(loggingObserver[1], 1);
	wd.RegisterObserver(loggingObserver[2]);
	wd.RegisterObserver(loggingObserver[2], 2);
	REQUIRE(CLoggingObserver<SWeatherInfo>::GetLog().empty());

	wd.SetMeasurements(6.85, 0.8, 740);
	REQUIRE(
		CLoggingObserver<SWeatherInfo>::GetLog() == std::vector
		{
			&loggingObserver[1],
			&loggingObserver[0],
			&loggingObserver[2]
		}
	);

	CLoggingObserver<SWeatherInfo>::ResetLog();
	REQUIRE(CLoggingObserver<SWeatherInfo>::GetLog().empty());

	wd.RemoveObserver(loggingObserver[0]);
	wd.RemoveObserver(*(loggingObserver + 3));

	wd.SetMeasurements(11.85, 0.7, 750);
	REQUIRE(
		CLoggingObserver<SWeatherInfo>::GetLog() == std::vector
		{
			&loggingObserver[1],
			&loggingObserver[2]
		}
	);

	wd.RemoveObserver(loggingObserver[1]);
	wd.RemoveObserver(loggingObserver[2]);
}
