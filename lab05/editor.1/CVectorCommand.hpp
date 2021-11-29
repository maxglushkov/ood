#pragma once
#include <optional>
#include <vector>
#include "ICommand.hpp"

template<typename T>
class CVectorCommand: public ICommand
{
public:
	CVectorCommand(std::vector<T> & vector, size_t position, std::optional<T> && item)
		:m_vector(vector)
		,m_item(std::move(item))
		,m_position(position)
	{
		if (item.has_value())
		{
			vector.reserve(vector.size() + 1);
		}
	}

	void Do()noexcept override
	{
		const auto iter = m_vector.cbegin() + m_position;
		if (m_item.has_value())
		{
			m_vector.insert(iter, std::move(*m_item));
			m_item = std::nullopt;
		}
		else
		{
			m_item = std::move(*iter);
			m_vector.erase(iter);
		}
	}

private:
	std::vector<T> & m_vector;
	std::optional<T> m_item;
	size_t m_position;
};
