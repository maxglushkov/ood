#include "CGumballMachineMenu.hpp"
#include "GumBallMachineWithDynamicallyCreatedState.hpp"
#include "GumBallMachineWithState.hpp"
#include "NaiveGumBallMachine.hpp"

using namespace std;

class CAppMenu: public CMenu
{
public:
	CAppMenu()
		:CMenu{
			{
				"Naive",
				"Use naive gumball machine",
				[](CArguments &, std::ostream &)
				{
					naive::CGumballMachine m(5);
					CGumballMachineMenu(m).Run(cin, cout, cerr);
					return true;
				}
			}, {
				"WithState",
				"Use gumball machine with state",
				[](CArguments &, std::ostream &)
				{
					with_state::CGumballMachine m(5);
					CGumballMachineMenu(m).Run(cin, cout, cerr);
					return true;
				}
			}, {
				"WithDynState",
				"Use gumball machine with dynamic state",
				[](CArguments &, std::ostream &)
				{
					with_dynamic_state::CGumballMachine m(5);
					CGumballMachineMenu(m).Run(cin, cout, cerr);
					return true;
				}
			}, {
				"Help",
				"Display help",
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
				"Quit",
				[](CArguments &, std::ostream &)
				{
					return false;
				}
			}
		}
	{}
};

int main()
{
	CAppMenu().Run(cin, cout, cerr);
	return 0;
}
