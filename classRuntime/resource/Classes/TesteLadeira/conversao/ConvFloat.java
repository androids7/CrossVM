package conversao;

public class ConvFloat{
	public static void main(String [] args){
		int i = 1;
		long l = 2;
		double d = 3.14812877132712;
		short s = 4;
		byte b = 5;
		float f = 6.0f;
		
		System.out.println("Conversao para float:");
		f = (float)l;
		System.out.println(f);
		f = (float)d;
		System.out.println(f);
		f = (float)s;
		System.out.println(f);
		f = (float)b;
		System.out.println(f);
		f = (float)i;
		System.out.println(f);
		
	}
}