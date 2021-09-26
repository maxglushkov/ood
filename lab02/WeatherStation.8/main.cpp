#include "WeatherData.h"

int main()
{
	CWeatherData wdIn, wdOut(true);

	CDisplay display;
	wdOut.RegisterObserver(display);
	wdIn.RegisterObserver(display);

	CStatsDisplay statsDisplay;
	wdOut.RegisterObserver(statsDisplay);
	wdIn.RegisterObserver(statsDisplay);

	wdOut.SetMeasurements(3, 0.7, 760);
	wdIn.SetMeasurements(23, 0.5, 760);
	wdOut.SetWindMeasurements(4, 90);

	wdOut.SetMeasurements(4, 0.8, 761);
	wdIn.SetMeasurements(24, 0.6, 761);
	wdOut.SetWindMeasurements(5, 270);

	wdOut.RemoveObserver(statsDisplay);
	wdIn.RemoveObserver(statsDisplay);

	wdOut.SetMeasurements(10, 0.8, 761);
	wdOut.SetWindMeasurements(3, 180);
	wdIn.SetMeasurements(25, 0.7, 761);

	wdOut.SetMeasurements(-10, 0.8, 761);
	wdOut.SetWindMeasurements(3, 180);
	wdIn.SetMeasurements(24, 0.7, 761);
	return 0;
}
