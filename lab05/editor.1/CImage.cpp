#include "CImage.hpp"
#include "CSetCommand.hpp"

void CImage::Resize(int width, int height)
{
	m_history.Do(std::make_unique<CSetCommand<CSize>>(m_size, CSize(width, height)));
}
