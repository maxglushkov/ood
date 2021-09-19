#include "WeatherData.h"

int main()
{
	CWeatherData wd;

	CDisplay display;
	wd.RegisterObserver(display);

	CStatsDisplay statsDisplay;
	wd.RegisterObserver(statsDisplay);

	wd.SetMeasurements(3, 0.7, 760, 4, 90);
	wd.SetMeasurements(4, 0.8, 761, 5, 270);

	wd.RemoveObserver(statsDisplay);

	wd.SetMeasurements(10, 0.8, 761, 3, 180);
	wd.SetMeasurements(-10, 0.8, 761, 0, 0);
	return 0;
}
