package conversao;

public class ConvLong{
	public static void main(String [] args){
		int i = 1;
		long l = 2;
		double d = 3.5;
		short s = 4;
		byte b = 5;
		float f = 6.5f;
		
		System.out.println("Conversao para long:");
		l = (long)i;
		System.out.println(l);
		l = (long)d;
		System.out.println(l);
		l = (long)s;
		System.out.println(l);
		l = (long)b;
		System.out.println(l);
		l = (long)f;
		System.out.println(l);
		
	}
}