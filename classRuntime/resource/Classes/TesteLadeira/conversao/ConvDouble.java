package conversao;

public class ConvDouble{
	public static void main(String [] args){
		int i = 1;
		long l = 2;
		double d = 3.0;
		short s = 4;
		byte b = 5;
		float f = 6.55f;
		
		System.out.println("Conversao para double:");
		d = (double)i;
		System.out.println(d);
		d = (double)l;
		System.out.println(d);
		d = (double)s;
		System.out.println(d);
		d = (double)b;
		System.out.println(d);
		d = (double)f;
		System.out.println(d);
	}
}