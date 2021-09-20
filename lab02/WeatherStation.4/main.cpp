#include "WeatherData.h"

int main()
{
	CWeatherData wd;
	CWeatherData wdIn("in");

	CDisplay display;
	wd.RegisterObserver(display);
	wdIn.RegisterObserver(display);

	CStatsDisplay statsDisplay;
	wd.RegisterObserver(statsDisplay);
	wdIn.RegisterObserver(statsDisplay);

	wd.SetMeasurements(3, 0.7, 760);
	wdIn.SetMeasurements(23, 0.5, 760);
	wd.SetMeasurements(4, 0.8, 761);
	wdIn.SetMeasurements(24, 0.6, 761);

	wd.RemoveObserver(statsDisplay);
	wdIn.RemoveObserver(statsDisplay);

	wd.SetMeasurements(10, 0.8, 761);
	wdIn.SetMeasurements(25, 0.7, 761);
	wd.SetMeasurements(-10, 0.8, 761);
	wdIn.SetMeasurements(24, 0.7, 761);
	return 0;
}
