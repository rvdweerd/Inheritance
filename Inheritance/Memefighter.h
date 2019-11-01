#pragma once
#include <iostream>
#include <string>
#include <conio.h>
#include <random>
#include "Weapon.h"
#include <memory>

class MemeFighter
{
public:
	virtual ~MemeFighter()
	{
		std::cout << "Destructing MemFighter " << name << std::endl;
		delete pWeapon;
		pWeapon = nullptr;
	}
	std::string GetName() const
	{
		return name;
	}
	bool IsAlive() const
	{
		return attr.hp > 0;
	}
	int GetInitiative() const
	{
		std::cout << "Getting intiative on "<<*this;
		return attr.speed + Roll(2);
		
	}
	void Attack(MemeFighter& target)
	{
		if (this->IsAlive())
		{
			if (target.IsAlive())
			{
				std::cout << "======================================================newturn\n";
				std::cout << *this << " attacks " << target << " with a "<<pWeapon->GetName();
				ApplyDamageTo( target, pWeapon->CalculateDamage(attr,dice ));
			}
			else
			{
				std::cout << "======================================================newturn\n";
				std::cout << target << " is already dead." << std::endl;
			}
		}
	}
	void ApplyDamageTo(MemeFighter& target, int damage) const
	{
		std::cout << target << " takes damage of " << damage;
		target.attr.hp -= damage;
		std::cout << " and is left with " << target.attr.hp << " hp." << std::endl;

		if (target.attr.hp < 0)
		{
			std::cout << target << " dies." << std::endl;
		}

	}
	friend std::ostream& operator<<(std::ostream& os, const MemeFighter& mf);
	virtual void Tick()
	{
		if (this->IsAlive())
		{
			std::cout << "======================================================newturn\n";
			const int gain = Roll(1);
			std::cout << *this << " recovers " << gain;
			attr.hp += gain;
			std::cout<<" (new hp="<< attr.hp<<")" << std::endl;
		}
	}
	virtual void SpecialMove(MemeFighter& target) = 0;
	bool HasWeapon() const
	{
		return pWeapon != nullptr;
	}
	const Weapon& GetWeapon() const
	{
		return *pWeapon;
	}
	void GiveWeapon(Weapon* pNewWeapon)
	{
		delete pWeapon;
		pWeapon = pNewWeapon;
	}
	Weapon* PilferWeapon()
	{
		auto pWep = pWeapon;
		pWeapon = nullptr;
		return pWep;
	}
protected:
	MemeFighter(const std::string& name, int hp, int speed, int power, Weapon* pWeapon = nullptr)
		:
		name(name),
		attr({ hp,speed,power }),
		pWeapon(pWeapon)
	{
		//pWeapon = new Knife();
	}
	//void Add(std::string name_append, int hp_add, int speed_add, float power_factor)
	//{
	//	if (this->IsAlive())
	//	{
	//		name += name_append;
	//		attr.hp += hp_add;
	//		attr.speed += speed_add;
	//		attr.power = int( attr.power * power_factor);
	//		
	//	}
	//}
	std::string name;
	Attributes attr;
	int Roll(int nDice = 1) const
	{
		return dice.Roll(nDice);
	}
private:
	Weapon* pWeapon = nullptr;
	mutable Dice dice;
};

std::ostream& operator<<(std::ostream& os, const MemeFighter& mf)
{
	os << mf.name << " (hp=" << mf.attr.hp<<", speed="<<mf.attr.speed << ", power=" << mf.attr.power<<")";
	return os;
}

class MemeFrog : public MemeFighter
{
public:
	MemeFrog(const std::string& name, Weapon* pWeapon = nullptr)
		:
		MemeFighter(name, 69, 7, 14, pWeapon )
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
			attr.hp += gain;

			int damage = Roll(1);
			std::cout << "AIDS hits for ";
			attr.hp -= damage;
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
					ApplyDamageTo(target, Roll(3) + 20);
				}
				else
				{
					std::cout << *this << " fails to apply Special move" << std::endl;
				}
			}
			else
			{
				std::cout << "======================================================\n";
				std::cout << target << " is already dead.";
			}
		}
	}
};

class MemeStoner : public MemeFighter
{
public:
	MemeStoner(const std::string& name, Weapon* pWeapon = nullptr)
		:
		MemeFighter(name, 80, 4, 10, pWeapon )
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
				name += "*";
				attr.hp += 10;
				attr.speed += 3;
				attr.power = int (attr.power + 69.0f / 42.0f);
			}
			else
			{
				std::cout << *this << " attempted special move failed.\n";
			}
		}
	}
};
