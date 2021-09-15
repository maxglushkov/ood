#pragma once
#include <iostream>
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
	void Update(SWeatherInfo const& data) override
	{
		std::cout << "Current Temp " << data.temperature << std::endl;
		std::cout << "Current Hum " << data.humidity << std::endl;
		std::cout << "Current Pressure " << data.pressure << std::endl;
		std::cout << "----------------" << std::endl;
	}
};

class CStatsDisplay : public IObserver<SWeatherInfo>
{
public:
	CStatsDisplay()
	{
		for (auto const& [field, name] : FIELD_NAME_PAIRS)
		{
			m_minValues.*field = std::numeric_limits<double>::infinity();
			m_maxValues.*field = -std::numeric_limits<double>::infinity();
			m_accValues.*field = 0;
		}
	}

private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
	Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
	остается публичным
	*/
	void Update(SWeatherInfo const& data) override
	{
		++m_countAcc;
		for (auto const& [field, name] : FIELD_NAME_PAIRS)
		{
			if (m_minValues.*field > data.*field)
			{
				m_minValues.*field = data.*field;
			}
			if (m_maxValues.*field < data.*field)
			{
				m_maxValues.*field = data.*field;
			}
			m_accValues.*field += data.*field;

			std::cout << "Max " << name << ' ' << m_maxValues.*field << std::endl;
			std::cout << "Min " << name << ' ' << m_minValues.*field << std::endl;
			std::cout << "Average " << name << ' ' << (m_accValues.*field / m_countAcc) << std::endl;
			std::cout << "----------------" << std::endl;
		}
	}

	SWeatherInfo m_minValues;
	SWeatherInfo m_maxValues;
	SWeatherInfo m_accValues;
	unsigned m_countAcc = 0;

	constexpr static auto FIELD_NAME_PAIRS = {
		std::pair(&SWeatherInfo::temperature, "Temp"),
		std::pair(&SWeatherInfo::humidity, "Hum"),
		std::pair(&SWeatherInfo::pressure, "Pressure")
	};
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
