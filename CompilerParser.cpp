#include "CompilerParser.h"
using namespace std;


/**
 * Constructor for the CompilerParser
 * @param tokens A linked list of tokens to be parsed
 */
CompilerParser::CompilerParser(std::list<Token*> tokens) {
    tokenList = tokens;
}

/**
 * Generates a parse tree for a single program
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileProgram() {
    if (!tokenList.empty() && tokenList.front()->getValue() != "class") {
    throw ParseException();
    }
    ParseTree* parseTree = new ParseTree("class", "");
    for (Token* token : tokenList) {
        std::string type = token->getType();
        std::string value = token->getValue();
        parseTree->addChild(new ParseTree(type, value));
}
    return parseTree;
}

/**
 * Generates a parse tree for a single class
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileClass() {

     if (tokenList.empty() || tokenList.front()->getValue() != "class") {

        throw ParseException();

    }


    ParseTree* parseTree = new ParseTree("class", "");

    ParseTree* currentSubtree = parseTree;  // Track the current subtree


    for (Token* token : tokenList) {

        std::string type = token->getType();

        std::string value = token->getValue();


        if (value == "static" || value == "field") {

            ParseTree* classVarDecSubtree = new ParseTree("classVarDec", "");

            currentSubtree->addChild(classVarDecSubtree);

            currentSubtree = classVarDecSubtree;  // Update current subtree

        } 

        if (value == "}"){

            currentSubtree = parseTree;

        }

        currentSubtree->addChild(new ParseTree(type, value));

        if (value == ";"){

            currentSubtree = parseTree;

        }

    }

    return parseTree;

}


/**
 * Generates a parse tree for a static variable declaration or field declaration
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileClassVarDec() {
    ParseTree* classVarDecTree = new ParseTree("classVarDec", "");

    // Add tokens until a semicolon is encountered or the token list is empty
    while (!tokenList.empty()) {
        std::string value = tokenList.front()->getValue();
        if (value == ";" || value == "}") {
            break;  // Exit the loop when encountering a semicolon or closing brace
        }

        classVarDecTree->addChild(parseToken());
    }

    return classVarDecTree;
}

/**
 * Generates a parse tree for a method, function, or constructor
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileSubroutine() {
     if (tokenList.empty() || tokenList.front()->getValue() != "function") {

        throw ParseException();

    }


    ParseTree* parseTree = new ParseTree("subroutine", "");

    ParseTree* currentSubtree = parseTree;  // Track the current subtree


    for (Token* token : tokenList) {

        std::string type = token->getType();

        std::string value = token->getValue();


        if (value == "int" && currentSubtree == parseTree) {

            ParseTree* parameterSubtree = new ParseTree("parameterList", "");

            currentSubtree->addChild(parameterSubtree);

            currentSubtree = parameterSubtree;  // Update current subtree

        } 
        if (value == "{") {
            ParseTree* subSubtree = new ParseTree("subroutineBody", "");

            currentSubtree->addChild(subSubtree);

            currentSubtree = subSubtree;  // Update current subtree

        }
        if (value == "var" ){
            ParseTree* varSubtree = new ParseTree("varDec", "");

            currentSubtree->addChild(varSubtree);

            currentSubtree = varSubtree;  // Update current subtree

        }
        if (value == "let"){
            ParseTree* statementSubtree = new ParseTree("statements", "");

            currentSubtree->addChild(statementSubtree);

            currentSubtree = statementSubtree;  // Update current subtree

        }

        if (value == ")"){

            currentSubtree = parseTree;

        }


        if (value == "}"){

            currentSubtree = parseTree;

        }

        currentSubtree->addChild(new ParseTree(type, value));

        if (value == ";"){

            currentSubtree = parseTree;

        }

    }

    return parseTree;
}

/**
 * Generates a parse tree for a subroutine's parameters
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileParameterList() {
    ParseTree* parseTree = new ParseTree("parameterList", "");
    for (Token* token : tokenList) {
        std::string type = token->getType();
        std::string value = token->getValue();
        parseTree->addChild(new ParseTree(type, value));
}
    return parseTree;
}

/**
 * Generates a parse tree for a subroutine's body
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileSubroutineBody() {
        if (tokenList.empty() || tokenList.front()->getValue() != "{") {

        throw ParseException();

    }


    ParseTree* parseTree = new ParseTree("subroutineBody", "");

    ParseTree* currentSubtree = parseTree;  // Track the current subtree


    for (Token* token : tokenList) {

        std::string type = token->getType();

        std::string value = token->getValue();


        if (value == "var") {

            ParseTree* classVarDecSubtree = new ParseTree("varDec", "");

            currentSubtree->addChild(classVarDecSubtree);

            currentSubtree = classVarDecSubtree;  // Update current subtree

        } 
        if (value == "let"){
            ParseTree* statementSubtree = new ParseTree("statements", "");

            currentSubtree->addChild(statementSubtree);

            currentSubtree = statementSubtree;  // Update current subtree

        }

        if (value == "}"){

            currentSubtree = parseTree;

        }

        currentSubtree->addChild(new ParseTree(type, value));

        if (value == ";"){

            currentSubtree = parseTree;

        }

    }

    return parseTree;
}

/**
 * Generates a parse tree for a subroutine variable declaration
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileVarDec() {
    if (tokenList.front()->getValue() != "var" || tokenList.front()->getType() != "keyword"){
        throw ParseException();
    }
    ParseTree* parseTree = new ParseTree("varDec", "");
    for (Token* token : tokenList) {
        std::string type = token->getType();
        std::string value = token->getValue();
        parseTree->addChild(new ParseTree(type, value));
}
    return parseTree;
}

/**
 * Generates a parse tree for a series of statements
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileStatements() {


    ParseTree* parseTree = new ParseTree("statements", "");

    ParseTree* currentSubtree = parseTree;  // Track the current subtree


    for (Token* token : tokenList) {

        std::string type = token->getType();

        std::string value = token->getValue();


        if (value == "let") {

            ParseTree* letSubtree = new ParseTree("letStatement", "");

            currentSubtree->addChild(letSubtree);

            currentSubtree = letSubtree;  // Update current subtree

        } 
        if (value == "do") {

            ParseTree* doSubtree = new ParseTree("doStatement", "");

            currentSubtree->addChild(doSubtree);

            currentSubtree = doSubtree;  // Update current subtree

        } 

        if (value == "skip"){
            ParseTree* exSubtree = new ParseTree("expression", "");

            currentSubtree->addChild(exSubtree);

            currentSubtree = exSubtree;  // Update current subtree


        }
        if (value == ";" && currentSubtree != parseTree){
            currentSubtree = parseTree;
        }


        currentSubtree->addChild(new ParseTree(type, value));

    }

    return parseTree;

}

/**
 * Generates a parse tree for a let statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileLet() {
    return NULL;
}

/**
 * Generates a parse tree for an if statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileIf() {
    return NULL;
}

/**
 * Generates a parse tree for a while statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileWhile() {
    return NULL;
}

/**
 * Generates a parse tree for a do statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileDo() {
    return NULL;
}

/**
 * Generates a parse tree for a return statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileReturn() {
    return NULL;
}

/**
 * Generates a parse tree for an expression
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileExpression() {
     if (tokenList.empty() || tokenList.front()->getValue() != "skip") {

        throw ParseException();

    }

    ParseTree* parseTree = new ParseTree("expression", "");

    ParseTree* currentSubtree = parseTree;  // Track the current subtree


    for (Token* token : tokenList) {

        std::string type = token->getType();

        std::string value = token->getValue();
        currentSubtree->addChild(new ParseTree(type, value));

    }

    return parseTree;
}

/**
 * Generates a parse tree for an expression term
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileTerm() {
    return NULL;
}

/**
 * Generates a parse tree for an expression list
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileExpressionList() {
    return NULL;
}

/**
 * Advance to the next token
 */
void CompilerParser::next(){
    return;
}

/**
 * Return the current token
 * @return the Token
 */
Token* CompilerParser::current(){
    return NULL;
}

/**
 * Check if the current token matches the expected type and value.
 * @return true if a match, false otherwise
 */
bool CompilerParser::have(std::string expectedType, std::string expectedValue){
    return false;
}

/**
 * Check if the current token matches the expected type and value.
 * If so, advance to the next token, returning the current token, otherwise throw a ParseException.
 * @return the current token before advancing
 */
Token* CompilerParser::mustBe(std::string expectedType, std::string expectedValue){
    return NULL;
}

/**
 * Definition of a ParseException
 * You can use this ParseException with `throw ParseException();`
 */
const char* ParseException::what() {
    return "An Exception occurred while parsing!";
}

ParseTree* CompilerParser::parseToken() {
    Token* token = tokenList.front();
    tokenList.pop_front();
    std::string type = token->getType();
    std::string value = token->getValue();
    return new ParseTree(type, value);
}