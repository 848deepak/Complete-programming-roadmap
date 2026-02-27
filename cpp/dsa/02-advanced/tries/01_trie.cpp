// ============================================================
// DSA | C++ → Trie (Prefix Tree)
// ============================================================
// DESCRIPTION:
//   A Trie (pronounced "try") is a tree-like data structure for
//   efficient string storage and prefix-based retrieval.
//
//   Each node represents ONE CHARACTER. A path from root to a
//   marked node spells a complete word.
//
// STRUCTURE:
//   root → 'a' → 'p' → 'p' → [end]   "app"
//              → 'e' → [end]           "ape"
//
// OPERATIONS COVERED:
//   - insert(word)           O(L)
//   - search(word)           O(L)   exact word match
//   - startsWith(prefix)     O(L)   prefix match
//   - countWordsWithPrefix   O(L)
//   - delete(word)           O(L)
//   - autocomplete           O(L + N) N = results
//
// APPLICATIONS:
//   - Autocomplete / Search suggestions
//   - Spell checker
//   - IP routing tables (bitwise trie)
//   - Word games (Boggle, Scrabble)
//
// COMPILE & RUN:
//   g++ -std=c++17 01_trie.cpp -o out && ./out
//
// COMPLEXITY:
//   All operations : O(L) — L = length of word/prefix
//   Space          : O(N * A) — N words, A = alphabet size (26)
// ============================================================

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

// ============================================================
// TRIE NODE
// ============================================================

struct TrieNode {
    TrieNode* children[26];  // one slot per lowercase letter (a–z)
    bool      isEnd;         // true if this node completes a word
    int       count;         // how many words pass through this node (for prefix count)
    int       wordCount;     // how many complete words end here (for duplicates)

    TrieNode() : isEnd(false), count(0), wordCount(0) {
        fill(begin(children), end(children), nullptr);
    }
};

// ============================================================
// TRIE CLASS
// ============================================================

class Trie {
    TrieNode* root_;

    /** Maps 'a'–'z' → index 0–25 */
    int idx(char c) const { return c - 'a'; }

public:
    Trie() : root_(new TrieNode()) {}

    // -------------------------------------------------------
    // INSERT: O(L)
    // -------------------------------------------------------
    /**
     * Inserts word into the trie.
     * Creates nodes for each character if they don't exist.
     * Marks the last node as a word ending.
     *
     * @param word  Lowercase English letters only
     */
    void insert(const string& word) {
        TrieNode* curr = root_;
        for (char ch : word) {
            int i = idx(ch);
            if (!curr->children[i])
                curr->children[i] = new TrieNode();   // create missing node
            curr = curr->children[i];
            curr->count++;    // this node is part of one more word's prefix
        }
        curr->isEnd = true;
        curr->wordCount++;   // supports duplicate insertions
    }

    // -------------------------------------------------------
    // SEARCH: O(L)
    // -------------------------------------------------------
    /**
     * Returns true if word exists in the trie (exact match).
     */
    bool search(const string& word) const {
        TrieNode* curr = root_;
        for (char ch : word) {
            int i = idx(ch);
            if (!curr->children[i]) return false;   // path broken
            curr = curr->children[i];
        }
        return curr->isEnd;   // path complete AND marked as a word
    }

    // -------------------------------------------------------
    // STARTS WITH (prefix check): O(L)
    // -------------------------------------------------------
    /**
     * Returns true if any word in the trie starts with prefix.
     */
    bool startsWith(const string& prefix) const {
        TrieNode* curr = root_;
        for (char ch : prefix) {
            int i = idx(ch);
            if (!curr->children[i]) return false;
            curr = curr->children[i];
        }
        return true;   // reached end of prefix — at least one word has this prefix
    }

    // -------------------------------------------------------
    // COUNT WORDS WITH PREFIX: O(L)
    // -------------------------------------------------------
    /**
     * Returns the number of words in the trie that begin with prefix.
     */
    int countWithPrefix(const string& prefix) const {
        TrieNode* curr = root_;
        for (char ch : prefix) {
            int i = idx(ch);
            if (!curr->children[i]) return 0;
            curr = curr->children[i];
        }
        return curr->count;   // count stored at last prefix node
    }

