package Main;

import Characters.Races;
import Exceptions.ExceptionsCharacters;
import Characters.Character;
public class Rpg {

	public static void main(String[] args) throws ExceptionsCharacters {
		/*	Actually, some tests	*/
		Races gobelin = Races.Goblin;
		Character gob = null;
		
		try {
			gob = new Character("Arzig");			
		}catch (NullPointerException e){
			System.out.println("un des objets véhicules est resté à null");
		}
		
		for(int i = 0; i < 100; i++) {
			gob.InitMonster(gobelin);
			System.out.println("Force : " + gob.getStrength());
			System.out.println("Resistance : " + gob.getResistance());
			System.out.println("Health : " + gob.getHealth());
		}
		gob = null;
		gobelin = null;


	}
}
