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
	protected int exp;
	protected int strBonus;	//	strenght bonus if str >= 13
	protected int resBonus;	//	resistance bonus if resistance >= 13// amount experience if hero defeat monster
	
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
		this.armorClass = 12;							//	Protection's value
		this.strength = RandomValues(1, 7) - 1;		//	attack power
		if(this.strength <= 0)
			this.strength = 1;
		this.resistance = RandomValues(1, 7) - 1;	//	defense
		if(this.resistance <= 0)
			this.resistance = 1;
		this.exp = 10;
		this.resBonus = 0;
		this.strBonus = 0;
	}
	
	public void initHobgoblins()
	{
		System.out.println("Je suis un Hobgobelin");
		this.level = 1;
		this.health = RandomValues(1, 7) + 1; 		//	points of life
		this.armorClass = 14;							//	Protection's value
		this.strength = RandomValues(1, 7) + 1;		//	attack power
		this.resistance = RandomValues(1, 7) + 1;	//	defense
		if(this.resistance <= 0)
			this.resistance = 1;
		this.exp = 17;	
		this.resBonus = 0;
		this.strBonus = 0;
	}
	
	public void initHumans()
	{
		System.out.println("Je suis un Humain");
		this.level = 1;
		this.health = RandomValues(1, 7); 		//	points of life
		this.armorClass = 13;							//	Protection's value
		this.strength = RandomValues(1, 7);		//	attack power
		this.resistance = RandomValues(1, 7);	//	defense
		if(this.resistance <= 0)
			this.resistance = 1;
		this.exp = 14;	
		this.resBonus = 0;
		this.strBonus = 0;
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
	
	/**
	 * @Lethael
	 */
	public void calculStrengthBonus () {
		int bonus = 0;

		if(this.strength >= 13 && this.strength <=15 && this.strBonus != 1) {
			bonus = 1;
		}
		else if(this.strength >= 16 && this.strength <=17 && this.strBonus != 2) {
			bonus = 2;
		}
		else if(this.strength == 18 && this.strBonus != 3) {
			bonus = 3;
		}
		else
			this.strBonus = 0;
		
		if(bonus > this.strBonus) {
			this.strBonus = bonus;
			System.out.println("Vous gagnez " + bonus + " en bonus de force");
		}
		
	}
	
	/**
	 * @Lethael
	 * Like calculStrengthBonus 
	 */
	public void calculResBonus() {
		int bonus = 0;
		/*	Attribute Resitance Bonus if random is better than 13	*/
		if(this.resistance >= 13 && this.resistance <=15)
			bonus = 1;
		else if(this.resistance >= 16 && this.resistance <=17)
			bonus = 2;
		else if(this.resistance == 18)
			bonus = 3;
		else
			this.resBonus = 0;
		
		if(bonus > this.resBonus) {
			this.resBonus = bonus;
			System.out.println("Vous gagnez " + bonus + " en bonus de resistance");
		}
	}
	
	public void damageMonster(Heros hero) {
		int toHit = RandomValues(1, 21) + this.strBonus;
		
		if(toHit >= hero.armorClass) {
			int damage = this.RandomValues(1, 7) + this.strBonus;
			
			if(toHit >= 19) {
				System.out.println(this.Name + " vous attaque et fait... " + toHit);
				System.out.println("Attaque CRITIQUE !" + this.Name + " vous frappe de toutes ses forces!");
				System.out.println("Vos os se brisent sous l'impact de ses coups");
				damage += 6;
				System.out.println("Il vous fait " + damage + " de dégâts");
			}else {
				System.out.println(this.Name + "vous attaque et fait... " + toHit);
				System.out.println("Il vous fait " + damage + " de dégâts");
			}
			hero.health -= damage;
		}else {
			System.out.println(this.Name + " vous rate complétement...");
		}
	}
	
	
}
