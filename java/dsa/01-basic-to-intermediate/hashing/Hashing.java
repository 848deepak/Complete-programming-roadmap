// ============================================================
// DSA | Java → Hashing: HashMap, HashSet, Interview Problems
// ============================================================
// DESCRIPTION:
//   Java's built-in HashMap and HashSet with interview classics:
//   - Two Sum, Longest Consecutive, Group Anagrams
//   - Subarray sum = k, Count distinct in window
//   - Custom objects as keys (overriding hashCode & equals)
//
// COMPILE & RUN:
//   javac Hashing.java && java Hashing
// ============================================================

import java.util.*;

public class Hashing {

    // ============================================================
    // SECTION 1: HASHMAP BASICS
    // ============================================================
    static void demoHashMap() {
        System.out.println("=== HASHMAP BASICS ===");

        // Word frequency counter
        String[] words = { "the", "cat", "sat", "on", "the", "mat", "the", "cat" };
        Map<String, Integer> freq = new HashMap<>();
        for (String w : words)
            freq.merge(w, 1, Integer::sum);
        System.out.println("  Word frequencies: " + freq);

        // getOrDefault — safe access without null check
        System.out.println("  'cat' count: " + freq.getOrDefault("cat", 0));
        System.out.println("  'dog' count: " + freq.getOrDefault("dog", 0));

        // putIfAbsent — only insert if key not already present
        freq.putIfAbsent("dog", 0);
        System.out.println("  After putIfAbsent('dog'): " + freq.get("dog"));

        // computeIfAbsent — compute value if absent
        Map<String, List<String>> map = new HashMap<>();
        map.computeIfAbsent("fruits", k -> new ArrayList<>()).add("apple");
        map.computeIfAbsent("fruits", k -> new ArrayList<>()).add("banana");
        System.out.println("  computeIfAbsent: " + map.get("fruits"));

        // Iterate with entrySet
        System.out.println("  Sorted freq:");
        freq.entrySet().stream()
                .sorted(Map.Entry.comparingByKey())
                .forEach(e -> System.out.println("    " + e.getKey() + " → " + e.getValue()));
    }

    // ============================================================
    // SECTION 2: HASHSET BASICS
    // ============================================================
    static void demoHashSet() {
        System.out.println("\n=== HASHSET BASICS ===");
        Set<Integer> set = new HashSet<>();
        int[] nums = { 4, 1, 2, 1, 3, 4, 2, 5 };
        System.out.print("  Unique elements: ");
        for (int n : nums)
            if (set.add(n))
                System.out.print(n + " ");
        System.out.println();
        System.out.println("  contains(3): " + set.contains(3));
        set.remove(3);
        System.out.println("  after remove(3): contains(3)=" + set.contains(3));
    }

    // ============================================================
    // SECTION 3: CUSTOM KEY — override hashCode + equals
    // ============================================================
    static class Point {
        int x, y;

        Point(int x, int y) {
            this.x = x;
            this.y = y;
        }

        @Override
        public int hashCode() {
            return java.util.Objects.hash(x, y); // combines x.hash and y.hash
        }

        @Override
        public boolean equals(Object o) {
            if (!(o instanceof Point))
                return false;
            Point p = (Point) o;
            return x == p.x && y == p.y;
        }

        @Override
        public String toString() {
            return "(" + x + "," + y + ")";
        }
    }

    static void demoCustomKey() {
        System.out.println("\n=== CUSTOM KEY (Point) ===");
        Map<Point, String> labels = new HashMap<>();
        labels.put(new Point(0, 0), "origin");
        labels.put(new Point(1, 0), "x-axis");
        labels.put(new Point(0, 1), "y-axis");

        System.out.println("  (0,0) → " + labels.get(new Point(0, 0)));
        System.out.println("  (1,0) → " + labels.get(new Point(1, 0)));

        Set<Point> visited = new HashSet<>();
        visited.add(new Point(3, 4));
        System.out.println("  visited (3,4): " + visited.contains(new Point(3, 4)));
    }

    // ============================================================
    // SECTION 4: INTERVIEW PROBLEMS
    // ============================================================

    /** Two Sum: indices i,j where arr[i]+arr[j]==target. O(n) */
    static int[] twoSum(int[] arr, int target) {
        Map<Integer, Integer> seen = new HashMap<>();
        for (int i = 0; i < arr.length; i++) {
            int comp = target - arr[i];
            if (seen.containsKey(comp))
                return new int[] { seen.get(comp), i };
            seen.put(arr[i], i);
        }
        return new int[] { -1, -1 };
    }

