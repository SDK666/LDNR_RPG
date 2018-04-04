/*	By Lethael
 * 		class Hero
 */

package Characters;

public class Heros extends Character {

	private int strBonus;	//	strenght bonus if str >= 13
	private int resBonus;	//	resistance bonus if str >= 13
	private int expNextLevel;
	private int victories;
	
	public Heros()
	{
		super();
	}
	
	public Heros(String n) {
		super(n);
	}

	/*	GETTERS & SETTERS	*/
	public int getStrBonus() {
		return strBonus;
	}

	public void setStrBonus(int strBonus) {
		this.strBonus = strBonus;
	}

	public int getResBonus() {
		return resBonus;
	}

	public void setResBonus(int resBonus) {
		this.resBonus = resBonus;
	}

	public int getExpNextLevel() {
		return expNextLevel;
	}

	public void setExpNextLevel(int expNextLevel) {
		this.expNextLevel = expNextLevel;
	}
	
	public int getVictories() {
		return victories;
	}

	public void setVictories(int victories) {
		this.victories = victories;
	}
	/*	END GETTERS & SETTERS	*/
	
	public void initHero()
	{
		this.level = 1;
		this.exp = 0;
		this.expNextLevel = 500;
		this.victories = 0;
		
		
		
		this.strength = RandomValues(8, 19); //Between 3 and 18
		/*	Attribute Strenght Bonus if random is better than 13	*/
		if(this.strength >= 13 && this.strength <=15)
			this.strBonus = 1;
		else if(this.strength >= 16 && this.strength <=17)
			this.strBonus = 2;
		else if(this.strength == 18)
			this.strBonus = 3;
		else
			this.strBonus = 0;
		/*	########## END STRENGTH ##########	*/
		
		/*	########## BEGIN RESISTANCE ##########	*/
		this.resistance = RandomValues(8, 19);
		/*	Attribute Resitance Bonus if random is better than 13	*/
		if(this.resistance >= 13 && this.resistance <=15)
			this.resBonus = 1;
		else if(this.resistance >= 16 && this.resistance <=17)
			this.resBonus = 2;
		else if(this.resistance == 18)
			this.resBonus = 3;
		else
			this.resBonus = 0;
		/*	########## END RESISTANCE ##########	*/
		
		this.armorClass = 10 + this.resBonus; // + nothing actually. Need to have Armor 
		
		/*	Initialize Health	*/
		this.health = 6 + this.resBonus;
	}

}

