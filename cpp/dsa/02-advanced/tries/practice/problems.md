# 🔤 Trie — Practice Problems

> **Topic:** Trie (Prefix Tree) | **Level:** Easy → Hard

---

| # | Problem | Difficulty | Pattern |
|---|---------|-----------|---------|
| 1 | [Implement Trie](#1-implement-trie) | 🟢 Easy | Basic Trie |
| 2 | [Search Prefix](#2-search-prefix) | 🟢 Easy | Prefix Traversal |
| 3 | [Count Words with Prefix](#3-count-prefix) | 🟢 Easy | Prefix Count |
| 4 | [Longest Common Prefix](#4-longest-common-prefix) | 🟢 Easy | Trie Traversal |
| 5 | [Delete Word from Trie](#5-delete-word) | 🟢 Easy | Recursive Delete |
| 6 | [Word Search II (Boggle)](#6-word-search-ii) | 🟡 Medium | Trie + DFS |
| 7 | [Auto-Complete System](#7-autocomplete) | 🟡 Medium | Trie + Priority |
| 8 | [Replace Words](#8-replace-words) | 🟡 Medium | Trie Prefix Match |
| 9 | [Design Add & Search (Wildcard)](#9-add-search-wildcard) | 🟡 Medium | Trie + Backtrack |
| 10 | [Maximum XOR of Two Numbers](#10-max-xor) | 🟡 Medium | Bitwise Trie |
| 11 | [Palindrome Pairs](#11-palindrome-pairs) | 🔴 Hard | Trie + Palindrome |
| 12 | [Word Concatenation](#12-word-concat) | 🔴 Hard | Trie + DP |
| 13 | [Stream of Strings (Aho-Corasick lite)](#13-stream-match) | 🔴 Hard | Trie + BFS |

---

## Trie Node Structure
```cpp
struct TrieNode {
    TrieNode* children[26] = {};
    bool isEnd = false;
    int prefixCount = 0;
};
```
```java
class TrieNode {
    TrieNode[] children = new TrieNode[26];
    boolean isEnd = false;
    int prefixCount = 0;
}
```

---

## 🟢 EASY

### 1. Implement Trie
```cpp
class Trie {
    TrieNode* root;
public:
    Trie() { root = new TrieNode(); }
    void insert(string word) {
        TrieNode* cur = root;
        for (char c : word) {
            if (!cur->children[c-'a']) cur->children[c-'a'] = new TrieNode();
            cur = cur->children[c-'a']; cur->prefixCount++;
        }
        cur->isEnd = true;
    }
    bool search(string word) {
        TrieNode* cur = root;
        for (char c : word) { if (!cur->children[c-'a']) return false; cur = cur->children[c-'a']; }
        return cur->isEnd;
    }
    bool startsWith(string prefix) {
        TrieNode* cur = root;
        for (char c : prefix) { if (!cur->children[c-'a']) return false; cur = cur->children[c-'a']; }
        return true;
    }
};
```
```java
class Trie {
    TrieNode root = new TrieNode();
    void insert(String word) {
        TrieNode cur = root;
        for (char c : word.toCharArray()) {
            if (cur.children[c-'a']==null) cur.children[c-'a']=new TrieNode();
            cur=cur.children[c-'a']; cur.prefixCount++;
        }
        cur.isEnd=true;
    }
    boolean search(String word) {
        TrieNode cur=root;
        for(char c:word.toCharArray()){if(cur.children[c-'a']==null)return false;cur=cur.children[c-'a'];}
        return cur.isEnd;
    }
    boolean startsWith(String prefix) {
        TrieNode cur=root;
        for(char c:prefix.toCharArray()){if(cur.children[c-'a']==null)return false;cur=cur.children[c-'a'];}
        return true;
    }
}
```

### 2–5. (Prefix search, Count prefix, Longest common prefix, Delete — built on top of basic Trie using the same patterns)

---

## 🟡 MEDIUM

### 6. Word Search II (Boggle)
**Problem:** Given a board and word list, find all words that can be formed by adjacent cells.
**Approach:** Build trie from word list. DFS on each cell through the trie.

```cpp
void dfs(vector<vector<char>>& board, int r, int c, TrieNode* node, string& path, vector<string>& res) {
    if (r<0||r>=(int)board.size()||c<0||c>=(int)board[0].size()||board[r][c]=='#') return;
    char ch = board[r][c];
    if (!node->children[ch-'a']) return;
    node = node->children[ch-'a']; path += ch;
    if (node->isEnd) { res.push_back(path); node->isEnd = false; } // Avoid dups
    board[r][c] = '#'; // Mark visited
    dfs(board,r+1,c,node,path,res); dfs(board,r-1,c,node,path,res);
    dfs(board,r,c+1,node,path,res); dfs(board,r,c-1,node,path,res);
    board[r][c] = ch; path.pop_back();
}
vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
    Trie trie; for (auto& w:words) trie.insert(w);
    vector<string> res; string path;
    for (int r=0;r<(int)board.size();r++) for (int c=0;c<(int)board[0].size();c++)
        dfs(board,r,c,trie.root,path,res);
    return res;
}
```

### 9. Add & Search with Wildcard (`.` matches any)
```cpp
bool searchWild(TrieNode* node, string& word, int idx) {
    if (idx==(int)word.size()) return node->isEnd;
    if (word[idx]=='.') {
        for (int i=0;i<26;i++) if (node->children[i] && searchWild(node->children[i],word,idx+1)) return true;
        return false;
    }
    if (!node->children[word[idx]-'a']) return false;
    return searchWild(node->children[word[idx]-'a'],word,idx+1);
}
```

### 10. Maximum XOR of Two Numbers
**Approach:** Insert all numbers bit-by-bit (MSB first) into a bitwise trie. For each number, greedily choose opposite bits.

```cpp
int findMaximumXOR(vector<int>& nums) {
    struct BitNode { BitNode* ch[2]={}; };
    BitNode* root = new BitNode();
    // Insert all numbers
    for (int n:nums) { BitNode* cur=root;
        for (int i=31;i>=0;i--) { int bit=(n>>i)&1; if(!cur->ch[bit]) cur->ch[bit]=new BitNode(); cur=cur->ch[bit]; }
    }
    int maxXor=0;
    for (int n:nums) { BitNode* cur=root; int curXor=0;
        for (int i=31;i>=0;i--) { int bit=(n>>i)&1; int want=1-bit;
            if (cur->ch[want]) { curXor|=(1<<i); cur=cur->ch[want]; } else cur=cur->ch[bit];
        }
        maxXor=max(maxXor,curXor);
    }
    return maxXor;
}
```
**O(32n) ≈ O(n).**

---

## 🔴 HARD

### 11–13. (Palindrome Pairs uses trie + reverse-word matching. Word Concatenation uses trie + DP. Stream matching is a simplified Aho-Corasick.)

---

## 🗺️ Pattern Summary

| Pattern | Problems |
|---------|----------|
| Basic Trie | Implement, Search, Prefix Count |
| Trie + DFS/Backtrack | Word Search II, Wildcard Search |
| Bitwise Trie | Maximum XOR |
| Trie + DP | Word Concatenation |
