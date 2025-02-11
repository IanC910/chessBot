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

    buildTree(root, 0);

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

int TreeWizardBot::evaluateBoard(const Board& board) {
    return board.getMaterialValue() * COLOUR_VALUE_MODIFIERS[getColour()];
}

void TreeWizardBot::buildTree(TreeNode* node, int depth) {
    if (node == nullptr) {
        return;
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

int TreeWizardBot::getNodeValue(TreeNode* node, int depth) {
    if (node->children.empty()) {
        return evaluateBoard(node->board);
    }

    int* nodeValues = new int[node->children.size()];
    int minValueIndex = 0;
    int maxValueIndex = 0;

    int i = 0;
    for(TreeNode* child : node->children) {
        nodeValues[i] = getNodeValue(child, depth + 1);

        if (nodeValues[i] < nodeValues[minValueIndex]) {
            minValueIndex = i;
        }
        else if (nodeValues[i] > nodeValues[maxValueIndex]) {
            maxValueIndex = i;
        }

        ++i;
    }

    if (depth % 2 == 0) {
        return nodeValues[maxValueIndex];
    }

    return nodeValues[minValueIndex];
}
