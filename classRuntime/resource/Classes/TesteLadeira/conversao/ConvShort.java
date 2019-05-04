package conversao;

public class ConvShort{
	public static void main(String [] args){
		int i = 1;
		long l = 2;
		double d = 3.0;
		short s = 4;
		byte b = 5;
		float f = 6.0f;
		
		System.out.println("Conversao para int:");
		s = (short)l;
		System.out.println(s);
		s = (short)d;
		System.out.println(s);
		s = (short)i;
		System.out.println(s);
		s = (short)b;
		System.out.println(s);
		s = (short)f;
		System.out.println(s);
		
	}
}