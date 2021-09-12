#include <cassert>
#include <functional>
#include <iostream>

using namespace std;

using FlyStrategy = function<void()>;
void FlyWithWings()
{
	cout << "I'm flying with wings!!" << endl;
}
void FlyNoWay() {}

using QuackStrategy = function<void()>;
void QuackBehavior()
{
	cout << "Quack Quack!!!" << endl;
}
void SqueakBehavior()
{
	cout << "Squeek!!!" << endl;
}
void MuteQuackBehavior() {}

class Duck
{
public:
	Duck(FlyStrategy&& flyStrategy,
		QuackStrategy&& quackStrategy)
		: m_quackStrategy(move(quackStrategy))
	{
		assert(m_quackStrategy);
		SetFlyStrategy(move(flyStrategy));
	}
	void Quack() const
	{
		m_quackStrategy();
	}
	void Swim()
	{
		cout << "I'm swimming" << endl;
	}
	void Fly()
	{
		m_flyStrategy();
	}
	virtual void Dance()
	{
		cout << "I'm Dancing" << endl;
	}
	void SetFlyStrategy(FlyStrategy&& flyStrategy)
	{
		assert(flyStrategy);
		m_flyStrategy = move(flyStrategy);
	}
	virtual void Display() const = 0;
	virtual ~Duck() = default;

private:
	FlyStrategy m_flyStrategy;
	QuackStrategy m_quackStrategy;
};

class MallardDuck : public Duck
{
public:
	MallardDuck()
		: Duck(FlyWithWings, QuackBehavior)
	{
	}

	void Display() const override
	{
		cout << "I'm mallard duck" << endl;
	}
};

class RedheadDuck : public Duck
{
public:
	RedheadDuck()
		: Duck(FlyWithWings, QuackBehavior)
	{
	}
	void Display() const override
	{
		cout << "I'm redhead duck" << endl;
	}
};
class DecoyDuck : public Duck
{
public:
	DecoyDuck()
		: Duck(FlyNoWay, MuteQuackBehavior)
	{
	}
	void Display() const override
	{
		cout << "I'm decoy duck" << endl;
	}
	void Dance() override {}
};
class RubberDuck : public Duck
{
public:
	RubberDuck()
		: Duck(FlyNoWay, SqueakBehavior)
	{
	}
	void Display() const override
	{
		cout << "I'm rubber duck" << endl;
	}
	void Dance() override {}
};

class ModelDuck : public Duck
{
public:
	ModelDuck()
		: Duck(FlyNoWay, QuackBehavior)
	{
	}
	void Display() const override
	{
		cout << "I'm model duck" << endl;
	}
	void Dance() override {}
};

void DrawDuck(Duck const& duck)
{
	duck.Display();
}

void PlayWithDuck(Duck& duck)
{
	DrawDuck(duck);
	duck.Quack();
	duck.Fly();
	duck.Dance();
	cout << endl;
}

int main()
{
	MallardDuck mallardDuck;
	PlayWithDuck(mallardDuck);

	RedheadDuck redheadDuck;
	PlayWithDuck(redheadDuck);

	RubberDuck rubberDuck;
	PlayWithDuck(rubberDuck);

	DecoyDuck decoyDuck;
	PlayWithDuck(decoyDuck);

	ModelDuck modelDuck;
	PlayWithDuck(modelDuck);
	modelDuck.SetFlyStrategy(FlyWithWings);
	PlayWithDuck(modelDuck);
}
