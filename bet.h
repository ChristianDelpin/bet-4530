class BET
{
    public:
        BET();
        BET(const string postfix);
        BET(const BET& b);
        ~BET();
        
        bool empty();
        bool buildFromPostfix(const string postfix);
        void printInfixExpression();
        void printPostfixExpression();
        size_t size();
        size_t leaf_nodes();
        
        const BET& operator=(const BET& b);

    private:
    //ALL REQUIRED PRIVATE MEMBERS MUST BE IMPLEMENTED RECURSIVELY
        void printInfixExpression(BinaryNode* n);
        void makeEmpty(BinaryNode*& t);
        BinaryNode* clone(BinaryNode* t) const;
        void printPostfixExpression(BinaryNode* n);
        size_t size(BinaryNode* n);
        size_t leaf_nodes(BinaryNode* n);

        struct BinaryNode
        {
            std::string element;
            BinaryNode* left;
            BinaryNode* right;
            BinaryNode(const std::string& e, BinaryNode* l = nullptr, BinaryNode* r = nullptr)
            : element(e), left(l), right(r) {}
        };
};