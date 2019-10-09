package q04;

import java.util.HashMap;
import java.util.Map;

public class Main {

	public static void main(String[] args) {
		Map<Integer, Integer> m = new HashMap<Integer, Integer>();
		Map<Integer, Integer> cm = new CacheMap<Integer, Integer>(m, 10, 5);
	}

}
