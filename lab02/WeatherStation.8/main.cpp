#include "WeatherData.h"

int main()
{
	CWeatherData wdIn, wdOut(true);

	wdOut.RegisterObserver(Display);
	wdIn.RegisterObserver(Display);

	const auto outStatsConn = wdOut.RegisterObserver(StatsDisplay());
	const auto inStatsConn = wdIn.RegisterObserver(StatsDisplay());

	wdOut.SetMeasurements(3, 0.7, 760);
	wdIn.SetMeasurements(23, 0.5, 760);
	wdOut.SetWindMeasurements(4, 90);

	wdOut.SetMeasurements(4, 0.8, 761);
	wdIn.SetMeasurements(24, 0.6, 761);
	wdOut.SetWindMeasurements(5, 270);

	outStatsConn.disconnect();

	wdOut.SetMeasurements(10, 0.8, 761);
	wdOut.SetWindMeasurements(3, 180);
	wdIn.SetMeasurements(25, 0.7, 761);

	wdOut.SetMeasurements(-10, 0.8, 761);
	wdOut.SetWindMeasurements(3, 180);
	wdIn.SetMeasurements(24, 0.7, 761);
	return 0;
}
