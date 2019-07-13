#include "CommandTrie.h"

using namespace std;

void CommandTrie::TrieNode::TrieNode(char letter = NULL) : 
    letter{letter},
    terminalLetter{false} {}

void CommandTrie::CommandTrie() {
    
}

void CommandTrie::insert(string command) {
    TrieNode curr = root;
    for (char letter : command) {
        iterator<TrieNode> next = curr.find(letter);
        if ()
    }
}

string CommandTrie::interpretInput(string input) {

}