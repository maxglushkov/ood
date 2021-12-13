#pragma once
#include <functional>
#include "CArguments.hpp"

class CMenu
{
public:
	typedef std::function<bool(CArguments &, std::ostream &)> Command;

	struct Item
	{
		std::string name, description;
		Command command;
	};

	CMenu(std::initializer_list<Item> && items)
		:m_items(std::move(items))
	{}

	virtual ~CMenu() = default;

	std::vector<Item> const& GetItems()const
	{
		return m_items;
	}

	void Run(std::istream & input, std::ostream & output, std::ostream & error)const;

private:
	std::vector<Item> m_items;
};
