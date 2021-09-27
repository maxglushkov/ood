#pragma once
#include <cmath>
#include <iostream>
#include "Observer.h"

struct SWeatherInfo
{
	struct SWind
	{
		double speed = 0;
		double direction = 0;
	};
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
	std::unique_ptr<SWind> wind;
};

static void Display(IObservable<SWeatherInfo> const& sender, SWeatherInfo const& data)
{
	std::cout << "Weather Station " << &sender << std::endl;
	std::cout << "Current Temp " << data.temperature << std::endl;
	std::cout << "Current Hum " << data.humidity << std::endl;
	std::cout << "Current Pressure " << data.pressure << std::endl;
	if (data.wind)
	{
		std::cout << "Current Wind Speed " << data.wind->speed << std::endl;
		std::cout << "Current Wind Direction " << data.wind->direction << std::endl;
	}
	std::cout << "----------------" << std::endl;
}

struct StatsDisplay
{
public:
	void operator()(IObservable<SWeatherInfo> const& sender, SWeatherInfo const& data)
	{
		std::cout << "Weather Station " << &sender << std::endl;
		temperature.Update("Temp", data.temperature);
		humidity.Update("Hum", data.humidity);
		pressure.Update("Pressure", data.pressure);
		if (data.wind)
		{
			windSpeed.Update("Wind Speed", data.wind->speed);
			windDirection.Update("Wind Direction", data.wind->speed, data.wind->direction);
		}
	}

private:
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
	temperature, humidity, pressure, windSpeed;

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
	windDirection;
};

class CWeatherData : public CObservable<SWeatherInfo>
{
public:
	explicit CWeatherData(bool hasWindSensors = false)
	{
		if (hasWindSensors)
		{
			m_wind = std::make_unique<SWeatherInfo::SWind>();
		}
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
	// Скорость ветра (в м/с)
	double GetWindSpeed()const
	{
		return m_wind->speed;
	}
	// Направление ветра (в градусах, где 0 – север, 90-восток, 180-юг, 270-запад)
	double GetWindDirection()const
	{
		return m_wind->direction;
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
	void SetWindMeasurements(double speed, double direction)
	{
		m_wind->speed = speed;
		m_wind->direction = direction;

		MeasurementsChanged();
	}
protected:
	SWeatherInfo GetChangedData()const override
	{
		SWeatherInfo info;
		info.temperature = GetTemperature();
		info.humidity = GetHumidity();
		info.pressure = GetPressure();
		if (m_wind)
		{
			info.wind = std::make_unique<SWeatherInfo::SWind>(*m_wind);
		}
		return info;
	}
private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
	std::unique_ptr<SWeatherInfo::SWind> m_wind;
};
