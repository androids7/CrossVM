public class Float {

	private float number;

	protected void add19() {
		number += 19.0f;
	}

	public Float() {
		number = 19.0f;
	}

	public static void main(String[] args) {
		Float f = new Float();
		System.out.print(f.number);
		System.out.print("\n");
		f.add19();
		System.out.print(f.number);
	}

}
