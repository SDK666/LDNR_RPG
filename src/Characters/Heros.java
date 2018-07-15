/*	By Lethael
 * 		class Hero
 */

package Characters;

import java.util.Scanner;

public class Heros extends Characters {

	private int expNextLevel;
	private int victories;
	
	public Heros()
	{
		super();
		initHero();
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
		Scanner heroName = new Scanner(System.in);
		boolean errorDigit;
		do
		{
			errorDigit = false;
			System.out.println("Veuillez saisir votre nom");
			Name = heroName.nextLine();
			
			for(int i = 0; i < Name.length(); i++)
				if(Character.isDigit(Name.charAt(i))) {
					System.out.println("Veuillez n'inséré que des lettres"); errorDigit = true;}
		}while(Name.isEmpty() || errorDigit == true);
		System.out.println("Vous vous appelez donc : " + Name);
		this.level = 1;
		this.exp = 0;
		this.expNextLevel = 500;
		this.victories = 0;
		
		
		
		this.strength = RandomValues(8, 19); //Between 3 and 18
		this.calculStrengthBonus();
		
		
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
	
	/**
	 * @Lethael
	 * @param monster
	 */
	public void defeatEnemy(Characters monster) {
		if(monster.exp >= this.expNextLevel) {
			this.levelUp(monster);
		}else {
			this.expNextLevel -= monster.exp;
			System.out.println("Vous avez vaincu " + monster.Name);
			System.out.println("Vous avez gagné : " + monster.exp + " points d'expériences");
			System.out.println("Encore " + this.expNextLevel + " avant de monter de niveau");
		}
	}
	
	/**
	 * @Lethael
	 * @param monster
	 * 
	 * Upgrade life point between 1 -> 6
	 * Every 2 lvl upgrade strength by 1
	 */
	public void levelUp(Characters monster) {
		int expSup = monster.exp - this.expNextLevel;
		this.level += 1;
		this.expNextLevel = (500 * (2 * this.level)) - expSup;
		int gainHealth = this.RandomValues(1, 7);
		this.health = gainHealth;
		if(this.level % 2 == 0) {
			this.strength += 1;
			System.out.println("Vous gagnez 1 point de force. ");
			this.calculStrengthBonus();
		}
		System.out.println("Vous avez pris un niveau ! Level : " + this.level);
		System.out.println("Encore " + this.expNextLevel + " avant de monter de niveau");
		System.out.println("Vous gagnez " + gainHealth+ " points de vie");
	}

}

