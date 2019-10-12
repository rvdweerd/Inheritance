#include "Memefighter.h"
#include <algorithm>
#include <vector>
#include <random>

void TakeWeaponIfDead(MemeFighter& taker, MemeFighter& giver)
{
	if (taker.IsAlive() && !giver.IsAlive() && giver.HasWeapon())
	{
		if (taker.GetWeapon().GetRank() < giver.GetWeapon().GetRank())
		{
			std::cout << taker << " takes the " << giver.GetWeapon().GetName() << " from " << giver << "'s still cooling body.\nOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO\n";
			taker.GiveWeapon(giver.PilferWeapon());
		}
	}
}

void Engage( MemeFighter& f1,MemeFighter& f2 )
{
	// pointers for sorting purposes
	auto* p1 = &f1;
	auto* p2 = &f2;
	// determine attack order
	if( p1->GetInitiative() < p2->GetInitiative() )
	{
		std::swap( p1,p2 );
	}
	// execute attacks
	p1->Attack( *p2 );
	TakeWeaponIfDead(*p1, *p2);
	p2->Attack( *p1 );
	TakeWeaponIfDead(*p2, *p1);
}
void EngageSpecial(MemeFighter& f1, MemeFighter& f2)
{
	// pointers for sorting purposes
	auto* p1 = &f1;
	auto* p2 = &f2;

	// determine attack order
	if (p1->GetInitiative() < p2->GetInitiative())
	{
		std::swap(p1, p2);
	}
	// execute attacks
	p1->SpecialMove(*p2);
	TakeWeaponIfDead(*p1, *p2);
	p2->SpecialMove(*p1);
	TakeWeaponIfDead(*p2, *p1);

}

int main()
{
	Weapon* pW = new Fist();

	std::vector<MemeFighter*> team1 = { 
		new MemeFrog{"M Kermit The Frog", new Knife{} },
		new MemeStoner("M Sharon Stone", new Fist ), 
		new MemeStoner("M Sylvester Stonone", new Bat ) };
	std::vector<MemeFighter*> team2 = { 
		new MemeFrog("P Boris Frogston", new Knife()), 
		new MemeFrog("P Trump The Frog", new Fist()), 
		new MemeFrog("P Rutte The Frog", new Bat()) };

	const auto alive_pred = [](MemeFighter* mf)->bool {return mf->IsAlive(); };
	while(
		std::any_of(team1.begin(),team1.end(), alive_pred) && 
		std::any_of(team2.begin(), team2.end(), alive_pred) )
	{
		
		//Shufffle teams
		std::random_shuffle(team1.begin(), team1.end()); 
		std::random_shuffle(team2.begin(), team2.end());
		//partition teams
		std::partition(team1.begin(), team1.end(), alive_pred);
		std::partition(team2.begin(), team2.end(), alive_pred);
		
		//fight!
		//for (auto it1 = team1.begin(), it2 = team2.begin(); it1!=team1.end() && (*it1)->IsAlive(); ++it1, ++it2)
		//{
		//	Engage(**it1, **it2);
		//	EngageSpecial(**it1, **it2);
		//}
		for (size_t i = 0; i < team1.size(); i++)
		{
			std::cout << "\n...1-on-1 begins....................................................\n";
			std::cout <<   "....................................................................\n";
			if (team1[i]->IsAlive())
			{
				Engage(*team1[i], *team2[i]);
				EngageSpecial(*team1[i], *team2[i]);
			}
			std::cout << "...1-on-1 ends......................................................\n"; 
			std::cout << "....................................................................\n";
		}
				
		// end of turn maintainence
		std::cout << "\n...End of turn action begins......................................\n";
		std::cout << "....................................................................\n";
		//for (auto it1 = team1.begin(); it1 != team1.end() && (*it1)->IsAlive(); ++it1)
		//{
		//	(*it1)->Tick();
		//}
		//for (auto it2 = team2.begin(); it2 != team2.end() && (*it2)->IsAlive(); ++it2)
		//{
		//	(*it2)->Tick();
		//}
		for (size_t i = 0; i < team1.size(); i++)
		{
			team1[i]->Tick();
			team2[i]->Tick();
		}
		std::cout << "...End of turn action ends..........................................\n";
		std::cout << "....................................................................\n";


		std::cout << "Press any key to continue...";
		while( !_kbhit() );
		_getch();
		std::cout << std::endl << std::endl;
	}

	if( std::any_of(team1.begin(),team1.end(), alive_pred ) )
	{
		std::cout << "Team 1 is victorious!, with"<< *team1[0] << *team1[1] << *team1[2]<<std::endl;
		std::cout << "Team 2: "<< *team2[0] << *team2[1] << *team2[2] << std::endl;
	}
	else
	{
		std::cout << "Team 2 is victorious!, with" << *team2[0] << *team2[1] << *team2[2] << std::endl;
		std::cout << "Team 1: " << *team1[0] << *team1[1] << *team1[2] << std::endl;

	}

	//Free the memory
	//for (MemeFighter* m : team1)
	//{
	//	delete m;
	//}
	//for (MemeFighter* m : team2)
	//{
	//	delete m;
	//}
	for (size_t i = 0; i < team1.size(); i++)
	{
		delete team1[i];
		delete team2[i];
	}

	while( !_kbhit() );
	return 0;
}