// ============================================================
// MODULE 10+11 | DSA → Data Structures & Algorithms (C++)
// Compile: g++ -std=c++17 01_data_structures.cpp -o out && ./out
// ============================================================
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// ============================================================
// LINKED LIST (Singly)
// ============================================================
struct ListNode {
    int val; ListNode* next;
    ListNode(int v) : val(v), next(nullptr) {}
};

class LinkedList {
    ListNode* head = nullptr;
public:
    ~LinkedList(){ListNode* c=head;while(c){ListNode* t=c;c=c->next;delete t;}}
    void append(int v){
        ListNode* n=new ListNode(v);
        if(!head){head=n;return;}
        ListNode* c=head; while(c->next) c=c->next; c->next=n;
    }
    void prepend(int v){ListNode* n=new ListNode(v);n->next=head;head=n;}
    void remove(int v){
        if(!head)return;
        if(head->val==v){ListNode* t=head;head=head->next;delete t;return;}
        ListNode* c=head;
        while(c->next&&c->next->val!=v) c=c->next;
        if(c->next){ListNode* t=c->next;c->next=t->next;delete t;}
    }
    void reverse(){
        ListNode* prev=nullptr,*curr=head,*nxt=nullptr;
        while(curr){nxt=curr->next;curr->next=prev;prev=curr;curr=nxt;} head=prev;
    }
    bool hasCycle(){
        ListNode* slow=head,*fast=head;
        while(fast&&fast->next){slow=slow->next;fast=fast->next->next;if(slow==fast)return true;}
        return false;
    }
    int middleVal(){
        ListNode* slow=head,*fast=head;
        while(fast&&fast->next){slow=slow->next;fast=fast->next->next;}
        return slow?slow->val:-1;
    }
    void print(){
        ListNode* c=head;while(c){cout<<c->val<<(c->next?" -> ":"");c=c->next;}cout<<"\n";
    }
};

// ============================================================
// BINARY SEARCH TREE
// ============================================================
struct TreeNode {int val;TreeNode* l;TreeNode* r;TreeNode(int v):val(v),l(nullptr),r(nullptr){}};

class BST {
    TreeNode* root=nullptr;
    TreeNode* insert(TreeNode* n,int v){
        if(!n)return new TreeNode(v);
        if(v<n->val)n->l=insert(n->l,v);else if(v>n->val)n->r=insert(n->r,v);return n;
    }
    void inorder(TreeNode* n){if(!n)return;inorder(n->l);cout<<n->val<<" ";inorder(n->r);}
    int  height(TreeNode* n){if(!n)return 0;return 1+max(height(n->l),height(n->r));}
    bool search(TreeNode* n,int v){if(!n)return false;if(n->val==v)return true;return v<n->val?search(n->l,v):search(n->r,v);}
    void destroy(TreeNode* n){if(!n)return;destroy(n->l);destroy(n->r);delete n;}
public:
    ~BST(){destroy(root);}
    void insert(int v){root=insert(root,v);}
    void inorder(){cout<<"Inorder: ";inorder(root);cout<<"\n";}
    void levelOrder(){
        if(!root)return;queue<TreeNode*>q;q.push(root);cout<<"LevelOrder: ";
        while(!q.empty()){TreeNode* n=q.front();q.pop();cout<<n->val<<" ";
            if(n->l)q.push(n->l);if(n->r)q.push(n->r);}cout<<"\n";
    }
    int  height(){return height(root);}
    bool search(int v){return search(root,v);}
};

// ============================================================
// GRAPH (Adjacency list, BFS+DFS)
// ============================================================
class Graph {
    int V; vector<vector<int>> adj;
public:
    Graph(int v):V(v),adj(v){}
    void addEdge(int u,int v){adj[u].push_back(v);adj[v].push_back(u);}
    void bfs(int s){
        vector<bool>vis(V,false);queue<int>q;vis[s]=true;q.push(s);cout<<"BFS: ";
        while(!q.empty()){int n=q.front();q.pop();cout<<n<<" ";
            for(int nb:adj[n])if(!vis[nb]){vis[nb]=true;q.push(nb);}}cout<<"\n";
    }
    void dfsH(int n,vector<bool>&vis){vis[n]=true;cout<<n<<" ";for(int nb:adj[n])if(!vis[nb])dfsH(nb,vis);}
    void dfs(int s){vector<bool>vis(V,false);cout<<"DFS: ";dfsH(s,vis);cout<<"\n";}
};

int main() {
    // Linked List:
    cout << "=== LINKED LIST ===" << endl;
    LinkedList ll;
    for (int x:{10,20,30,40,50}) ll.append(x);
    ll.prepend(5); ll.print();
    ll.remove(30); ll.print();
    ll.reverse();  ll.print();
    cout << "Cycle: " << ll.hasCycle() << "  Middle: " << ll.middleVal() << "\n";

    // BST:
    cout << "\n=== BINARY SEARCH TREE ===" << endl;
    BST bst;
    for (int x:{50,30,70,20,40,60,80}) bst.insert(x);
    bst.inorder(); bst.levelOrder();
    cout << "Height: " << bst.height() << "\n";
    cout << "Search 40: " << bst.search(40) << "  Search 99: " << bst.search(99) << "\n";

    // Graph:
    cout << "\n=== GRAPH ===" << endl;
    Graph g(6);
    g.addEdge(0,1);g.addEdge(0,2);g.addEdge(1,3);g.addEdge(2,4);g.addEdge(3,5);
    g.bfs(0); g.dfs(0);

    return 0;
}
