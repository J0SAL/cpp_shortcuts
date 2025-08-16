#include <bits/stdc++.h>
using namespace std;

class TrieNode {
public:
    vector<int> children;
    int nodecnt, endhere;
    TrieNode(){
        children.resize(26, -1);
        nodecnt = 0;
        endhere = 0;
    }
};

class Trie {
public:
    vector<TrieNode> trieroot;
    int triesize = 0;

    Trie() {
        trieroot.push_back(TrieNode());
        triesize++;
    }

    void insert(const string &word) {
        int curr = 0;
        for (char ch : word) {
            int idx = ch - 'a';
            if (trieroot[curr].children[idx] == -1) {
                trieroot[curr].children[idx] = triesize;
                trieroot.push_back(TrieNode());
                triesize++;
            }
            curr = trieroot[curr].children[idx];
            trieroot[curr].nodecnt++;
        }
        trieroot[curr].endhere++;
    }


    void deletenode(const string &s) {
        int curr = 0;
        for (char ch : s) {
            int idx = ch - 'a';
            int child = trieroot[curr].children[idx];
            if (child == -1) return; 
            trieroot[child].nodecnt--;
            if(trieroot[child].nodecnt == 0)
                trieroot[curr].children[idx] = -1;
            curr = child;
        }
        trieroot[curr].endhere--;
    }

    bool find(string word) {
        string res = "";
        int curr = 0;
        for(char &ch: word){
            res += ch;
            if(trieroot[curr].children[ch - 'a'] == -1)
                return false;
            curr = trieroot[curr].children[ch - 'a'];
        }
        return trieroot[curr].endhere > 0;
    }

};
