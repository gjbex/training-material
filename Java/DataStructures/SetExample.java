import java.util.HashSet;
import java.util.Set;

/**
 * @author Geert Jan Bex
 *
 */
public class SetExample {

	public static void main(String[] args) {
		Set<Integer> set = new HashSet<Integer>();
		for (int i = 0; i < 10; i++)
			set.add(2*i + 1);
		printSet(set);
		if (set.contains(3))
			System.out.println("has 3");
		if (!set.contains(2))
			System.out.println("has no 2");
		set.remove(3);
		printSet(set);
		System.out.println("size = " + set.size());
	}

	public static void printSet(Set<?> set) {
		System.out.print("set:");
		for (Object value: set)
			System.out.print(" " + value);
		System.out.println();;
	}

}
