#include "WeatherData.h"

int main()
{
	CWeatherData wd;

	CDisplay display;
	wd.RegisterObserver(display, CWeatherData::Events()
		.set(SWeatherInfo::Temperature)
		.set(SWeatherInfo::Pressure));

	CStatsDisplay statsDisplay;
	wd.RegisterObserver(statsDisplay, CWeatherData::Events()
		.set(SWeatherInfo::Temperature)
		.set(SWeatherInfo::WindDirection));

	wd.SetTemperatureMeasurements(3);
	wd.SetHumidityMeasurements(0.7);
	wd.SetPressureMeasurements(760);
	wd.SetWindMeasurements(4, 90);

	wd.RegisterObserver(statsDisplay, CWeatherData::Events()
		.set(SWeatherInfo::Temperature)
		.set(SWeatherInfo::Humidity));

	wd.SetTemperatureMeasurements(4);
	wd.SetHumidityMeasurements(0.8);
	wd.SetPressureMeasurements(761);
	wd.SetWindMeasurements(5, 270);

	wd.UnregisterObserver(statsDisplay, CWeatherData::Events().set(SWeatherInfo::Temperature));

	wd.SetTemperatureMeasurements(10);
	wd.SetWindMeasurements(3, 180);

	wd.SetTemperatureMeasurements(-10);
	wd.SetWindMeasurements(0, 0);
	return 0;
}
