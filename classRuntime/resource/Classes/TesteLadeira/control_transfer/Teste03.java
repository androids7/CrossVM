/*
 * Testes de if_icmp<cond>
 */
public class Teste03{
	public static void main(String [] args){
		int x;
		int y;
		
		x = 1;
		y = 1;
		if(x == y){
			System.out.println("Valor de X ");
			System.out.println(x);
			System.out.println(" - Valor de Y ");
			System.out.println(y);
			System.out.println("\nX igual a Y\n");
		} else {
			System.out.println("Erro!");
		}
		
		y = 2;
		if(x != y){
			System.out.println("Valor de X ");
			System.out.println(x);
			System.out.println(" - Valor de Y ");
			System.out.println(y);
			System.out.println("\nX diferente de Y\n");
		} else {
			System.out.println("Erro!");
		}
		
		if(x < y){
			System.out.println("Valor de X ");
			System.out.println(x);
			System.out.println(" - Valor de Y ");
			System.out.println(y);
			System.out.println("\nX menor que Y\n");
		} else {
			System.out.println("Erro!");
		}
		
		y = 1;
		if(x <= y){
			System.out.println("Valor de X ");
			System.out.println(x);
			System.out.println(" - Valor de Y ");
			System.out.println(y);
			System.out.println("\nX menor ou igual a Y\n");
		} else {
			System.out.println("Erro!");
		}
		
		x = 2;
		if(x > y){
			System.out.println("Valor de X ");
			System.out.println(x);
			System.out.println(" - Valor de Y ");
			System.out.println(y);
			System.out.println("\nX maior que Y\n");			
		} else {
			System.out.println("Erro!");						
		}
		
		x = 1;
		if(x > y){
			System.out.println("Valor de X ");
			System.out.println(x);
			System.out.println(" - Valor de Y ");
			System.out.println(y);
			System.out.println("\nX maior ou igual a Y\n");			
		} else {
			System.out.println("Erro!");						
		}
		
		
		
		
	}
}
