#include "CMenu.hpp"

void CMenu::Run(std::istream & input, std::ostream & output, std::ostream & error)const
{
	std::string line;
	while (output << "> " && std::getline(input, line))
	{
		CArguments args(line);
		const auto name = args.Pop<std::string>();
		try
		{
			const auto iter = std::find_if(
				m_items.cbegin(), m_items.cend(),
				[&](auto & item)
				{
					return item.name == name;
				}
			);
			if (iter == m_items.end())
			{
				throw std::invalid_argument("unknown command");
			}
			if (!iter->command(args, output))
			{
				break;
			}
		}
		catch (std::exception const& exception)
		{
			error << "Error: " << exception.what() << '\n';
		}
	}
}
