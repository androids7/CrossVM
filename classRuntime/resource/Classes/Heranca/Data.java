
public class Data {
		
	public static void main(String[] args) {
		

		
		/*
		System.out.println("Here");
		
		for( Testando t : Testando.values())
		{
			System.out.println("Esse cara tem "+t.getAge()+" anos e se chama " + t.getName());
		}
		
		String carros[] = new String[3];
		carros[0] = new String("wolks");
		carros[1] = "fiat";
		carros[2] = "gm";
		
		for (String nome : carros)
			System.out.println(nome);
		
		
		Perdida perdida = new Perdida();
		perdida.x = 40;
		*/
		
		Monster monster = new Monster(100, 10);
		monster.attack();
		Barrier bar = new Barrier(100, 20);
		bar.attack();
		Monster mb = bar;
		mb.attack();
		bar.stay();
		//bar.setLife(1000);
		System.out.println(mb.getLife());
	}
	
}

class Perdida
{
	int x = 5;
}
