package Characters;

public class Character {
	
	private String Name;
	private int level;
	private int health;		//	points of life
	private int armorClass;	//	Protection's value
	private int strength;	//	attack power
	private int resistance;	//	defense
	private int exp;		// amount experience if hero defeat monster
	
	public Character(String n)
	{
		this.setName(n);
	}

	/*	GETTERS & SETTERS	*/
	public String getName() {
		return Name;
	}

	public void setName(String name) {
		Name = name;
	}

	public int getLevel() {
		return level;
	}

	public void setLevel(int level) {
		this.level = level;
	}

	public int getHealth() {
		return health;
	}

	public void setHealth(int health) {
		this.health = health;
	}

	public int getArmorClass() {
		return armorClass;
	}

	public void setArmorClass(int armorClass) {
		this.armorClass = armorClass;
	}

	public int getStrength() {
		return strength;
	}

	public void setStrength(int strength) {
		this.strength = strength;
	}

	public int getResistance() {
		return resistance;
	}

	public void setResistance(int resistance) {
		this.resistance = resistance;
	}

	public int getExp() {
		return exp;
	}
	
	/*	END GETTERS & SETTERS	*/
	
	/*	METHODS	*/
	public void InitMonster(Races race)
	{
		switch(race)
		{
		case Goblin:
			initGoblins();
			break;
		case Hobgoblins:
			System.out.println("Je suis un hobgobelin");
			break;
		case Human:
			System.out.println("Je suis un humain");
		}
	}
	
	/*	Because Goblin are too weak, there are -1 for Strength, Health & Resistance	*/
	public void initGoblins()
	{
		System.out.println("Je suis un gobelin");
		this.level = 1;
		this.health = RandomValues(1, 6) - 1; 		//	points of life
		if(this.health <= 0)
			this.health = 1;
		armorClass = 12;							//	Protection's value
		this.strength = RandomValues(1, 6) - 1;		//	attack power
		if(this.strength <= 0)
			this.strength = 1;
		this.resistance = RandomValues(1, 6) - 1;	//	defense
		if(this.resistance <= 0)
			this.resistance = 1;
		this.exp = 10;								
	}
	/*	Random for Characters & Fights	*/
	int RandomValues(int Minimum, int Maximum)
	{
		return (int)(Math.random() * (Maximum-Minimum)) + Minimum;
	}
}
