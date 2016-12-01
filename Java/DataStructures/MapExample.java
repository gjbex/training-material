import java.util.TreeMap;
import java.util.Map;

/**
 * @author Geert Jan Bex
 *
 */
public class MapExample {

	public static void main(String[] args) {
		Map<String, Integer> translation = new TreeMap<String, Integer>();
		String[] keys = {"one", "two", "three"};
		int value = 0;
		for (String key: keys)
			translation.put(key, ++value);
		printMap(translation);
		if (translation.containsKey("three"))
			System.out.println("has three");
		if (!translation.containsKey("six")) {
			System.out.println("has no six");
		}
		translation.put("two", 5);
		printMap(translation);
		translation.remove("one");
		printMap(translation);
	}

	public static void printMap(Map<?,?> map) {
		System.out.print("map:");
		for (Object key: map.keySet())
			System.out.print(" " + key + "->" + map.get(key));
		System.out.println();;
	}

}
