package algoritmo;

public class Fibonacci{
	
	public static int fibo(int n){
		if(n == 0){
			return 0;
		}else{
			if(n == 1){
				return 1;
			}else{
				return fibo(n-1)+fibo(n-2);
			}
		}
	}

	public static void main(String [] args){
		System.out.println("Fibonacci:");
		for(int i=0; i< 11; i++){
			System.out.println(fibo(i));
		}
		
	}
}
