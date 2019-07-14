#include "CommandTrie.h"

CommandTrie::TrieNode::TrieNode(char letter) : 
    letter{letter},
    terminalLetter{false} {}

CommandTrie::CommandTrie(): root{'\0'} {
    
}

void CommandTrie::insert(string command) {
    TrieNode curr = root;
    for (char letter : command) {
        // iterator<TrieNode> next = curr.find(letter);
    }
}

string CommandTrie::interpretInput(string input) {

}