/**
 * 
 */

/**
 * @author Geert Jan Bex
 *
 */
public class ArrayExample {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		final int n = 10;
		int[] data = new int[n];
		for (int i = 0; i < n; i++)
			data[i] = i*i;
		System.out.println("length: " + data.length);
		for (int value: data)
			System.out.print(" " + value);
		System.out.println();
	}

}