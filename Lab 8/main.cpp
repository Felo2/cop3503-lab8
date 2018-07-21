#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <conio.h>
typedef unsigned int uint;
using namespace std;

// Inventory Struct
struct Inventory
{
	string invName;
	uint cost;
	float weight;
};

// Hero struct
struct Hero
{
	string name;
	short strength, intelligence, agility;
	uint hp, maxHP;
	float armor, magicArmor;
	vector<Inventory> inventory;
};

// Display Hero helper function
void DisplayHero(Hero &hero)
{
	cout << "Name: " << hero.name << endl;
	cout << "Str: " << hero.strength << endl;
	cout << "Int: " << hero.intelligence << endl;
	cout << "Agi: " << hero.agility << endl;
	cout << "HP: " << hero.hp << " / " << hero.maxHP << endl;
	cout << "Armor: " << hero.armor * 100 << "%" << endl;
	cout << "Magic armor: " << hero.magicArmor * 100 << "%" << endl;
	cout << "Inventory: " << endl;

	if (hero.inventory.size() != 0)
	{
		for (uint i = 0; i < hero.inventory.size(); i++)
		{
			cout << "   " << hero.inventory.at(i).invName << ", "
				<< hero.inventory.at(i).cost << ", "
				<< hero.inventory.at(i).weight << endl;
		}
	}
	else
	{
		cout << "   Inventory empty." << endl;
	}
	cout << endl;
}

// LoadHero function
void LoadHeroFile(vector<Hero> &heroes, int fileNum)
{
	// Open the file
	ifstream file("SAMPLE_heroes.dat", ios_base::binary);

	if (file.is_open())
	{
	
		// Read total count of characters
		uint count;
		file.read((char*)&count, 4);

		// Loop for count many times to save all characters
		for (uint i = 0; i < count; i++)
		{
			// Intialize all vars
			Hero hero;
			uint nameLength;
			uint invCount = 0;

			// Read length of name
			file.read((char *)&nameLength, 4);

			// Create char array of namelength and read the name
			char* name = new char[nameLength];
			for (uint i = 0; i < nameLength; i++)
			{
				file.read(&name[i], 1);
			}
			hero.name = name;
			delete name;

			// Read Strength, Int and Agi shorts
			file.read((char *)&hero.strength, 2);
			file.read((char *)&hero.intelligence, 2);
			file.read((char *)&hero.agility, 2);

			// Read HP and Max HP
			file.read((char *)&hero.hp, 4);
			file.read((char *)&hero.maxHP, 4);

			// Read Armor and Magic Armor
			file.read((char *)&hero.armor, 4);
			file.read((char *)&hero.magicArmor, 4);

			// Get the inv count
			file.read((char *)&invCount, 4);
			// If inv count > 0 then initiate for loop to read items
			if (invCount > 0)
			{
				Inventory inv;
				for (uint i = 0; i < invCount; i++)
				{
					// Read length of name
					file.read((char *)&nameLength, 4);

					// Create char array of namelength and read the name
					char* name = new char[nameLength];
					for (uint i = 0; i < nameLength; i++)
					{
						file.read(&name[i], 1);
					}
					inv.invName = name;
					delete name;

					//	Read inventory item cost
					file.read((char *)&inv.cost, 4);

					//	Read inventory item weight
					file.read((char *)&inv.weight, 4);

					hero.inventory.push_back(inv);
				}
			}

			heroes.push_back(hero);

		}
		

		file.close();
	}

}

// Print all heroes
void PrintAllHeroes(vector<Hero> &heroes)
{
	for (uint i = 0; i < heroes.size(); i++)
	{
		DisplayHero(heroes.at(i));
	}
}




int main()
{
	cout << "Which file(s) to open?\n";
	cout << "1. fantasyheroes.dat" << endl;
	cout << "2. superheroes.dat" << endl;
	cout << "3. Both files" << endl;
	int option;
	cin >> option;

	// Create vector of heroes
	vector<Hero> heroes;
	/* Load hero files here */
	switch (option)
	{
	case 1:
		LoadHeroFile(heroes, 1);
		break;
	default:
		break;
	}

	cout << "1. Print all heroes" << endl;
	cout << "2. Hero with the most items" << endl;
	cout << "3. Strongest hero" << endl;
	cout << "4. Heroes with greater than 18 intelligence" << endl;
	cout << "5. 2 clumsiest heroes" << endl;
	cout << "6. Hero with the most valuable stuff" << endl << endl;

	cin >> option;

	/* Work your magic here */
	switch (option)
	{
	case 1:
		PrintAllHeroes(heroes);
	default:
		break;
	}

	_getch();

	return 0;
}