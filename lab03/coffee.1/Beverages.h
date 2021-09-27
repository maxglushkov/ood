#pragma once

#include "IBeverage.h"

// Базовая реализация напитка, предоставляющая его описание
class CBeverage : public IBeverage
{
public:
	CBeverage(const std::string & description)
		:m_description(description)
	{}

	std::string GetDescription()const override final
	{
		return m_description;
	}
private:
	std::string m_description;
};

// Кофе
class CCoffee : public CBeverage
{
public:
	CCoffee(const std::string& description = "Coffee")
		:CBeverage(description) 
	{}

	double GetCost() const override 
	{
		return 60; 
	}
};

struct CoffeePortion
{
	enum Portion
	{
		Standard,
		Double
	};

	CoffeePortion(Portion portion)
		:m_portion(portion)
	{}

	operator std::string()const
	{
		constexpr static char const* PORTION_DESCRIPTION[] = {"standard", "double"};
		return std::string(PORTION_DESCRIPTION[m_portion]) + " portion";
	}
	operator Portion()const
	{
		return m_portion;
	}
private:
	Portion m_portion;
};

// Капуччино
class CCappuccino : public CCoffee
{
public:
	CCappuccino(CoffeePortion portion = CoffeePortion::Standard)
		:CCoffee("Cappuccino (" + std::string(portion) + ')')
		,m_portion(portion)
	{}

	double GetCost() const override 
	{
		constexpr static double PORTION_COST[] = {80, 120};
		return PORTION_COST[m_portion];
	}
private:
	CoffeePortion m_portion;
};

// Латте
class CLatte : public CCoffee
{
public:
	CLatte(CoffeePortion portion = CoffeePortion::Standard)
		:CCoffee("Latte (" + std::string(portion) + ')')
		,m_portion(portion)
	{}

	double GetCost() const override 
	{
		constexpr static double PORTION_COST[] = {90, 130};
		return PORTION_COST[m_portion];
	}
private:
	CoffeePortion m_portion;
};

// Чай
class CTea : public CBeverage
{
public:
	CTea(std::string const& description = "Tea")
		:CBeverage(description)
	{}

	double GetCost() const override 
	{
		return 30; 
	}
};

class CIvanChai : public CTea
{
public:
	CIvanChai()
		:CTea("Ivan chai")
	{}
};

class CGeorgianTea : public CTea
{
public:
	CGeorgianTea()
		:CTea("Georgian tea")
	{}
};

class CAzerbaijaniTea : public CTea
{
public:
	CAzerbaijaniTea()
		:CTea("Azerbaijani tea")
	{}
};

class CKrasnodarTea : public CTea
{
public:
	CKrasnodarTea()
		:CTea("Krasnodar tea")
	{}
};

struct MilkshakePortion
{
	enum Portion
	{
		Small,
		Medium,
		Large
	};

	MilkshakePortion(Portion portion)
		:m_portion(portion)
	{}

	operator std::string()const
	{
		constexpr static char const* PORTION_DESCRIPTION[] = {"small", "medium", "large"};
		return std::string(PORTION_DESCRIPTION[m_portion]) + " portion";
	}
	operator Portion()const
	{
		return m_portion;
	}
private:
	Portion m_portion;
};

// Молочный коктейль
class CMilkshake : public CBeverage
{
public:
	CMilkshake(MilkshakePortion portion = MilkshakePortion::Large)
		:CBeverage("Milkshake (" + std::string(portion) + ')')
		,m_portion(portion)
	{}

	double GetCost() const override 
	{ 
		constexpr static double PORTION_COST[] = {50, 60, 80};
		return PORTION_COST[m_portion];
	}
private:
	MilkshakePortion m_portion;
};
