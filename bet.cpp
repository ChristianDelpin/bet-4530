#ifndef BET_HPP
#define BET_HPP

#include <stack>
#include <string>
#include <sstream>
#include <iostream>

#include "bet.h"

BET::BET() : root(nullptr) {}

BET::BET(const std::string postfix) : root(nullptr)
{
//std::cout << "Inside BET(postfix)" << std::endl;
    buildFromPostfix(postfix);
}

BET::BET(const BET& b) : root(nullptr)
{
    root = clone(b.root);
}

BET::~BET()
{
    makeEmpty(root);
}

bool BET::empty()
{
    return root == nullptr;
}

bool BET::buildFromPostfix(const std::string postfix)
{
//std::cout << "inside buildFromPostfix()" << std::endl;
    std::istringstream iss(postfix);
    std::stack<BinaryNode*> nodeStack;
    std::string token;

    makeEmpty(root);  // Clear the existing tree

    while (iss >> token)
    {
        if (isdigit(token[0]) || isalpha(token[0]))
            nodeStack.push(new BinaryNode(token));

        else if (token == "+" || token == "-" || token == "*" || token == "/")
        {
            if (nodeStack.size() < 2)
            {
                std::cerr << "Error: Invalid postfix expression (not enough operands for operator '" << token << "')." << std::endl;
                return false;
            }

            BinaryNode* right = nodeStack.top(); nodeStack.pop();
            BinaryNode* left = nodeStack.top(); nodeStack.pop();

            // Create a new node with the operator and push it onto the stack
            nodeStack.push(new BinaryNode(token, left, right));
        } 
        // Invalid token
        else {
            std::cerr << "Error: Invalid token '" << token << "' in postfix expression." << std::endl;
            return false;
        }
    }

    // After processing all tokens, there should be exactly *one* element on the stack
    if (nodeStack.size() != 1) {
        std::cerr << "Error: Invalid postfix expression (too many operands or missing operators)." << std::endl;
        return false;
    }

    // Set the root of the tree to the last remaining element on the stack
    root = nodeStack.top();
    return true;
}

void BET::printInfixExpression()
{
    printInfixExpression(root);
    std::cout << std::endl;
}

void BET::printPostfixExpression()
{
    printPostfixExpression(root);
    std::cout << std::endl;
}

size_t BET::size()
{
    return size(root);
}

size_t BET::leaf_nodes()
{
    return leaf_nodes(root);
}

const BET& BET::operator=(const BET& b)
{
    if(this != &b)
    {
        makeEmpty(root);
        root = clone(b.root);
    }
    return *this;
}

void BET::printInfixExpression(BinaryNode* n)
{
    if (n != nullptr)
    {
        if (n->left && n->right)
            std::cout << "(";
	
        printInfixExpression(n->left);
        std::cout << " " << n->element << " ";
        printInfixExpression(n->right);
        
        if (n->left && n->right)
            std::cout << ")";
    }
}

void BET::makeEmpty(BinaryNode*& n)
{
//std::cout << "inside makeEmpty()" << std::endl;

//std::cout << "root == nullptr: " << (root==nullptr) << std::endl;
    if(n != nullptr)
    {
//std::cout << "beginning makeEmpty(n->left)" << std::endl;
        makeEmpty(n->left);
//std::cout << "beginning makeEmpty(N->RIGHT)" << std::endl;
        makeEmpty(n->right);
//std::cout << "deleting n..." << std::endl;
        delete n;
//std::cout << "delete n successful" << std::endl;
        n = nullptr;
//std::cout << "n = nullptr success" << std::endl;
    }
}

BET::BinaryNode* BET::clone(BinaryNode* t) const
{
    if(t == nullptr)
        return nullptr;
    return new BinaryNode(t->element, clone(t->left), clone(t->right));
}

void BET::printPostfixExpression(BinaryNode* n)
{
    if (n != nullptr)
    {
        // Postorder traversal: left, right, root
        printPostfixExpression(n->left);
        printPostfixExpression(n->right);
        std::cout << n->element << " ";
    }
}

size_t BET::size(BET::BinaryNode* n)
{
    if (n == nullptr)
        return 0;
    return 1 + size(n->left) + size(n->right);
}

size_t BET::leaf_nodes(BET::BinaryNode* n)
{
    if(n == nullptr)
        return 0;
    if(n->left == nullptr && n->right == nullptr)
        return 1;
    return leaf_nodes(n->left) + leaf_nodes(n->right);
}

#endif
