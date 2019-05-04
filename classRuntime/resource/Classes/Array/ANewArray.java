public class ANewArray {

	public static void main(String[] args) {

		Dog[] d = new Dog[10];

		for(int i=0; i<d.length; i++) {
			d[i] = new Dog(i);
		}

		for(int i=0; i<d.length; i++) {
			d[i].bark();
		}

	}

}
