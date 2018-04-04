package Characters;

public class Character {
	
	private String Name;
	private int level;
	private int health;		//	points of life
	private int armorClass;	//	Protection's value
	private int strength;	//	attack power
	private int resistance;	//	defense
	private int exp;
	
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
			System.out.println("Je suis un gobelin");
			break;
		case Hobgoblins:
			System.out.println("Je suis un hobgobelin");
			break;
		}
	}
	
	/*	Random for Characters & Fights	*/
	int RandomValues(int Minimum, int Maximum)
	{
		return (int)(Math.random() * (Maximum-Minimum)) + Minimum;
	}
}
