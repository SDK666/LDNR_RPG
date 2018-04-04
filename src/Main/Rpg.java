package Main;

import Characters.Races;
import Characters.Character;
public class Rpg {

	public static void main(String[] args) {
		Races gobelin = Races.Goblin;
		Character gob = new Character("Arzig");
		gob.InitMonster(gobelin);
		
	}

}
