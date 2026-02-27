# 🔑 Hashing — Practice Problems

> **Topic:** Hash Maps & Hash Sets | **Level:** Easy → Hard

---

| # | Problem | Difficulty | Pattern |
|---|---------|-----------|---------|
| 1 | [Contains Duplicate](#1-contains-duplicate) | 🟢 Easy | Hash Set |
| 2 | [Valid Anagram](#2-valid-anagram) | 🟢 Easy | Frequency Map |
| 3 | [Intersection of Two Arrays](#3-intersection) | 🟢 Easy | Hash Set |
| 4 | [First Unique Character](#4-first-unique-char) | 🟢 Easy | Frequency Map |
| 5 | [Ransom Note](#5-ransom-note) | 🟢 Easy | Frequency Map |
| 6 | [Group Anagrams](#6-group-anagrams) | 🟡 Medium | Sort Key Map |
| 7 | [Longest Consecutive Sequence](#7-longest-consecutive) | 🟡 Medium | Hash Set |
| 8 | [Subarray Sum Equals K](#8-subarray-sum-k) | 🟡 Medium | Prefix Sum + Map |
| 9 | [Top K Frequent Elements](#9-top-k-frequent) | 🟡 Medium | Bucket Sort |
| 10 | [4Sum II](#10-4sum-ii) | 🟡 Medium | Hash Map |
| 11 | [Count Distinct Elements in Windows](#11-distinct-in-windows) | 🔴 Hard | Sliding Window + Map |
| 12 | [Longest Substring Without Repeating](#12-longest-no-repeat) | 🔴 Hard | Hash Set + Sliding |
| 13 | [Minimum Window Substring](#13-minimum-window-substring) | 🔴 Hard | Sliding Window + Freq |

---

## 🟢 EASY PROBLEMS

### 1. Contains Duplicate
**Problem:** Return true if any value appears at least twice.

```cpp
bool containsDuplicate(vector<int>& nums) {
    unordered_set<int> seen;
    for (int n : nums) { if (seen.count(n)) return true; seen.insert(n); }
    return false;
}
```
```java
public static boolean containsDuplicate(int[] nums) {
    Set<Integer> seen = new HashSet<>();
    for (int n : nums) if (!seen.add(n)) return true;
    return false;
}
```
**O(n) time, O(n) space.**

---

### 2. Valid Anagram
**Problem:** Check if string t is anagram of s. `"anagram","nagaram"` → true.

```cpp
bool isAnagram(string s, string t) {
    if (s.size()!=t.size()) return false;
    int freq[26]={}; for (char c:s) freq[c-'a']++; for (char c:t) if(--freq[c-'a']<0) return false;
    return true;
}
```
```java
public static boolean isAnagram(String s, String t) {
    if (s.length()!=t.length()) return false;
    int[] f = new int[26]; for (char c:s.toCharArray()) f[c-'a']++; for (char c:t.toCharArray()) if(--f[c-'a']<0) return false;
    return true;
}
```

---

### 3. Intersection of Two Arrays
**Problem:** Return unique elements common to both arrays.

```cpp
vector<int> intersection(vector<int>& a, vector<int>& b) {
    unordered_set<int> sa(a.begin(), a.end()); vector<int> res;
    for (int x : b) if (sa.erase(x)) res.push_back(x);
    return res;
}
```
```java
public static int[] intersection(int[] a, int[] b) {
    Set<Integer> sa = new HashSet<>(); for (int x:a) sa.add(x);
    Set<Integer> res = new HashSet<>(); for (int x:b) if (sa.contains(x)) res.add(x);
    return res.stream().mapToInt(Integer::intValue).toArray();
}
```

---

### 4. First Unique Character
**Problem:** First non-repeating character index in a string. `"leetcode"` → 0 (`l`).

```cpp
int firstUniqChar(string s) {
    int freq[26]={}; for (char c:s) freq[c-'a']++;
    for (int i=0;i<(int)s.size();i++) if (freq[s[i]-'a']==1) return i;
    return -1;
}
```
```java
public static int firstUniqChar(String s) {
    int[] f=new int[26]; for (char c:s.toCharArray()) f[c-'a']++;
    for (int i=0;i<s.length();i++) if (f[s.charAt(i)-'a']==1) return i;
    return -1;
}
```

---

### 5. Ransom Note
**Problem:** Can `ransomNote` be constructed from letters in `magazine`?

```cpp
bool canConstruct(string r, string m) {
    int f[26]={}; for (char c:m) f[c-'a']++;
    for (char c:r) if (--f[c-'a']<0) return false;
    return true;
}
```
```java
public static boolean canConstruct(String r, String m) {
    int[] f=new int[26]; for (char c:m.toCharArray()) f[c-'a']++;
    for (char c:r.toCharArray()) if (--f[c-'a']<0) return false;
    return true;
}
```

---

## 🟡 MEDIUM PROBLEMS

### 6. Group Anagrams
**Problem:** Group strings that are anagrams of each other.
```
["eat","tea","tan","ate","nat","bat"] → [["eat","tea","ate"],["tan","nat"],["bat"]]
```
**Approach:** Sort each string as the key in a hash map.

```cpp
vector<vector<string>> groupAnagrams(vector<string>& strs) {
    unordered_map<string, vector<string>> map;
    for (auto& s : strs) { string key = s; sort(key.begin(), key.end()); map[key].push_back(s); }
    vector<vector<string>> res;
    for (auto& [k, v] : map) res.push_back(v);
    return res;
}
```
```java
public static List<List<String>> groupAnagrams(String[] strs) {
    Map<String, List<String>> map = new HashMap<>();
    for (String s : strs) { char[] ch=s.toCharArray(); Arrays.sort(ch); String key=new String(ch); map.computeIfAbsent(key,k->new ArrayList<>()).add(s); }
    return new ArrayList<>(map.values());
}
```
**O(n·k log k) where k = max string length.**

---

### 7. Longest Consecutive Sequence
**Problem:** Find longest consecutive element sequence. Must be O(n).
```
[100, 4, 200, 1, 3, 2] → 4  (sequence: 1,2,3,4)
```
**Approach:** Put all in hash set. For each number that is a sequence start (n-1 not in set), count forward.

```cpp
int longestConsecutive(vector<int>& nums) {
    unordered_set<int> s(nums.begin(), nums.end()); int best = 0;
    for (int n : s) {
        if (!s.count(n-1)) { // Start of sequence
            int len = 1; while (s.count(n+len)) len++;
            best = max(best, len);
        }
    }
    return best;
}
```
```java
public static int longestConsecutive(int[] nums) {
    Set<Integer> s = new HashSet<>(); for (int n:nums) s.add(n);
    int best = 0;
    for (int n : s) {
        if (!s.contains(n-1)) { int len=1; while(s.contains(n+len)) len++; best=Math.max(best,len); }
    }
    return best;
}
```
**O(n) time.**

---

### 8. Subarray Sum Equals K
**Problem:** Count subarrays with sum = k.
```
[1,1,1], k=2 → 2
```
**Approach:** Prefix sum + hash map counting occurrences of each prefix sum. If `prefixSum - k` exists, we found subarrays.

```cpp
int subarraySum(vector<int>& nums, int k) {
    unordered_map<int,int> prefCount; prefCount[0]=1;
    int sum=0, count=0;
    for (int n:nums) { sum+=n; if (prefCount.count(sum-k)) count+=prefCount[sum-k]; prefCount[sum]++; }
    return count;
}
```
```java
public static int subarraySum(int[] nums, int k) {
    Map<Integer,Integer> pc = new HashMap<>(); pc.put(0,1);
    int sum=0, count=0;
    for (int n:nums) { sum+=n; count+=pc.getOrDefault(sum-k,0); pc.merge(sum,1,Integer::sum); }
    return count;
}
```
**O(n) time, O(n) space.**

---

### 9. Top K Frequent Elements
**Problem:** Return the k most frequent elements from an array.
**Approach:** Bucket sort — frequency array where index = frequency.

```cpp
vector<int> topKFrequent(vector<int>& nums, int k) {
    unordered_map<int,int> freq; for (int n:nums) freq[n]++;
    int n = nums.size();
    vector<vector<int>> bucket(n+1);
    for (auto& [val, cnt] : freq) bucket[cnt].push_back(val);
    vector<int> res;
    for (int i=n; i>=0 && (int)res.size()<k; i--)
        for (int x : bucket[i]) { res.push_back(x); if ((int)res.size()==k) break; }
    return res;
}
```
```java
public static int[] topKFrequent(int[] nums, int k) {
    Map<Integer,Integer> freq = new HashMap<>(); for (int n:nums) freq.merge(n,1,Integer::sum);
    List<Integer>[] bucket = new List[nums.length+1];
    for (int i=0;i<bucket.length;i++) bucket[i]=new ArrayList<>();
    freq.forEach((v,c)->bucket[c].add(v));
    int[] res = new int[k]; int idx=0;
    for (int i=bucket.length-1;i>=0&&idx<k;i--) for (int x:bucket[i]) { res[idx++]=x; if(idx==k)break; }
    return res;
}
```
**O(n) time with bucket sort.**

---

### 10. 4Sum II
**Problem:** Given four arrays A, B, C, D, count tuples (i,j,k,l) such that A[i]+B[j]+C[k]+D[l]=0.
**Approach:** Store all A[i]+B[j] sums in map. Lookup -(C[k]+D[l]).

```cpp
int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D) {
    unordered_map<int,int> ab; int count=0;
    for (int a:A) for (int b:B) ab[a+b]++;
    for (int c:C) for (int d:D) { auto it = ab.find(-(c+d)); if (it!=ab.end()) count+=it->second; }
    return count;
}
```
```java
public static int fourSumCount(int[] A, int[] B, int[] C, int[] D) {
    Map<Integer,Integer> ab = new HashMap<>(); int count = 0;
    for (int a:A) for (int b:B) ab.merge(a+b,1,Integer::sum);
    for (int c:C) for (int d:D) count += ab.getOrDefault(-(c+d),0);
    return count;
}
```
**O(n²) time, O(n²) space.**

---

## 🔴 HARD PROBLEMS

### 11. Count Distinct Elements in Windows
**Problem:** For each window of size k, count distinct elements.
```
[1,2,1,3,4,2,3], k=4 → [3,4,4,3]
```
**Approach:** Sliding window with frequency map. Add right element, remove left when window exceeds k.

```cpp
vector<int> distinctInWindows(vector<int>& nums, int k) {
    unordered_map<int,int> freq; vector<int> res;
    for (int i=0;i<(int)nums.size();i++) {
        freq[nums[i]]++;
        if (i >= k) { freq[nums[i-k]]--; if (freq[nums[i-k]]==0) freq.erase(nums[i-k]); }
        if (i >= k-1) res.push_back(freq.size());
    }
    return res;
}
```
```java
public static int[] distinctInWindows(int[] nums, int k) {
    Map<Integer,Integer> freq = new HashMap<>(); int[] res = new int[nums.length-k+1]; int idx=0;
    for (int i=0;i<nums.length;i++) {
        freq.merge(nums[i],1,Integer::sum);
        if (i>=k) { freq.merge(nums[i-k],-1,Integer::sum); if(freq.get(nums[i-k])==0) freq.remove(nums[i-k]); }
        if (i>=k-1) res[idx++]=freq.size();
    }
    return res;
}
```

---

### 12. Longest Substring Without Repeating Characters
**Problem:** Find length of longest substring without repeating characters.
```
"abcabcbb" → 3  ("abc")
```
**Approach:** Sliding window + hash map tracking last index of each character.

```cpp
int lengthOfLongestSubstring(string s) {
    unordered_map<char,int> last; int maxLen=0, left=0;
    for (int i=0;i<(int)s.size();i++) {
        if (last.count(s[i]) && last[s[i]]>=left) left = last[s[i]]+1;
        last[s[i]] = i;
        maxLen = max(maxLen, i-left+1);
    }
    return maxLen;
}
```
```java
public static int lengthOfLongestSubstring(String s) {
    Map<Character,Integer> last = new HashMap<>(); int max=0, left=0;
    for (int i=0;i<s.length();i++) {
        if (last.containsKey(s.charAt(i)) && last.get(s.charAt(i))>=left) left=last.get(s.charAt(i))+1;
        last.put(s.charAt(i),i); max=Math.max(max,i-left+1);
    }
    return max;
}
```
**O(n) time, O(min(n, alphabet)) space.**

---

### 13. Minimum Window Substring
**Problem:** Smallest substring of s containing all characters of t.
```
s = "ADOBECODEBANC", t = "ABC" → "BANC"
```
**Approach:** Sliding window with frequency map. Expand right until all needed chars are found, then shrink left.

```cpp
string minWindow(string s, string t) {
    unordered_map<char,int> need, have; for (char c:t) need[c]++;
    int required = need.size(), formed = 0, best = INT_MAX, bestL = 0, left = 0;
    for (int r = 0; r < (int)s.size(); r++) {
        have[s[r]]++;
        if (need.count(s[r]) && have[s[r]] == need[s[r]]) formed++;
        while (formed == required) {
            if (r-left+1 < best) { best = r-left+1; bestL = left; }
            have[s[left]]--;
            if (need.count(s[left]) && have[s[left]] < need[s[left]]) formed--;
            left++;
        }
    }
    return best == INT_MAX ? "" : s.substr(bestL, best);
}
```
```java
public static String minWindow(String s, String t) {
    Map<Character,Integer> need=new HashMap<>(), have=new HashMap<>();
    for (char c:t.toCharArray()) need.merge(c,1,Integer::sum);
    int req=need.size(), formed=0, best=Integer.MAX_VALUE, bestL=0, left=0;
    for (int r=0;r<s.length();r++) {
        char c=s.charAt(r); have.merge(c,1,Integer::sum);
        if (need.containsKey(c) && have.get(c).equals(need.get(c))) formed++;
        while (formed==req) {
            if (r-left+1<best) { best=r-left+1; bestL=left; }
            char lc=s.charAt(left); have.merge(lc,-1,Integer::sum);
            if (need.containsKey(lc)&&have.get(lc)<need.get(lc)) formed--;
            left++;
        }
    }
    return best==Integer.MAX_VALUE ? "" : s.substring(bestL, bestL+best);
}
```
**O(|s|+|t|) time.**

---

## 🗺️ Pattern Summary

| Pattern | Problems |
|---------|----------|
| Hash Set Membership | Contains Duplicate, Intersection, Longest Consecutive |
| Frequency Map | Anagram, Unique Char, Ransom Note, Group Anagrams, Top K |
| Prefix Sum + Map | Subarray Sum Equals K |
| Sliding Window + Map | Distinct in Windows, Longest No Repeat, Min Window Substring |
| Two-Map Merge | 4Sum II |
