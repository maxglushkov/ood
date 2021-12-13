#pragma once
#include "CMenu.hpp"

template<typename GumballMachineType>
class CGumballMachineMenu: public CMenu
{
public:
	CGumballMachineMenu(GumballMachineType & machine)
		:CMenu{
			{
				"InsertQuarter",
				"Inserts a quarter",
				[&](CArguments &, std::ostream &)
				{
					machine.InsertQuarter();
					return true;
				}
			}, {
				"EjectQuarters",
				"Ejects all quarters",
				[&](CArguments &, std::ostream &)
				{
					machine.EjectQuarters();
					return true;
				}
			}, {
				"TurnCrank",
				"Turns crank",
				[&](CArguments &, std::ostream &)
				{
					machine.TurnCrank();
					return true;
				}
			}, {
				"Display",
				"Displays machine state",
				[&](CArguments &, std::ostream & output)
				{
					output << machine.ToString() << '\n';
					return true;
				}
			}, {
				"Refill",
				"Refills machine. Args: <new ball count>",
				[&](CArguments & args, std::ostream &)
				{
					machine.Refill(args.Pop<int>());
					return true;
				}
			}, {
				"Help",
				"Displays help",
				[this](CArguments &, std::ostream & output)
				{
					for (auto & item: GetItems())
					{
						output << item.name << ": " << item.description << '\n';
					}
					return true;
				}
			}, {
				"Exit",
				"Returns to main menu",
				[](CArguments &, std::ostream &)
				{
					return false;
				}
			}
		}
	{}
};
