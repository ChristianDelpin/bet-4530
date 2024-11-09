/*

TODO: 
    Make this a repository so I can access anywhere. Thanks babes.

*/

#include <stack>
#include <string>
#include <sstream>

#include "bet.h"

BET::BET() : root(nullptr) {}

BET::~BET()
{
    makeEmpty(root);
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

void BET::printInfixExpression(BinaryNode* n) const 
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

void BET::printInfixExpression() const
{
    printInfixExpression(root);
    std::cout << std::endl;
}