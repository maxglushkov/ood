#pragma once
#include <iostream>
#include <cmath>
#include "Observer.h"

struct SWeatherInfo
{
	enum Event
	{
		Temperature,
		Humidity,
		Pressure,
		WindSpeed,
		WindDirection
	};

	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
	double windSpeed = 0;
	double windDirection = 0;
};

class CDisplay: public IObserver<SWeatherInfo, 5>
{
private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
		Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
		остается публичным
	*/
	void Update(Events const& events, SWeatherInfo const& data) override
	{
		if (events[SWeatherInfo::Temperature])
		{
			std::cout << "Current Temp " << data.temperature << std::endl;
		}
		if (events[SWeatherInfo::Humidity])
		{
			std::cout << "Current Hum " << data.humidity << std::endl;
		}
		if (events[SWeatherInfo::Pressure])
		{
			std::cout << "Current Pressure " << data.pressure << std::endl;
		}
		if (events[SWeatherInfo::WindSpeed])
		{
			std::cout << "Current Wind Speed " << data.windSpeed << std::endl;
		}
		if (events[SWeatherInfo::WindDirection])
		{
			std::cout << "Current Wind Direction " << data.windDirection << std::endl;
		}
		std::cout << "----------------" << std::endl;
	}
};

class CStatsDisplay : public IObserver<SWeatherInfo, 5>
{
private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
	Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
	остается публичным
	*/
	void Update(Events const& events, SWeatherInfo const& data) override
	{
		if (events[SWeatherInfo::Temperature])
		{
			m_temperature.Update("Temp", data.temperature);
		}
		if (events[SWeatherInfo::Humidity])
		{
			m_humidity.Update("Hum", data.humidity);
		}
		if (events[SWeatherInfo::Pressure])
		{
			m_pressure.Update("Pressure", data.pressure);
		}
		if (events[SWeatherInfo::WindSpeed])
		{
			m_windSpeed.Update("Wind Speed", data.windSpeed);
		}
		if (events[SWeatherInfo::WindSpeed] || events[SWeatherInfo::WindDirection])
		{
			m_windDirection.Update("Wind Direction", data.windSpeed, data.windDirection);
		}
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

class CWeatherData : public CObservable<SWeatherInfo, 5>
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

	void SetTemperatureMeasurements(double temp)
	{
		m_temperature = temp;
		NotifyObservers(Events().set(SWeatherInfo::Temperature));
	}
	void SetHumidityMeasurements(double humidity)
	{
		m_humidity = humidity;
		NotifyObservers(Events().set(SWeatherInfo::Humidity));
	}
	void SetPressureMeasurements(double pressure)
	{
		m_pressure = pressure;
		NotifyObservers(Events().set(SWeatherInfo::Pressure));
	}
	void SetWindMeasurements(double speed, double direction)
	{
		m_windSpeed = speed;
		m_windDirection = direction;

		NotifyObservers(Events()
			.set(SWeatherInfo::WindSpeed)
			.set(SWeatherInfo::WindDirection));
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
