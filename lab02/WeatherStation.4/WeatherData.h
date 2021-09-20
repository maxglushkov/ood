#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <climits>
#include "Observer.h"

struct SWeatherInfo
{
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
};

class CDisplay: public IObserver<SWeatherInfo>
{
private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
		Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
		остается публичным
	*/
	void Update(IObservable<SWeatherInfo> const& sender, SWeatherInfo const& data) override
	{
		std::cout << "Weather Station " << &sender << std::endl;
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
	void Update(IObservable<SWeatherInfo> const& sender, SWeatherInfo const& data) override
	{
		auto & stats = m_stats[&sender];
		stats.m_temperature.Update("Temp", data.temperature);
		stats.m_humidity.Update("Hum", data.humidity);
		stats.m_pressure.Update("Pressure", data.pressure);
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

	struct Stats
	{
		CGenericStats m_temperature;
		CGenericStats m_humidity;
		CGenericStats m_pressure;
	};
	std::map<IObservable<SWeatherInfo> const*, Stats> m_stats;
};

class CWeatherData : public CObservable<SWeatherInfo>
{
public:
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
		SWeatherInfo info;
		info.temperature = GetTemperature();
		info.humidity = GetHumidity();
		info.pressure = GetPressure();
		return info;
	}
private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
};
