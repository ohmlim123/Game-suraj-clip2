#pragma once
class AttributeComponent
{
public:
	//Leveling 
	int level;
	int exp;
	int expNext;
	int atrributePoints;


	//Attributes
	int vitality;
	int strength;
	int dexterity;
	int agility;
	int intelligence;

	//Stats
	int hp;
	int hpMax;
	int damageMin;
	int damageMax;
	int accuracy;
	int defence;
	int luck;


	//Constructor / Destructor
	
	AttributeComponent(int level);
	virtual ~AttributeComponent();

	//funstion

	std::string debugPrint() const;

	void gainExp(const int exp);

	void updateStats(const bool reset);
	void updateLevel();

	void update();
};

