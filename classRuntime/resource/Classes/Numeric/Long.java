public class Long {

	private long myLong;

	private void add19() {
		myLong += 19l;
	}

	public Long() {
		myLong = 19l;
	}

	public static void main(String[] args) {
		Long longObject = new Long();
		System.out.print(longObject.myLong);
		System.out.print("\n");
		longObject.add19();
		System.out.println(longObject.myLong);
	}

}
