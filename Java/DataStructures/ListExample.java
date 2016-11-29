import java.util.ArrayList;
import java.util.List;

/**
 * @author Geert Jan Bex
 *
 */
public class ListExample {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		List<Integer> list = new ArrayList<Integer>();
		for (int i = 0; i < 10; i++)
			list.add(5*i);
		printList(list);
		int pos = 3;
		System.out.println("value at " + pos + " = " + list.get(pos));
		list.set(3, -17);
		list.add(0, -13);
		printList(list);
		list.remove(5);
		printList(list);
		list.remove(new Integer(5));
		printList(list);
		System.out.println("size = " + list.size());
		printList(list);
	}

	public static void printList(List<?> list) {
		System.out.print("list:");
		for (Object i: list)
			System.out.print(" " + i);
		System.out.println();;		
	}

}