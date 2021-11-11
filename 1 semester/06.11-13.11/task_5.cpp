#include<iostream>

class Soldier
{
public:
	static bool fight(Soldier* one, Soldier* other)
	{
		while (one->HP > 0 && other->HP > 0)
		{
			one->shoot(other);
			other->shoot(one);
		}
		if (one->HP > 0) return true;
		else return false;
	}
	virtual ~Soldier() = 0;
	unsigned int HP;
protected:
	virtual void shoot(Soldier* other) = 0;
};

class Bazooka_man :public Soldier
{
public:
	Bazooka_man() { HP = 500; };
	virtual ~Bazooka_man() = default;
	virtual void shoot(Soldier* other) override
	{
		other->HP -= 100;
	}
};

class Revolver_man :public Soldier
{
public:
	Revolver_man() { HP = 300; };
	virtual ~Revolver_man() = default;
	virtual void shoot(Soldier* other) override
	{
		other->HP -= 20;
	}
};

template<class Derived>
class Soldier1
{
public:
	template<class Derived1>
	bool fight(Soldier1<Derived1>* other)
	{
		while (this->HP > 0 && other->HP > 0)
		{
			static_cast<Derived*>(this)->shoot(other);
			static_cast<Derived1*>(other)->shoot(this);
		}
		if (this->HP > 0) return true;
		else return false;
	}
	unsigned int HP;
};

class Bazooka_man1 :public Soldier1<Bazooka_man1>
{
	friend Soldier1;
public:
	template<class Derived1>
	void shoot(Soldier1<Derived1>* other)
	{
		other->HP -= 100;
	}
};

class Revolver_man1 :public Soldier1<Revolver_man1>
{
	friend Soldier1;
public:
	template<class Derived1>
	void shoot(Soldier1<Derived1>* other)
	{
		other->HP -= 20;
	}
};

int main()
{
	Soldier* soldier1 = new Revolver_man();
	Soldier* soldier2 = new Bazooka_man();
	std::cout << std::boolalpha << Soldier::fight(soldier1, soldier2) << std::endl;
	delete soldier1, soldier2;

	Soldier1<Revolver_man1>* soldier3 = new Soldier1<Revolver_man1>;
	Soldier1<Bazooka_man1>* soldier4 = new Soldier1<Bazooka_man1>;
	std::cout << std::boolalpha << soldier3->fight(soldier4) << std::endl;
	delete soldier3, soldier4;
}
/*
* MixIn Позволяет избегать повторяющегося кода, локализовывать функциональность
* в небольших классах и впоследствии микшировать их в нужную в данный момент смесь.
* Но данный метод также в некоторых случаях, например для сохранения инкапсуляции,
* требует создавать новые классы, что не всегда удобно. Также программировать
* классическими методами иногда проще.
*/