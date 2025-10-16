#include <bits/stdc++.h>
#include <conio.h> 

using namespace std;

struct TrieNode {
    bool isEnd = false;
    array<TrieNode*, 26> children = {nullptr};
};

class Trie {
    TrieNode* root;
public:
    Trie() { root = new TrieNode(); }

    void insert(const string& word) {
        TrieNode* node = root;
        for (char c : word) {
            c = tolower(c);
            if (c < 'a' || c > 'z') continue; 
            if (!node->children[c - 'a'])
                node->children[c - 'a'] = new TrieNode();
            node = node->children[c - 'a'];
        }
        node->isEnd = true;
    }

    void collect(TrieNode* node, string prefix, vector<string>& results, int limit = 10) {
        if (!node || results.size() >= limit) return;
        if (node->isEnd) results.push_back(prefix);
        for (int i = 0; i < 26 && results.size() < limit; i++) {
            if (node->children[i])
                collect(node->children[i], prefix + char('a' + i), results, limit);
        }
    }

    vector<string> suggest(const string& prefix, int limit = 10) {
        TrieNode* node = root;
        for (char c : prefix) {
            c = tolower(c);
            if (c < 'a' || c > 'z') return {};
            if (!node->children[c - 'a']) return {};
            node = node->children[c - 'a'];
        }
        vector<string> results;
        collect(node, prefix, results, limit);
        return results;
    }
};

int main() {
    Trie trie;

    
    vector<string> words = {
        "apple", "application", "apply", "appetizer", "apricot", "approach",
        "banana", "band", "bank", "basket", "battle",
        "cat", "catch", "coding", "code", "coder", "computer",
        "data", "database", "day", "define", "depth", "design",
        "error", "example", "easy", "effect", "energy",
        "finish", "fast", "feature", "final", "folder", "foot",
        "great", "group", "game", "global", "goal",
        "house", "happy", "health", "heavy", "history",
        "idea", "image", "input", "initialize", "implement",
        "jump", "job", "join", "just", "jungle"
    };

    for (auto& w : words) trie.insert(w);

    cout << "------ 🔍 Interactive Autocomplete (Trie) ------\n";
    cout << "Type letters to get suggestions (Backspace to delete, Enter to finish)\n\n";

    string prefix = "";
    char ch;

    while (true) {
        ch = _getch();  

        if (ch == 13) { 
            cout << "\n\n✅ Final prefix entered: " << prefix << endl;
            break;
        } else if (ch == 8) { 
            if (!prefix.empty()) prefix.pop_back();
        } else if (isalpha(ch)) {
            prefix += tolower(ch);
        } else {
            continue;
        }

        system("cls"); 
        cout << "------ 🔍 Interactive Autocomplete (Trie) ------\n";
        cout << "Type letters to get suggestions (Backspace=Delete, Enter=Finish)\n";
        cout << "\nCurrent prefix: " << (prefix.empty() ? "(none)" : prefix) << "\n\n";

        if (prefix.empty()) {
            cout << "Start typing to see suggestions...\n";
            continue;
        }

        vector<string> suggestions = trie.suggest(prefix);
        if (suggestions.empty()) {
            cout << "❌ No suggestions found for \"" << prefix << "\"\n";
        } else {
            cout << "💡 Suggestions:\n";
            for (auto& s : suggestions)
                cout << "  → " << s << "\n";
        }
    }

    cout << "\nThanks for trying the interactive autocomplete demo!\n";
    return 0;
}
