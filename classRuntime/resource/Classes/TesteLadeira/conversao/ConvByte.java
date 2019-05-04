package conversao;

public class ConvByte{
	public static void main(String [] args){
		int i = 1;
		long l = 2;
		double d = 3.0;
		short s = 4;
		byte b = 5;
		float f = 6.0f;
		
		System.out.println("Conversao para byte:");
		b = (byte)l;
		System.out.println(b);
		b = (byte)d;
		System.out.println(b);
		b = (byte)s;
		System.out.println(b);
		b = (byte)i;
		System.out.println(b);
		b = (byte)f;
		System.out.println(b);
	}
}