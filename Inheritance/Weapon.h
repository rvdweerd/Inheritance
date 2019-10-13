#pragma once

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
		std::cout << "[" << nDice << " Dices roll " << total << "]\n";
		return total;
	}
private:
	std::uniform_int_distribution<int> d6 = std::uniform_int_distribution<int>(1, 6);
	std::mt19937 rng = std::mt19937(std::random_device{}());
};

struct Attributes
{
	int hp;
	int speed;
	int power;
};

class Weapon
{
public:
	virtual const std::string& GetName() const = 0;
	virtual const int GetRank() const = 0;
	virtual int CalculateDamage(const Attributes& attr, Dice& d) const = 0;
	virtual ~Weapon()
	{}
protected:
	Weapon(std::string name, int rank)
		:
		name(name),
		rank(rank)
	{}
protected:
	std::string name;
	int rank;
};

class Fist : public Weapon
{
public:
	Fist()
		:
		Weapon("Fist", 0)
	{}
	~Fist() override = default;
	virtual const std::string& GetName() const override
	{
		return name;
	}
	virtual const int GetRank() const override
	{
		return rank;
	}
	virtual int CalculateDamage(const Attributes& attr, Dice& d) const override
	{
		return attr.power + d.Roll(2);
	}
};

class Knife : public Weapon
{
public:
	Knife()
		:
		Weapon("Knife", 2)
	{}
	~Knife() override = default;
	virtual const std::string& GetName() const override
	{
		return name;
	}
	virtual const int GetRank() const override
	{
		return rank;
	}
	int CalculateDamage(const Attributes& attr, Dice& d) const override
	{
		return attr.speed * 3 + d.Roll(3);
	}
};

class Bat : public Weapon
{
public:
	Bat()
		:
		Weapon("Bat", 1)
	{}
	~Bat() override = default;
	virtual const std::string& GetName() const override
	{
		return name;
	}
	virtual const int GetRank() const override
	{
		return rank;
	}
	int CalculateDamage(const Attributes& attr, Dice& d) const 
	{
		return attr.power*2+d.Roll(1);
	}
};