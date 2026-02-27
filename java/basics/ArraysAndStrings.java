/**
 * MODULE 04 | BASICS → Arrays & Strings (Java)
 * Compile: javac ArraysAndStrings.java && java ArraysAndStrings
 */
import java.util.*;

public class ArraysAndStrings {
    static void reverse(int[] a,int l,int r){while(l<r){int t=a[l];a[l++]=a[r];a[r--]=t;}}
    static boolean isPalindrome(String s){int l=0,r=s.length()-1;while(l<r)if(s.charAt(l++)!=s.charAt(r--))return false;return true;}
    static boolean isAnagram(String a,String b){if(a.length()!=b.length())return false;int[]cnt=new int[26];for(char c:a.toCharArray())cnt[c-'a']++;for(char c:b.toCharArray())if(--cnt[c-'a']<0)return false;return true;}
    static int longestUnique(String s){Map<Character,Integer>pos=new HashMap<>();int l=0,mx=0;for(int r=0;r<s.length();r++){char c=s.charAt(r);if(pos.containsKey(c)&&pos.get(c)>=l)l=pos.get(c)+1;pos.put(c,r);mx=Math.max(mx,r-l+1);}return mx;}

    public static void main(String[] args) {
        System.out.println("=== ARRAYS ===");
        int[] arr = {64,23,87,12,45};
        System.out.println("Original: " + Arrays.toString(arr));
        Arrays.sort(arr);
        System.out.println("Sorted:   " + Arrays.toString(arr));

        // Reverse:
        int[] rev = {1,2,3,4,5}; reverse(rev,0,4);
        System.out.println("Reversed: " + Arrays.toString(rev));

        // Rotate right by k:
        int[] rot = {1,2,3,4,5,6,7}; int k=3, sz=rot.length; k%=sz;
        reverse(rot,0,sz-1); reverse(rot,0,k-1); reverse(rot,k,sz-1);
        System.out.println("Rotated+3:" + Arrays.toString(rot));

        // Sliding window (max sum k=3):
        int[] win={2,1,5,1,3,2}; int ws=0,ms=0,kw=3;
        for(int i=0;i<kw;i++) ws+=win[i]; ms=ws;
        for(int i=kw;i<win.length;i++){ws+=win[i]-win[i-kw];ms=Math.max(ms,ws);}
        System.out.println("Max window sum (k=3): " + ms);   // 9

        // Two sum (HashMap):
        int[] twoSum={2,7,11,15}; int target=9;
        Map<Integer,Integer> map=new HashMap<>();
        int[] res={-1,-1};
        for(int i=0;i<twoSum.length;i++){int comp=target-twoSum[i];if(map.containsKey(comp)){res[0]=map.get(comp);res[1]=i;break;}map.put(twoSum[i],i);}
        System.out.println("Two Sum [2,7,11,15] t=9: " + Arrays.toString(res));

        // Binary search:
        int[] sorted={1,3,5,7,9,11}; Arrays.sort(sorted);
        System.out.println("BinarySearch(7)=idx" + Arrays.binarySearch(sorted,7));

        System.out.println("\n=== 2D ARRAY (matrix transpose) ===");
        int[][] mat={{1,2,3},{4,5,6},{7,8,9}};
        for(int i=0;i<3;i++) for(int j=i+1;j<3;j++){int t=mat[i][j];mat[i][j]=mat[j][i];mat[j][i]=t;}
        for(int[] row:mat) System.out.println(Arrays.toString(row));

        System.out.println("\n=== STRINGS ===");
        String s = "Hello, World!";
        System.out.println("length="+s.length()+" upper="+s.toUpperCase());
        System.out.println("substring(7,12)="+s.substring(7,12));
        System.out.println("replace="+s.replace("World","Java"));
        System.out.println("isPalindrome(racecar)="+isPalindrome("racecar"));
        System.out.println("isAnagram(listen,silent)="+isAnagram("listen","silent"));
        System.out.println("longestUnique(abcabcbb)="+longestUnique("abcabcbb"));   // 3

        // StringBuilder:
        StringBuilder sb=new StringBuilder("Hello");
        sb.append(" World"); sb.reverse();
        System.out.println("StringBuilder reversed: " + sb);
    }
}
