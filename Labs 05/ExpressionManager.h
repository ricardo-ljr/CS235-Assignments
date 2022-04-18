

#ifndef EXPRESSIONMANAGER_H
#define EXPRESSIONMANAGER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <locale>
#include <cctype>
#include <string>
#include <vector>
#include <stack>
#include <functional>
#include "ExpressionManagerInterface.h"

using namespace std;

class ExpressionManager : public ExpressionManagerInterface
{
private:
    string expression;
    string post;
public:

    ExpressionManager(){
        expression = "";
    }
    ~ExpressionManager(){}

    virtual bool isBalanced(string expression);
    virtual string postfixToInfix(string postfixExpression);
    virtual string infixToPostfix(string infixExpression);
    virtual string postfixEvaluate(string postfixExpression);

    virtual void setExpression(string exp) {
        expression = exp;
    }

    virtual string getExpression() {
        return expression;
    }

    virtual void setPostFix(string exp) {
        post = exp;
    }

    virtual string getPostFix() {
        return post;
    }

    virtual int value(void) {};

    virtual std::string infix(void);

    /** Return a postfix representation of the infix expression */
    virtual std::string postfix(void);

    /** (BONUS) Return a prefix representation of the infix expression */
    virtual std::string prefix(void) {}


    /** Return the infix vector'd expression items */
    virtual std::string toString(void) const {}

};

#endif //EXPRESSIONMANAGER_H
