/**
 * MODULE 10-11 | DSA → Data Structures & Algorithms (Java)
 * Compile: javac DSA.java && java DSA
 */
import java.util.*;
import java.util.stream.*;

public class DSA {

    // ============================================================
    // LINKED LIST
    // ============================================================
    static class ListNode { int val; ListNode next; ListNode(int v){val=v;} }
    static class MyLinkedList {
        ListNode head;
        void append(int v){ListNode n=new ListNode(v);if(head==null){head=n;return;}ListNode c=head;while(c.next!=null)c=c.next;c.next=n;}
        void prepend(int v){ListNode n=new ListNode(v);n.next=head;head=n;}
        void delete(int v){if(head==null)return;if(head.val==v){head=head.next;return;}ListNode c=head;while(c.next!=null&&c.next.val!=v)c=c.next;if(c.next!=null)c.next=c.next.next;}
        void reverse(){ListNode prev=null,curr=head,nxt=null;while(curr!=null){nxt=curr.next;curr.next=prev;prev=curr;curr=nxt;}head=prev;}
        boolean hasCycle(){ListNode s=head,f=head;while(f!=null&&f.next!=null){s=s.next;f=f.next.next;if(s==f)return true;}return false;}
        int middle(){ListNode s=head,f=head;while(f!=null&&f.next!=null){s=s.next;f=f.next.next;}return s!=null?s.val:-1;}
        @Override public String toString(){StringBuilder sb=new StringBuilder();ListNode c=head;while(c!=null){sb.append(c.val);if(c.next!=null)sb.append(" → ");c=c.next;}return sb.toString();}
    }

    // ============================================================
    // BST
    // ============================================================
    static class TreeNode { int val; TreeNode l,r; TreeNode(int v){val=v;} }
    static class BST {
        TreeNode root;
        TreeNode insert(TreeNode n,int v){if(n==null)return new TreeNode(v);if(v<n.val)n.l=insert(n.l,v);else if(v>n.val)n.r=insert(n.r,v);return n;}
        void insert(int v){root=insert(root,v);}
        void inorder(TreeNode n){if(n==null)return;inorder(n.l);System.out.print(n.val+" ");inorder(n.r);}
        void levelOrder(){if(root==null)return;Queue<TreeNode>q=new ArrayDeque<>();q.offer(root);while(!q.isEmpty()){TreeNode n=q.poll();System.out.print(n.val+" ");if(n.l!=null)q.offer(n.l);if(n.r!=null)q.offer(n.r);}}
        int height(TreeNode n){if(n==null)return 0;return 1+Math.max(height(n.l),height(n.r));}
        boolean search(TreeNode n,int v){if(n==null)return false;if(n.val==v)return true;return v<n.val?search(n.l,v):search(n.r,v);}
    }

    // ============================================================
    // GRAPH
    // ============================================================
    static class Graph {
        int V; Map<Integer,List<Integer>> adj=new HashMap<>();
        Graph(int v){V=v;for(int i=0;i<v;i++)adj.put(i,new ArrayList<>());}
        void addEdge(int u,int w){adj.get(u).add(w);adj.get(w).add(u);}
        void bfs(int s){boolean[]vis=new boolean[V];Queue<Integer>q=new ArrayDeque<>();vis[s]=true;q.offer(s);System.out.print("BFS: ");while(!q.isEmpty()){int n=q.poll();System.out.print(n+" ");for(int nb:adj.get(n))if(!vis[nb]){vis[nb]=true;q.offer(nb);}}System.out.println();}
        void dfs(int n,boolean[]vis){vis[n]=true;System.out.print(n+" ");for(int nb:adj.get(n))if(!vis[nb])dfs(nb,vis);}
    }

    // ============================================================
    // SORTING
    // ============================================================
    static void mergeSort(int[]a,int l,int r){if(l>=r)return;int m=l+(r-l)/2;mergeSort(a,l,m);mergeSort(a,m+1,r);merge(a,l,m,r);}
    static void merge(int[]a,int l,int m,int r){int[]L=Arrays.copyOfRange(a,l,m+1),R=Arrays.copyOfRange(a,m+1,r+1);int i=0,j=0,k=l;while(i<L.length&&j<R.length)a[k++]=L[i]<=R[j]?L[i++]:R[j++];while(i<L.length)a[k++]=L[i++];while(j<R.length)a[k++]=R[j++];}
    static void quickSort(int[]a,int lo,int hi){if(lo>=hi)return;int pi=partition(a,lo,hi);quickSort(a,lo,pi-1);quickSort(a,pi+1,hi);}
    static int partition(int[]a,int lo,int hi){int piv=a[hi],i=lo-1;for(int j=lo;j<hi;j++)if(a[j]<=piv){i++;int t=a[i];a[i]=a[j];a[j]=t;}int t=a[i+1];a[i+1]=a[hi];a[hi]=t;return i+1;}

