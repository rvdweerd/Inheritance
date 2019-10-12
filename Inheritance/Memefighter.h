#pragma once
#include <iostream>
#include <string>
#include <conio.h>
#include <random>

class Dice
{
public:
	int Roll(int nDice)
	{
		int total = 0;
		for (int n = 0; n < nDice; n++)
		{
			total += d6(rng);
		}
		std::cout <<"[" << nDice <<" Dices roll " << total << "]\n";
		return total;
	}
private:
	std::uniform_int_distribution<int> d6 = std::uniform_int_distribution<int>(1, 6);
	std::mt19937 rng = std::mt19937(std::random_device{}());
};

class MemeFighter
{
public:
	virtual ~MemeFighter()
	{
		std::cout << "Destructing MemFighter " << name << std::endl;
	}
	bool IsAlive() const
	{
		return hp > 0;
	}
	void TakeDamage(int pow)
	{
		std::cout << *this << " takes damage of " << pow; 
		hp -= pow;
		std::cout << " and is left with " << hp << " hp." << std::endl;

		if (hp < 0)
		{
			std::cout << *this << " dies." << hp << std::endl;
		}
	}
	std::string GetName() const
	{
		return name;
	}
	friend std::ostream& operator<<(std::ostream& os, const MemeFighter& mf);
	virtual void Tick()
	{
		if (this->IsAlive())
		{
			std::cout << "======================================================newturn\n";
			const int gain = Roll(1);
			std::cout << *this << " recovers " << gain;
			hp += gain;
			std::cout<<" (new hp="<< hp<<")" << std::endl;
		}
	}
	int Roll(int nDice = 1) const
	{
		return dice.Roll(nDice);
	}
	int GetInitiative() const
	{
		std::cout << "Getting intiative on "<<*this;
		return speed + Roll(2);
		
	}
	virtual void SpecialMove(MemeFighter& target) = 0;
	void Punch(MemeFighter& target)
	{
		if (this->IsAlive())
		{
			if (target.IsAlive())
			{
				std::cout << "======================================================newturn\n";
				std::cout << *this << " punches " << target;
				target.TakeDamage(power + Roll(2));
			}
			else
			{
				std::cout << "======================================================newturn\n";
				std::cout << target << " is already dead." << std::endl;
			}
		}
	}
protected:
	MemeFighter(std::string name, int hp, int speed, int power)
		:
		name(name),
		hp(hp),
		speed(speed),
		power(power)
	{}
	void Add(std::string name_append, int hp_add, int speed_add, float power_factor)
	{
		if (this->IsAlive())
		{
			name += name_append;
			hp += hp_add;
			speed += speed_add;
			power = int( power * power_factor);
			
		}
	}
private:
	std::string name;
	int hp;
	int speed;
	int power;
	mutable Dice dice;
};

std::ostream& operator<<(std::ostream& os, const MemeFighter& mf)
{
	os << mf.name << " (hp=" << mf.hp<<", speed="<<mf.speed << ", power=" << mf.power<<")";
	return os;
}

class MemeFrog : public MemeFighter
{
public:
	MemeFrog(std::string name)
		:
		MemeFighter(name, 69, 7, 14)
	{
		std::cout << "Memefrog " << name << " enters the ring.\n";
	}
	~MemeFrog() override
	{
		std::cout << "MemFrog destructed\n";

	}
	void Tick() override
	{
		if (this->IsAlive())
		{
			std::cout << "======================================================newturn\n";
			const int gain = Roll(1);
			std::cout << *this << " recovers " << gain;
			Add("",gain,0,1);
			//std::cout << " (new hp=" << this.hp << ")" << std::endl;

			int damage = Roll(1);
			std::cout << "AIDS hits for ";
			this->TakeDamage(damage);
		}
		if (!this->IsAlive())
		{
			std::cout << *this << " dies.";
		}
	}
	void SpecialMove(MemeFighter& target) override
	{
		if (this->IsAlive())
		{
			if (target.IsAlive())
			{
				std::cout << "======================================================\n";
				if (Roll(1) <= 2)
				{
					std::cout << *this << " Special move succeeded" << std::endl;
					target.TakeDamage(Roll(3) + 20);
				}
				else
				{
					std::cout << *this << " fails to apply Special move" << std::endl;
				}
			}
			else
			{
				std::cout << "======================================================\n";
				std::cout << *this << " is already dead.";
			}
		}
	}
};

class MemeStoner : public MemeFighter
{
public:
	MemeStoner(std::string name)
		:
		MemeFighter(name, 80, 4, 10)
	{
		std::cout << "Memestoner " << name << " enters the ring.\n";
	}
	~MemeStoner() override
	{
		std::cout << "MemStoner destructed\n";

	}
	void SpecialMove(MemeFighter& target) override
	{
		if (this->IsAlive())
		{
			std::cout << "======================================================\n";
			if (Roll() <= 3)
			{
				std::cout << *this << " special move succeeded, added hp (+" << 10 << ") ,speed (+" << 3 << "), power (*" << 69.0f/42.0f << ") \n";
				this->Add("*", 10, 3, 69.0f/42.0f );
			}
			else
			{
				std::cout << *this << " attempted special move failed.\n";
			}
		}
	}
};