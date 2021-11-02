#pragma once
#include <boost/iterator/indirect_iterator.hpp>
#include <memory>
#include <vector>
#include "CShape.hpp"

class CPictureDraft
{
public:
	typedef std::vector<std::unique_ptr<CShape>> Storage;
	typedef boost::indirect_iterator<Storage::const_iterator, CShape const&> ConstIterator;

	void AddShape(std::unique_ptr<CShape> && shape)
	{
		m_shapes.push_back(std::move(shape));
	}

	ConstIterator begin()const
	{
		return m_shapes.begin();
	}

	ConstIterator end()const
	{
		return m_shapes.end();
	}

private:
	Storage m_shapes;
};
