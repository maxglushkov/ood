#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <climits>
#include "Observer.h"

struct SWeatherInfo
{
	std::string const& location;
	double temperature;
	double humidity;
	double pressure;
};

class CDisplay: public IObserver<SWeatherInfo>
{
private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
		Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
		остается публичным
	*/
	void Update(SWeatherInfo const& data) override
	{
		if (!data.location.empty())
		{
			std::cout << "Weather Station " << data.location << std::endl;
		}
		std::cout << "Current Temp " << data.temperature << std::endl;
		std::cout << "Current Hum " << data.humidity << std::endl;
		std::cout << "Current Pressure " << data.pressure << std::endl;
		std::cout << "----------------" << std::endl;
	}
};

class CStatsDisplay : public IObserver<SWeatherInfo>
{
private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
	Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
	остается публичным
	*/
	void Update(SWeatherInfo const& data) override
	{
		Update1(data.location, "Temp", data.temperature);
		Update1(data.location, "Hum", data.humidity);
		Update1(data.location, "Pressure", data.pressure);
	}

	template <typename... Args>
	void Update1(std::string location, const char * name, Args ...data)
	{
		if (!location.empty())
		{
			location.push_back(' ');
		}
		location += name;
		m_genericStats[location].Update(location, data...);
	}

	class CGenericStats
	{
	public:
		void Update(std::string const& name, double data)
		{
			if (m_min > data)
			{
				m_min = data;
			}
			if (m_max < data)
			{
				m_max = data;
			}
			m_acc += data;
			++m_count;

			std::cout << "Max " << name << ' ' << m_max << std::endl;
			std::cout << "Min " << name << ' ' << m_min << std::endl;
			std::cout << "Average " << name << ' ' << (m_acc / m_count) << std::endl;
			std::cout << "----------------" << std::endl;
		}
	private:
		double m_min = std::numeric_limits<double>::infinity();
		double m_max = -std::numeric_limits<double>::infinity();
		double m_acc = 0;
		unsigned m_count = 0;
	};
	std::map<std::string, CGenericStats> m_genericStats;
};

class CWeatherData : public CObservable<SWeatherInfo>
{
public:
	CWeatherData(std::string const& location = std::string())
		: m_location(location)
	{
	}

	// Температура в градусах Цельсия
	double GetTemperature()const
	{
		return m_temperature;
	}
	// Относительная влажность (0...100)
	double GetHumidity()const
	{
		return m_humidity;
	}
	// Атмосферное давление (в мм.рт.ст)
	double GetPressure()const
	{
		return m_pressure;
	}

	void MeasurementsChanged()
	{
		NotifyObservers();
	}

	void SetMeasurements(double temp, double humidity, double pressure)
	{
		m_humidity = humidity;
		m_temperature = temp;
		m_pressure = pressure;

		MeasurementsChanged();
	}
protected:
	SWeatherInfo GetChangedData()const override
	{
		return {
			.location = m_location,
			.temperature = GetTemperature(),
			.humidity = GetHumidity(),
			.pressure = GetPressure()
		};
	}
private:
	std::string m_location;
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
};