    // -------------------------------------------------------
    // AUTOCOMPLETE: O(L + N)
    // -------------------------------------------------------
    /**
     * Returns all words in the trie that start with prefix.
     * Uses DFS from the end of the prefix.
     *
     * @param prefix  Prefix to search
     * @return        Sorted list of matching words
     */
    vector<string> autocomplete(const string& prefix) const {
        TrieNode* curr = root_;
        for (char ch : prefix) {
            int i = idx(ch);
            if (!curr->children[i]) return {};   // prefix not found
            curr = curr->children[i];
        }

        vector<string> results;
        string current = prefix;
        dfs(curr, current, results);
        return results;
    }

    // -------------------------------------------------------
    // DELETE: O(L)
    // -------------------------------------------------------
    /**
     * Deletes a word from the trie.
     * Only removes nodes that become unreachable (no other words use them).
     *
     * @return  true if word was found and deleted
     */
    bool deleteWord(const string& word) {
        return deleteHelper(root_, word, 0);
    }

    // -------------------------------------------------------
    // LONGEST COMMON PREFIX: O(N * L)
    // -------------------------------------------------------
    /**
     * Returns the longest common prefix among all inserted words.
     */
    string longestCommonPrefix() const {
        string lcp;
        TrieNode* curr = root_;
        // Walk down as long as exactly one child exists and no word ends
        while (true) {
            int childCount = 0, childIdx = -1;
            for (int i = 0; i < 26; i++) {
                if (curr->children[i]) { childCount++; childIdx = i; }
            }
            if (childCount != 1 || curr->isEnd) break;   // branch or word end
            lcp += (char)('a' + childIdx);
            curr = curr->children[childIdx];
        }
        return lcp;
    }

private:
    /** DFS helper for autocomplete: collects all words reachable from node. */
    void dfs(TrieNode* node, string& current, vector<string>& results) const {
        if (node->isEnd) results.push_back(current);

        for (int i = 0; i < 26; i++) {
            if (node->children[i]) {
                current += (char)('a' + i);       // extend current word
                dfs(node->children[i], current, results);
                current.pop_back();               // backtrack
            }
        }
    }

    /** Recursive delete helper. Returns true if curr node can be deleted. */
    bool deleteHelper(TrieNode* curr, const string& word, int depth) {
        if (!curr) return false;

        if (depth == (int)word.size()) {
            if (!curr->isEnd) return false;   // word not in trie
            curr->isEnd = false;
            curr->wordCount--;
            // can delete this node only if it has no children
            for (int i = 0; i < 26; i++) if (curr->children[i]) return false;
            return true;   // safe to delete
        }

        int i = idx(word[depth]);
        if (!deleteHelper(curr->children[i], word, depth + 1)) return false;

        // Child was deleted
        delete curr->children[i];
        curr->children[i] = nullptr;
        curr->count--;

        // Can we delete curr? Only if it's not a word end and has no children
        if (curr->isEnd) return false;
        for (int j = 0; j < 26; j++) if (curr->children[j]) return false;
        return curr != root_;   // never delete root
    }
};

// ============================================================
// SECTION 2: TRIE WITH unordered_map (Unicode-friendly)
// ============================================================
// Using unordered_map<char, TrieNode*> instead of fixed array[26].
// Works for any character set (not just 'a'–'z').
// Slightly more memory-efficient for sparse alphabets.
// ------------------------------------------------------------ 

class UnicodeTrie {
    struct Node {
        unordered_map<char, Node*> children;
        bool isEnd = false;
    };
    Node* root_ = new Node();

public:
    void insert(const string& word) {
        Node* curr = root_;
        for (char ch : word) {
            if (!curr->children.count(ch))
                curr->children[ch] = new Node();
            curr = curr->children[ch];
        }
        curr->isEnd = true;
    }

    bool search(const string& word) const {
        Node* curr = root_;
        for (char ch : word) {
            if (!curr->children.count(ch)) return false;
            curr = curr->children.at(ch);
        }
        return curr->isEnd;
    }

    bool startsWith(const string& prefix) const {
        Node* curr = root_;
        for (char ch : prefix) {
            if (!curr->children.count(ch)) return false;
            curr = curr->children.at(ch);
        }
        return true;
    }
};

