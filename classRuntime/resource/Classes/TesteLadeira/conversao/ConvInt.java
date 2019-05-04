package conversao;

public class ConvInt{
	public static void main(String [] args){
		int i = 1;
		long l = 2;
		double d = 3.0;
		short s = 4;
		byte b = 5;
		float f = 6.0f;
		
		System.out.println("Conversao para int:");
		i = (int)l;
		System.out.println(i);
		i = (int)d;
		System.out.println(i);
		i = (int)s;
		System.out.println(i);
		i = (int)b;
		System.out.println(i);
		i = (int)f;
		System.out.println(i);
		
	}
}