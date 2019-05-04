
public enum Testando {

	
	Marco("Marco Antonio Marques", 12),
	Andre("Andre Marques", 13),
	Gabriel ("Gabriel Marques", 14);
	
	private final String name;
	private final int age;
	
	Testando (String nome, int idade)
	{
		name = nome;
		age = idade;
	}

	public String getName() {
		return name;
	}

	public int getAge() {
		return age;
	}
	
	
}
