import java.util.ArrayDeque;
import java.util.Queue;

/**
 * 
 */

/**
 * @author Geert Jan Bex
 *
 */
public class QueueExample {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		Queue<Integer> queue = new ArrayDeque<Integer>();
		for (int i = 0; i < 10; i++)
			queue.add(i*i);
		System.out.println("size after adds: " + queue.size());
		while (!queue.isEmpty()) {
			int value = queue.remove();
			System.out.print(" " + value);
		}
		System.out.println();
		System.out.println("size afters removes: " + queue.size());
	}

}