    /** Longest consecutive sequence. O(n) */
    static int longestConsecutive(int[] nums) {
        Set<Integer> set = new HashSet<>();
        for (int n : nums)
            set.add(n);
        int best = 0;
        for (int n : set) {
            if (!set.contains(n - 1)) { // start of sequence
                int len = 1;
                while (set.contains(++n))
                    len++;
                best = Math.max(best, len);
            }
        }
        return best;
    }

    /** Group anagrams. O(n * L log L) */
    static List<List<String>> groupAnagrams(String[] words) {
        Map<String, List<String>> map = new HashMap<>();
        for (String w : words) {
            char[] key = w.toCharArray();
            java.util.Arrays.sort(key);
            map.computeIfAbsent(new String(key), k -> new ArrayList<>()).add(w);
        }
        return new ArrayList<>(map.values());
    }

    /** Count subarrays with sum = k. O(n) */
    static int subarraySumK(int[] arr, int k) {
        Map<Integer, Integer> prefixFreq = new HashMap<>();
        prefixFreq.put(0, 1);
        int sum = 0, count = 0;
        for (int x : arr) {
            sum += x;
            count += prefixFreq.getOrDefault(sum - k, 0);
            prefixFreq.merge(sum, 1, Integer::sum);
        }
        return count;
    }

    /** First unique character in a string. O(n) */
    static int firstUnique(String s) {
        Map<Character, Integer> freq = new LinkedHashMap<>(); // preserves insertion order
        for (char c : s.toCharArray())
            freq.merge(c, 1, Integer::sum);
        for (int i = 0; i < s.length(); i++)
            if (freq.get(s.charAt(i)) == 1)
                return i;
        return -1;
    }

    /** Count distinct elements in every window of size k. O(n) */
    static List<Integer> distinctInWindow(int[] arr, int k) {
        Map<Integer, Integer> window = new HashMap<>();
        List<Integer> result = new ArrayList<>();
        for (int i = 0; i < arr.length; i++) {
            window.merge(arr[i], 1, Integer::sum);
            if (i >= k) {
                int out = arr[i - k];
                if (window.merge(out, -1, Integer::sum) == 0)
                    window.remove(out);
            }
            if (i >= k - 1)
                result.add(window.size());
        }
        return result;
    }

    /** Check if two strings are isomorphic. O(n) */
    static boolean isIsomorphic(String s, String t) {
        Map<Character, Character> sMap = new HashMap<>(), tMap = new HashMap<>();
        for (int i = 0; i < s.length(); i++) {
            char sc = s.charAt(i), tc = t.charAt(i);
            if (sMap.containsKey(sc) && sMap.get(sc) != tc)
                return false;
            if (tMap.containsKey(tc) && tMap.get(tc) != sc)
                return false;
            sMap.put(sc, tc);
            tMap.put(tc, sc);
        }
        return true;
    }

    // ============================================================
    // MAIN
    // ============================================================
    public static void main(String[] args) {
        demoHashMap();
        demoHashSet();
        demoCustomKey();

        System.out.println("\n=== INTERVIEW PROBLEMS ===");

        int[] arr = { 2, 7, 11, 15 };
        int[] res = twoSum(arr, 9);
        System.out.println("  twoSum([2,7,11,15], 9): [" + res[0] + "," + res[1] + "]");

        System.out.println("  longestConsecutive([100,4,200,1,3,2]): "
                + longestConsecutive(new int[] { 100, 4, 200, 1, 3, 2 })); // 4

        System.out.println("  groupAnagrams: "
                + groupAnagrams(new String[] { "eat", "tea", "tan", "ate", "nat", "bat" }));

        System.out.println("  subarraySumK([1,1,1], k=2): "
                + subarraySumK(new int[] { 1, 1, 1 }, 2)); // 2

        System.out.println("  firstUnique(\"leetcode\"): idx "
                + firstUnique("leetcode")); // 0

        System.out.println("  distinctInWindow([1,2,1,3,2],k=3): "
                + distinctInWindow(new int[] { 1, 2, 1, 3, 2 }, 3)); // [2,3,3]

        System.out.println("  isIsomorphic(\"egg\",\"add\"): " + isIsomorphic("egg", "add"));
        System.out.println("  isIsomorphic(\"foo\",\"bar\"): " + isIsomorphic("foo", "bar"));
    }
}
