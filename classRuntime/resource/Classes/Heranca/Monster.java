
public class Monster {

	private int life;
	private int strenght;
	
	public Monster(int life, int strenght) {
		super();
		this.life = life;
		this.strenght = strenght;
	}
	public int getLife() {
		return life;
	}
	public void setLife(int life) {
		this.life = life;
	}
	public int getStrenght() {
		return strenght;
	}
	public void setStrenght(int strenght) {
		this.strenght = strenght;
	}
	
	public void attack()
	{
		System.out.println("Monster attacks with "+getStrenght());
	}
	
	
}
