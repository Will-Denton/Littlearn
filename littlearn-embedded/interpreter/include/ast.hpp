#ifndef AST_HPP
#define AST_HPP

#include <vector>
#include <string>
#include <iostream>
#include "tokenizer.hpp"

// Forward declarations of AST node classes
class ASTNode; // virtual base class
class BlockNode; // block node for scope (e.g. function body, if statement body, while loop body)
class VariableDeclarationNode;
class AssignmentNode;
class VariableAccessNode;
class NumberNode;
class BinaryOperationNode;
class IfNode;
class PrintNode;

class Parser {
public:
    Parser(const std::vector<Token>& tokens);

    BlockNode* parseProgram(); // Entry point for parsing a program into an AST

    // Making these public to make testing easier

    // The functions to parse each type of AST node
    BlockNode* parseBlock();
    VariableDeclarationNode* parseVariableDeclaration();
    AssignmentNode* parseAssignment();
    VariableAccessNode* parseVariableAccess();
    NumberNode* parseConstant();
    IfNode* parseIfStatement();
    PrintNode* parsePrint();

    std::vector<const Token*> gatherTokensUntil(TokenType endTokenType, bool advanceIndex);

    ASTNode* parseStatement();
    ASTNode* parseExpression(std::vector<const Token*> expressionTokens); // Should result in a single AST node for an expression, constant or variable access
    ASTNode* parseSimpleExpression(std::vector<const Token*> exprTokens, std::vector<ASTNode*> nodes); // Parse from parallel vectors of tokens and nodes
    ASTNode* parseBinaryExpression();
    size_t getPrecedence(std::string lexeme);

    void eatToken(TokenType expectedTokenType);

    void syntaxError(const std::string& message);

    
private:
    const std::vector<Token>& tokens;
    size_t currentTokenIndex;

    
};

// Define a base class for all nodes
class ASTNode {
public:
    virtual std::string toString() const = 0;
    virtual ~ASTNode() = default;
};

// Define a class for housing a block of code
// (e.g. function body, if statement body, while loop body)
// Variables declared in a block are scoped to that block
class BlockNode : public ASTNode {
public:
    BlockNode(const std::vector<ASTNode*>& statements);

    std::string toString() const override;

    std::vector<ASTNode*> getStatements() const;

    ~BlockNode();

private:
    std::vector<ASTNode*> statements;

};

// Define a class for variable declarations
class VariableDeclarationNode : public ASTNode {
public:
    VariableDeclarationNode(const std::string& identifier, const std::string& type, ASTNode* initializer);

    std::string toString() const override;
    std::string getIdentifier() const;
    std::string getType() const;
    ASTNode* getInitializer() const;

    ~VariableDeclarationNode();

private:
    std::string identifier;
    std::string type;
    ASTNode* initializer;

};

// Define a class for variable assignments
class AssignmentNode : public ASTNode {
public:
    AssignmentNode(const std::string& identifier, ASTNode* expression);
    ~AssignmentNode();


    std::string toString() const override;

    std::string getIdentifier() const;

    ASTNode* getExpression() const;

private:
    std::string identifier;
    ASTNode* expression;

};

// Define a class for variable access
class VariableAccessNode : public ASTNode {
public:
    VariableAccessNode(const std::string& identifier);

    std::string toString() const override;

    std::string getIdentifier() const;

    ~VariableAccessNode();

private:
    std::string identifier;

};

// Define a class for integer literals
class NumberNode : public ASTNode {
public:
    NumberNode(std::string val, TokenType type);

    std::string toString() const override;

    ~NumberNode();

    TokenType getType() const;

    std::string getValue() const;

private:
    std::string value;
    TokenType type;

};

// Define a class for binary operations
class BinaryOperationNode : public ASTNode {
public:
    BinaryOperationNode(ASTNode* left, std::string op, ASTNode* right);

    std::string toString() const override;

    ASTNode* getLeftExpression() const;
    ASTNode* getRightExpression() const;
    std::string getOperator() const;

    ~BinaryOperationNode();

private:
    ASTNode* left;
    std::string op;
    ASTNode* right;

};

class IfNode : public ASTNode {
public:
    IfNode(ASTNode* expression, BlockNode* body);

    std::string toString() const override;

    ~IfNode();

private:
    ASTNode* expression;
    BlockNode* body;

};

class PrintNode : public ASTNode {
public:
    PrintNode(ASTNode* expression);

    std::string toString() const override;

    ASTNode* getExpression() const;

    ~PrintNode();

private:
    ASTNode* expression;

};

#endif // AST_HPP