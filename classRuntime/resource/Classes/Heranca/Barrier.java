
public class Barrier extends Monster {
   
	public Barrier(int life, int strenght)
	{
		super(life, strenght);
		setStrenght(0);
	
	}
	
	public void attack()
	{
		System.out.println("Barrier attacks with "+getStrenght());
	}
	
	public void stay()
	{
		System.out.println("Staying stopped...");
	}
	
}
