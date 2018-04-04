package Main;

import Characters.Races;
import Exceptions.ExceptionsCharacters;
import Characters.Character;
import Characters.Heros;
public class Rpg {

	public static void main(String[] args) throws ExceptionsCharacters {
		/*	Actually, some tests	*/
		Races gobelin = Races.Goblin;
		Races hobgobelin = Races.Hobgoblins;
		Races human = Races.Human;
		
		Character gob = null;
		Character hob = null;
		Character hum = null;
		Heros hero = null;
		try {
			gob = new Character("Arzig");
			hob = new Character("Azog");
			hum = new Character("Vilain");
			hero = new Heros("Player");
		}catch (NullPointerException e){
			System.out.println("un des objets véhicules est resté à null");
		}
		
		/*	Testing random values	*/
		for(int i = 0; i < 100; i++) {
			gob.initMonster(gobelin);
			System.out.println("Force : " + gob.getStrength());
			System.out.println("Resistance : " + gob.getResistance());
			System.out.println("Health : " + gob.getHealth());
		}
		
		for(int i = 0; i < 100; i++) {
			hob.initMonster(hobgobelin);
			System.out.println("Force : " + hob.getStrength());
			System.out.println("Resistance : " + hob.getResistance());
			System.out.println("Health : " + hob.getHealth());
		}
		
		for(int i = 0; i < 100; i++) {
			hum.initMonster(human);
			System.out.println("Force : " + hum.getStrength());
			System.out.println("Resistance : " + hum.getResistance());
			System.out.println("Health : " + hum.getHealth());
		}
		
		for(int i = 0; i < 100; i++) {
			hero.initHero();
			System.out.println("New challenger !!!");
			System.out.println("Force : " + hero.getStrength());
			System.out.println("Resistance : " + hero.getResistance());
			System.out.println("Health : " + hero.getHealth());
			System.out.println("Bonus Res : " + hero.getResBonus());
			System.out.println("Bonus str : " + hero.getStrBonus());
			System.out.println("Armor Class : " + hero.getArmorClass());
		}
		
		
		gob = null;
		hob = null;
		hum = null;
		hero = null;
		
		gobelin = null;
		hobgobelin = null;
		human = null;

	}
}