#ifndef COMMAND_TRIE_H_
#define COMMAND_TRIE_H_

#include <string>
#include <unordered_map>

using std::string;
using std::unordered_map;

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
};

#endif