// ============================================================
// MAIN
// ============================================================
int main() {

    Trie trie;

    // --- Insert words ---
    cout << "=== TRIE INSERT ===" << "\n";
    vector<string> words = {"apple","app","application","apply","apt","banana","band","bandana"};
    for (const auto& w : words) {
        trie.insert(w);
        cout << "  inserted: " << w << "\n";
    }

    // --- Search ---
    cout << "\n=== SEARCH (exact match) ===" << "\n";
    for (const auto& w : {"apple","app","ap","banana","ban","xyz"}) {
        cout << "  search(\"" << w << "\"): " << (trie.search(w) ? "FOUND" : "not found") << "\n";
    }

    // --- startsWith ---
    cout << "\n=== STARTS WITH (prefix) ===" << "\n";
    for (const auto& p : {"app","ap","ban","xyz","b"}) {
        cout << "  startsWith(\"" << p << "\"): " << (trie.startsWith(p) ? "YES" : "NO") << "\n";
    }

    // --- Count words with prefix ---
    cout << "\n=== COUNT WORDS WITH PREFIX ===" << "\n";
    for (const auto& p : {"app","ap","ban","b","a"}) {
        cout << "  countWithPrefix(\"" << p << "\"): " << trie.countWithPrefix(p) << "\n";
    }

    // --- Autocomplete ---
    cout << "\n=== AUTOCOMPLETE ===" << "\n";
    for (const auto& p : {"app","b","ban","ap"}) {
        auto results = trie.autocomplete(p);
        cout << "  autocomplete(\"" << p << "\"): [";
        for (int i = 0; i < (int)results.size(); i++)
            cout << results[i] << (i+1<(int)results.size()?", ":"");
        cout << "]\n";
    }

    // --- Longest Common Prefix ---
    cout << "\n=== LONGEST COMMON PREFIX ===" << "\n";
    Trie lcp_trie;
    for (const auto& w : {"flower","flow","flight"}) lcp_trie.insert(w);
    cout << "  words: flower, flow, flight\n";
    cout << "  LCP: \"" << lcp_trie.longestCommonPrefix() << "\"\n";   // "fl"

    Trie lcp2;
    for (const auto& w : {"dog","racecar","car"}) lcp2.insert(w);
    cout << "  words: dog, racecar, car\n";
    cout << "  LCP: \"" << lcp2.longestCommonPrefix() << "\"\n";   // ""

    // --- Delete ---
    cout << "\n=== DELETE ===" << "\n";
    cout << "  search(\"apple\") before delete: " << (trie.search("apple") ? "FOUND" : "not found") << "\n";
    trie.deleteWord("apple");
    cout << "  search(\"apple\") after delete:  " << (trie.search("apple") ? "FOUND" : "not found") << "\n";
    cout << "  search(\"app\") still exists:     " << (trie.search("app")   ? "FOUND" : "not found") << "\n";

    // --- Edge cases ---
    cout << "\n=== EDGE CASES ===" << "\n";
    Trie edge;
    edge.insert("a");
    cout << "  single char 'a': search=" << edge.search("a") << " startsWith=" << edge.startsWith("a") << "\n";
    edge.insert("a");    // insert duplicate
    cout << "  duplicate insert 'a': still searchable=" << edge.search("a") << "\n";
    edge.deleteWord("a");
    cout << "  after one delete, still searchable (second 'a' remains)=" << edge.search("a") << "\n";

    // --- Unicode Trie demo ---
    cout << "\n=== UNICODE TRIE ===" << "\n";
    UnicodeTrie utf;
    utf.insert("hello"); utf.insert("world"); utf.insert("he");
    cout << "  search(\"hello\"): " << utf.search("hello") << "\n";
    cout << "  search(\"hell\"): "  << utf.search("hell") << "\n";
    cout << "  startsWith(\"he\"): " << utf.startsWith("he") << "\n";

    return 0;
}

// ============================================================
// COMPLEXITY SUMMARY
//   insert          : O(L) time, O(L) space (new nodes)
//   search          : O(L) time, O(1) space
//   startsWith      : O(L) time, O(1) space
//   countWithPrefix : O(L) time, O(1) space
//   autocomplete    : O(L + M) M = total chars in all matching words
//   delete          : O(L) time
//   longestCommonPrefix: O(N*L) — N words, L avg length
//
// SPACE:
//   Fixed array[26] : O(N * 26) — 26 pointers per node
//   Hash map variant: O(N * avg_children) — more memory-efficient for sparse alphabets
//
// VS HASH SET:
//   HashSet insert/search: O(L) avg → same speed
//   Trie advantage: prefix queries, autocomplete, LCP — things HashSet can't do
// ============================================================
