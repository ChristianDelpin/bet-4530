#ifndef BET_HPP
#define BET_HPP

#include <stack>
#include <string>
#include <sstream>
#include <iostream>

#include "bet.h"

BET::BET() : root(nullptr) {}

BET::BET(const std::string postfix)
{
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
    std::istringstream iss(postfix);
    std::stack<BinaryNode*> nodeStack;
    std::string token;

    makeEmpty(root);  // Clear the existing tree

    while (iss >> token) 
    {
        if (isdigit(token[0])) 
        {  // Operand
            nodeStack.push(new BinaryNode(token));
        } 
        else 
        {  // Operator
            if (nodeStack.size() < 2) 
                return false;
            
            BinaryNode* right = nodeStack.top(); 
            nodeStack.pop();
            
            BinaryNode* left = nodeStack.top(); 
            nodeStack.pop();
            
            nodeStack.push(new BinaryNode(token, left, right));
        }
    }
    if (nodeStack.size() != 1) 
        return false;
    
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
    if(n != nullptr)
    {
        makeEmpty(n->left);
        makeEmpty(n->right);
        delete n;
        n = nullptr;
    }
}

BET::BinaryNode* BET::clone(BinaryNode* t) const
{
    if(t==nullptr)
        return nullptr;
    return new BinaryNode(t->element, clone(t->left), clone(t->right));
}

void BET::printPostfixExpression(BinaryNode* n)
{
    if(n != nullptr)
    {
        bool isOper = (n->element == "+" || n->element == "-" || n->element == "*" || n->element == "/");

        if(isOper && n->left && n->right)
            std::cout << "(";

        printInfixExpression(n->left);
        std::cout << n->element;
        printInfixExpression(n->right);

        if(isOper && n->left && n->right)
            std::cout << ")";
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