class CommandTrie {
        
    class TrieNode {
        
        char letter;
        bool terminalLetter;
        string suggestion;
        unordered_map<char, TrieNode> children;
    
        public:
            TrieNode(char);
    };
    
    TrieNode root;
    void insert(string);
    
    public:
        CommandTrie();
        string interpretInput(string);
}