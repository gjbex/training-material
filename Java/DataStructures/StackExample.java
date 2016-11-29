import java.util.Stack;

/**
 * @author Geert Jan Bex
 *
 */
public class StackExample {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		Stack<Integer> stack = new Stack<Integer>();
		for (int i = 0; i < 10; i++)
			stack.push(i*i);
		System.out.println("size after pushes: " + stack.size());
		while (!stack.isEmpty()) {
			int value = stack.pop();
			System.out.print(" " + value);
		}
		System.out.println();
		System.out.println("size afters pops: " + stack.size());
	}

}
