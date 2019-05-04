public class Dog {

	private int size;

	public void bark() {
		if(size <= 5) {
			System.out.println("Au! Au!");
		} else {
			System.out.println("Whoof! Whoof!");
		}
	}

	public Dog(int size) {
		setSize(size);
	}

	public Dog() {}

	public void setSize(int size) {
		this.size = size;
	}

	public int getSize() {
		return size;
	}

}


