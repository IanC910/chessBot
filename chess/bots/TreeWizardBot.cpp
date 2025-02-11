
#include <iostream>

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
    buildTree(root, 0);
    std::cout << "Tree size: " << treeSize << "\n";

    // Choose a move
    TreeNode* maxValueChild = root->children.front();
    int maxValue = -100; // Arbitrary low number
    int maxValueChildIndex = 0;
    int i = 0;
    for (TreeNode* child : root->children) {
        int value = getNodeValue(child, 1);
        if (value > maxValue) {
            maxValue = value;
            maxValueChild = child;
            maxValueChildIndex = i;
        }
        ++i;
    }

    std::cout << "Max value found: " << maxValue << "\n";

    // Get move
    BoardAnalyzer boardAnalyzer(root->board);
    std::list<Move> availableMoves;
    boardAnalyzer.getAllMoves(availableMoves, getColour());
    std::list<Move>::iterator moveIt = availableMoves.begin();
    for (int i = 0; i < maxValueChildIndex; i++) {
        moveIt++;
    }

    Move move = *moveIt;
    
    // Trim again
    reRootTree(maxValueChild);

    return move;
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
            // Lose
            if (turnColour == getColour()) {
                return -200 + depth;
            }

            // Else: win
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

    int* nodeValues = new int[node->children.size()];
    int minValueIndex = 0;
    int maxValueIndex = 0;

    int nodeIndex = 0;
    for(TreeNode* child : node->children) {
        nodeValues[nodeIndex] = getNodeValue(child, depth + 1);

        if (nodeValues[nodeIndex] < nodeValues[minValueIndex]) {
            minValueIndex = nodeIndex;
        }
        else if (nodeValues[nodeIndex] > nodeValues[maxValueIndex]) {
            maxValueIndex = nodeIndex;
        }

        ++nodeIndex;
    }

    if (depth % 2 == 0) {
        return nodeValues[maxValueIndex];
    }

    return nodeValues[minValueIndex];
}