    // ============================================================
    // DYNAMIC PROGRAMMING
    // ============================================================
    static int lcs(String s1,String s2){int m=s1.length(),n=s2.length();int[][]dp=new int[m+1][n+1];for(int i=1;i<=m;i++)for(int j=1;j<=n;j++)dp[i][j]=s1.charAt(i-1)==s2.charAt(j-1)?dp[i-1][j-1]+1:Math.max(dp[i-1][j],dp[i][j-1]);return dp[m][n];}
    static int knapsack(int[]w,int[]v,int W){int n=w.length;int[][]dp=new int[n+1][W+1];for(int i=1;i<=n;i++)for(int c=0;c<=W;c++){dp[i][c]=dp[i-1][c];if(w[i-1]<=c)dp[i][c]=Math.max(dp[i][c],dp[i-1][c-w[i-1]]+v[i-1]);}return dp[n][W];}
    static int coinChange(int[]coins,int amt){int[]dp=new int[amt+1];Arrays.fill(dp,Integer.MAX_VALUE);dp[0]=0;for(int i=1;i<=amt;i++)for(int c:coins)if(c<=i&&dp[i-c]!=Integer.MAX_VALUE)dp[i]=Math.min(dp[i],dp[i-c]+1);return dp[amt]==Integer.MAX_VALUE?-1:dp[amt];}
    static int kadane(int[]a){int mx=a[0],curr=a[0];for(int i=1;i<a.length;i++){curr=Math.max(a[i],curr+a[i]);mx=Math.max(mx,curr);}return mx;}

    public static void main(String[] args) {
        // Linked List:
        System.out.println("=== LINKED LIST ===");
        MyLinkedList ll=new MyLinkedList();
        for(int x:new int[]{10,20,30,40,50}) ll.append(x);
        ll.prepend(5); System.out.println(ll);
        ll.delete(30);  System.out.println(ll);
        ll.reverse();   System.out.println(ll);
        System.out.println("Cycle: "+ll.hasCycle()+"  Middle: "+ll.middle());

        // BST:
        System.out.println("\n=== BST ===");
        BST bst=new BST();
        for(int x:new int[]{50,30,70,20,40,60,80}) bst.insert(x);
        System.out.print("Inorder: "); bst.inorder(bst.root); System.out.println();
        System.out.print("LevelOrder: "); bst.levelOrder(); System.out.println();
        System.out.println("Height="+bst.height(bst.root)+" Search40="+bst.search(bst.root,40)+" Search99="+bst.search(bst.root,99));

        // Graph:
        System.out.println("\n=== GRAPH ===");
        Graph g=new Graph(6);
        g.addEdge(0,1);g.addEdge(0,2);g.addEdge(1,3);g.addEdge(2,4);g.addEdge(3,5);
        g.bfs(0); System.out.print("DFS: ");g.dfs(0,new boolean[6]);System.out.println();

        // Sorting:
        System.out.println("\n=== SORTING ===");
        int[]arr={64,34,25,12,22,11,90};
        int[]ms=arr.clone(); mergeSort(ms,0,ms.length-1); System.out.println("Merge:  "+Arrays.toString(ms));
        int[]qs=arr.clone(); quickSort(qs,0,qs.length-1); System.out.println("Quick:  "+Arrays.toString(qs));

        // DP:
        System.out.println("\n=== DYNAMIC PROGRAMMING ===");
        System.out.println("LCS(ABCBDAB,BDCAB)="+lcs("ABCBDAB","BDCAB"));   // 4
        System.out.println("Knapsack(W=7)="+knapsack(new int[]{1,3,4,5},new int[]{1,4,5,7},7));  // 9
        System.out.println("CoinChange(11)="+coinChange(new int[]{1,5,6,9},11));   // 2
        System.out.println("Kadane="+kadane(new int[]{-2,1,-3,4,-1,2,1,-5,4}));    // 6

        // Streams:
        System.out.println("\n=== STREAMS ===");
        List<Integer>nums=List.of(1,2,3,4,5,6,7,8,9,10);
        System.out.println("Even squares:"+nums.stream().filter(n->n%2==0).map(n->n*n).collect(Collectors.toList()));
        System.out.println("Sum="+nums.stream().mapToInt(Integer::intValue).sum());
    }
}
