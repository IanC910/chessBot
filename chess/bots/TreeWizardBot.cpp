
#include <chrono>
#include <iostream>
#include <list>

#include "TreeWizardBot.hpp"

using namespace Chess;

TreeWizardBot::TreeWizardBot(int maxTreeDepth) {
    if (maxTreeDepth < 2) {
        maxTreeDepth = 2;
    }
    this->maxTreeDepth = maxTreeDepth;
}

Move TreeWizardBot::takeTurn(const Board& board) {
    if (root == nullptr) {
        root = new TreeNode(board);
    }
    else {
        // Figure out which of the root's children is the new board
        TreeNode* newRoot = nullptr;
        for (TreeNode* child : root->children) {
            if (child->board == board) {
                newRoot = child;
                break;
            }
        }

        // Trim unused branches, re root
        reRootTree(newRoot);
    }
    treeSize = 1;
    auto buildStartTime = std::chrono::high_resolution_clock::now();
    buildTree(root, 0);
    auto buildStopTime = std::chrono::high_resolution_clock::now();
    auto buildTimeMs = std::chrono::duration_cast<std::chrono::milliseconds>(buildStopTime - buildStartTime);
    std::cout << "Tree size: " << treeSize << ", built in " << buildTimeMs.count() << " ms\n";

    // Choose a move
    auto evalStartTime = std::chrono::high_resolution_clock::now();
    int maxValue = -1000000; // Arbitrary low number
    std::vector<int> maxValueChildIndices;
    maxValueChildIndices.reserve(root->children.size());
    for(int i = 0; i < root->children.size(); i++) {
        int value = getNodeValue(root->children[i], 1);
        // Hold all children with same value
        if (value == maxValue) {
            maxValueChildIndices.push_back(i);
        }
        else if (value > maxValue) {
            maxValue = value;
            maxValueChildIndices.clear();
            maxValueChildIndices.push_back(i);
        }
    }
    auto evalStopTime = std::chrono::high_resolution_clock::now();
    auto evalTimeMs = std::chrono::duration_cast<std::chrono::milliseconds>(evalStopTime - evalStartTime);

    std::cout << "Max value: " << maxValue << ", found in " << evalTimeMs.count() << " ms\n";

    // Pick random move from max value moves
    int maxValueChildIndex = maxValueChildIndices[std::rand() % maxValueChildIndices.size()];
    TreeNode* maxValueChild = root->children[maxValueChildIndex];

    // Get move
    BoardAnalyzer boardAnalyzer(root->board);
    std::list<Move> availableMoves;
    boardAnalyzer.getAllMoves(availableMoves, getColour());
    std::list<Move>::iterator moveIt = availableMoves.begin();
    for (int i = 0; i < maxValueChildIndex; i++) {
        ++moveIt;
    }
    Move chosenMove = *moveIt;
    
    // Trim again
    reRootTree(maxValueChild);

    return chosenMove;
}

TreeWizardBot::TreeNode::TreeNode(const Board& board) {
    this->board = board;
}

TreeWizardBot::TreeNode::~TreeNode() {
    for (TreeNode* child : children) {
        delete child;
    }
}

void TreeWizardBot::buildTree(TreeNode* node, int depth) {
    if (node == nullptr) {
        return;
    }

    if (depth == 0) {
        treeSize = 1;
    }

    // Populate node's children if empty
    if (node->children.empty()) {
        BoardAnalyzer boardAnalyzer(node->board);
        std::list<Move> availableMoves;
        Colour turnColour = (depth % 2 == 0) ? getColour() : getOppositeColour(getColour());
        boardAnalyzer.getAllMoves(availableMoves, turnColour);
        node->children.reserve(availableMoves.size());

        for (Move& move : availableMoves) {
            TreeNode* newChild = new TreeNode(node->board);
            newChild->board.doMove(move);
            node->children.push_back(newChild);
        }

        treeSize += node->children.size();
    }

    // Add children to queue if not reached max depth
    if (depth + 1 < maxTreeDepth) {
        for (TreeNode* child : node->children) {
            buildTree(child, depth + 1);
        }
    }
}

void TreeWizardBot::reRootTree(TreeNode* newRoot) {
    for (TreeNode*& child : root->children) {
        if (child == newRoot) {
            child = nullptr;
            break;
        }
    }

    delete root;
    root = newRoot;
}

int TreeWizardBot::evaluateBoard(const Board& board, Colour turnColour, int depth) {
    BoardAnalyzer boardAnalyzer(board);
    std::list<Move> availableMoves;
    boardAnalyzer.getAllMoves(availableMoves, turnColour);

    // If no moves
    if (availableMoves.empty()) {
        // If checkmate
        if(boardAnalyzer.isKingChecked(turnColour)) {
            // Lose, higher depth -> greater score
            if (turnColour == getColour()) {
                return -200 + depth;
            }

            // Else: win, higher depth -> lower score
            return 200 - depth;
        }
        
        // Else: stalemate
        return 0;
    }

    // Standard scenario
    return board.getMaterialValue() * COLOUR_VALUE_MODIFIERS[getColour()];
}

int TreeWizardBot::getNodeValue(TreeNode* node, int depth) {
    Colour turnColour = (depth % 2 == 0) ? getColour() : getOppositeColour(getColour());
    if (node->children.empty()) {
        return evaluateBoard(node->board, turnColour, depth);
    }

    int numChildren = node->children.size();
    int* childValues = new int[numChildren];
    int minValueIndex = 0;
    int maxValueIndex = 0;

    for(int i = 0; i < numChildren; i++) {
        childValues[i] = getNodeValue(node->children[i], depth + 1);

        if (childValues[i] < childValues[minValueIndex]) {
            minValueIndex = i;
        }
        else if (childValues[i] > childValues[maxValueIndex]) {
            maxValueIndex = i;
        }
    }

    if (depth % 2 == 0) {
        return childValues[maxValueIndex];
    }

    return childValues[minValueIndex];
}
