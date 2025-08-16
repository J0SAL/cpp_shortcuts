class Trie {
    class TrieNode {
    public:
        TrieNode *children[2];
        int nodecnt;
        TrieNode(){
            for(int i=0; i<2; i++)
                children[i] = NULL;
                nodecnt = 0;
        }
    };
public:
    TrieNode *root;
    Trie() {
        root = new TrieNode();
    }
    
    void insert(int num) {
        TrieNode *curr = root;
        for(int i=31; i>=0; i--){
            int idx = (num>>i) & 1;
            if(curr->children[idx] == NULL)
                curr->children[idx] = new TrieNode();
            curr = curr->children[idx];
            curr->nodecnt++;
        }
    }
    
    int find(int num) {
        TrieNode *curr = root;
        int res = 0;
        for(int i=31; i>=0; i--){
            int idx = (num>>i) & 1;
            int oppidx = !idx;
            if(curr->children[oppidx] != NULL){
                res |= (1<<i);
                curr = curr->children[oppidx];
            }else{
                curr = curr->children[idx];
            }
        }
        return res;
    }
    void deleterecursive(TrieNode *curr){
        if(curr == NULL) return;
        for(int i=0; i<2; i++){
            deleterecursive(curr->children[i]);
            TrieNode *tmp = curr->children[i];
            curr->children[i] = NULL;
            delete tmp;
        }
    }

    void deletenode(int num){
        TrieNode *curr = root;
        for(int i=31; i>=0; i--){
            int idx = (num>>i) & 1;
            if(curr->children[idx] && curr->children[idx]->nodecnt > 1){
                curr->children[idx]->nodecnt--;
                curr = curr->children[idx];
                continue;
            }

            deleterecursive(curr->children[idx]);
            TrieNode *tmp = curr->children[idx];
            curr->children[idx] = NULL;
            delete tmp;
            break;
        }
    }
};
