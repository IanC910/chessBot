
#pragma once

#include <list>

#include "../core/core.hpp"

class TreeWizardBot : public Chess::Player {
public:
    TreeWizardBot(int maxTreeDepth = 2);

    Chess::Move takeTurn(const Chess::Board& board) override;
private:

    class TreeNode {
    public:
        Chess::Board board;
        std::list<TreeNode*> children;

        TreeNode(const Chess::Board& board);
        ~TreeNode();
    };

    TreeNode* root = nullptr;
    int maxTreeDepth = 2;
    int treeSize = 0;

    void buildTree(TreeNode* node, int depth);
    void reRootTree(TreeNode* newRoot);

    int evaluateBoard(const Chess::Board& board, Chess::Colour turnColour);
    int getNodeValue(TreeNode* node, int depth);
};

