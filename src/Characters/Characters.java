/*	By Lethael
 * 		Characters = monsters
 */

package Characters;

public class Characters {
	
	protected String Name;
	protected int level;
	protected int health;		//	points of life
	protected int armorClass;	//	Protection's value
	protected int strength;	//	attack power
	protected int resistance;	//	defense
	protected int exp;		// amount experience if hero defeat monster
	
	public Characters()
	{
		Name = "Undefined";
	}
	
	public Characters(String n)
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
	public void initMonster(Races race)
	{
		switch(race)
		{
		case Goblin:
			initGoblins();
			break;
		case Hobgoblins:
			initHobgoblins();
			break;
		case Human:
			initHumans();
		}
	}
	/*	INIT MONSTERS	*/
	/**
	 * Because Goblins are too weaks, they looses 1 from Strength, Health & Resistance
	 */
	public void initGoblins()
	{
		System.out.println("Je suis un gobelin");
		this.level = 1;
		this.health = RandomValues(1, 7) - 1; 		//	points of life
		if(this.health <= 0)
			this.health = 1;
		armorClass = 12;							//	Protection's value
		this.strength = RandomValues(1, 7) - 1;		//	attack power
		if(this.strength <= 0)
			this.strength = 1;
		this.resistance = RandomValues(1, 7) - 1;	//	defense
		if(this.resistance <= 0)
			this.resistance = 1;
		this.exp = 10;								
	}
	
	public void initHobgoblins()
	{
		System.out.println("Je suis un Hobgobelin");
		this.level = 1;
		this.health = RandomValues(1, 7) + 1; 		//	points of life
		armorClass = 14;							//	Protection's value
		this.strength = RandomValues(1, 7) + 1;		//	attack power
		this.resistance = RandomValues(1, 7) + 1;	//	defense
		if(this.resistance <= 0)
			this.resistance = 1;
		this.exp = 17;								
	}
	
	public void initHumans()
	{
		System.out.println("Je suis un Humain");
		this.level = 1;
		this.health = RandomValues(1, 7); 		//	points of life
		armorClass = 13;							//	Protection's value
		this.strength = RandomValues(1, 7);		//	attack power
		this.resistance = RandomValues(1, 7);	//	defense
		if(this.resistance <= 0)
			this.resistance = 1;
		this.exp = 14;								
	}
	/*	END INIT MONSTERS	*/
	/**
	 * 
	 * @param Minimum
	 * @param Maximum
	 * @return random between Minimum & Maximum
	 * Random for monster's & hero's attributes
	 * & fights
	 */
	int RandomValues(int Minimum, int Maximum)
	{
		return (int)(Math.random() * (Maximum-Minimum)) + Minimum;
	}
}
