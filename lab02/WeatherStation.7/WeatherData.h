#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cmath>
#include "Observer.h"

struct SWeatherInfo
{
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
	double windSpeed = 0;
	double windDirection = 0;
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
		std::cout << "Current Wind Speed " << data.windSpeed << std::endl;
		std::cout << "Current Wind Direction " << data.windDirection << std::endl;
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
		m_temperature.Update("Temp", data.temperature);
		m_humidity.Update("Hum", data.humidity);
		m_pressure.Update("Pressure", data.pressure);
		m_windSpeed.Update("Wind Speed", data.windSpeed);
		m_windDirection.Update("Wind Direction", data.windSpeed, data.windDirection);
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
	}
	m_temperature, m_humidity, m_pressure, m_windSpeed;

	class CPolarAngleStats
	{
	public:
		void Update(std::string const& name, double radius, double angle)
		{
			angle *= M_PI / 180.0;
			m_accX += radius * cos(angle);
			m_accY += radius * sin(angle);

			angle = atan2(m_accY, m_accX) / M_PI * 180.0;
			if (angle < 0)
			{
				angle += 360.0;
			}
			std::cout << "Average " << name << ' ' << angle << std::endl;
			std::cout << "----------------" << std::endl;
		}
	private:
		double m_accX = 0, m_accY = 0;
	}
	m_windDirection;
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
	// Скорость ветра (в м/с)
	double GetWindSpeed()const
	{
		return m_windSpeed;
	}
	// Направление ветра (в градусах, где 0 – север, 90-восток, 180-юг, 270-запад)
	double GetWindDirection()const
	{
		return m_windDirection;
	}

	void MeasurementsChanged()
	{
		NotifyObservers();
	}

	void SetMeasurements(double temp, double humidity, double pressure, double windSpeed, double windDirection)
	{
		m_humidity = humidity;
		m_temperature = temp;
		m_pressure = pressure;
		m_windSpeed = windSpeed;
		m_windDirection = windDirection;

		MeasurementsChanged();
	}
protected:
	SWeatherInfo GetChangedData()const override
	{
		SWeatherInfo info;
		info.temperature = GetTemperature();
		info.humidity = GetHumidity();
		info.pressure = GetPressure();
		info.windSpeed = GetWindSpeed();
		info.windDirection = GetWindDirection();
		return info;
	}
private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
	double m_windSpeed = 0.0;
	double m_windDirection = 0.0;
};
