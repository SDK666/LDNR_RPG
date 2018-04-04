/*	By Lethael
 * 		Characters = monsters
 */

package Characters;

public class Heros extends Character {

	private int strBonus;	//	strenght bonus if str >= 13
	private int resBonus;	//	resistance bonus if str >= 13
	private int expNextLevel;
	
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
	/*	END GETTERS & SETTERS	*/
	
}

