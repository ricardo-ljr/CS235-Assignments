#include "ExpressionManager.h"
#include <sstream>

using namespace std;

bool ExpressionManager::isBalanced(string expression) {
    stack<string> s;

    istringstream ss;
    ss.str(expression);
    string x;

    while (!ss.eof()) {
        ss >> x;

        if (x == "(") {
            s.push("(");
        } else if (x == "[") {
            s.push("[");
        } else if (x == "{") {
            s.push("{");
        }

        if (!s.empty())            // check if the stack is empty
        {
            if (x == ")" && s.top() == "(") {
                s.pop();
                x = "";
            } else if (x == "]" && s.top() == "[") {
                s.pop();
                x = "";
            } else if (x == "}" && s.top() == "{") {
                s.pop();
                x = "";
            }
        }

        if (s.empty()) {
            if (x == "}" || x == "]" ||
                x == ")")    // check if there is more closing parenthesis than opening parenthesis
            {
                return false;
            }
        }
    }
    if (s.empty()) {
        return true;
    } else {
        return false;
    }

}

string ExpressionManager::postfixToInfix(string postfixExpression) {
    stack<string> s;

    istringstream ss;
    ss.str(postfixExpression);
    string x;
    string result = "";


    while (!ss.eof()) {
        ss >> x;
        string after = "";
        string before = "";

        if (x.find('.') != string::npos) {
            return "invalid";
        }

        if (isdigit(x[0])) {
            s.push(x);
        } else if (x == "+") {

            if (s.empty()) {
                return "invalid";
            } else {
                after = s.top();
                s.pop();
                if (!s.empty()) {
                    before = s.top();
                    s.pop();
                    result = "( " + before + " + " + after + " )";
                    s.push(result);
                } else {
                    return "invalid";
                }
            }
        } else if (x == "-") {
            if (s.empty()) {
                return "invalid";
            } else {
                after = s.top();
                s.pop();
                if (!s.empty()) {
                    before = s.top();
                    s.pop();
                    result = "( " + before + " - " + after + " )";
                    s.push(result);
                } else {
                    return "invalid";
                }
            }
        } else if (x == "*") {
            if (s.empty()) {
                return "invalid";
            } else {
                after = s.top();
                s.pop();
                if (!s.empty()) {
                    before = s.top();
                    s.pop();
                    result = "( " + before + " * " + after + " )";
                    s.push(result);
                } else {
                    return "invalid";
                }
            }
        } else if (x == "/") {
            if (s.empty()) {
                return "invalid";
            } else {
                after = s.top();
                s.pop();
                if (!s.empty()) {
                    before = s.top();
                    s.pop();
                    if (after == "0") {
                        return "invalid";
                    } else {
                        result = "( " + before + " / " + after + " )";
                        s.push(result);
                    }
                } else {
                    return "invalid";
                }
            }
        } else if (x == "%") {

            if (s.empty()) {
                return "invalid";
            } else {
                after = s.top();
                s.pop();
                if (!s.empty()) {
                    before = s.top();
                    s.pop();
                    if (after == "0") {
                        return "invalid";
                    } else {
                        result = "( " + before + " % " + after + " )";
                        s.push(result);
                    }
                } else {
                    return "invalid";
                }
            }
        } else {
            return "invalid";
        }
    }

    if (s.size() == 1) {
        return s.top();
    } else {
        return "invalid";
    }
}

string ExpressionManager::infix() {
    return getExpression();
}

string ExpressionManager::postfix() {
    return infixToPostfix(getExpression());
}

string ExpressionManager::infixToPostfix(string infixExpression) {
    stack<string> s;

    istringstream ss;
    ss.str(infixExpression);
    string x;
    string result = "";

    if (isBalanced(infixExpression)) {
        bool lastWasOperator = false;
        while (!ss.eof()) {
            ss >> x;
            if (x.find('.') != string::npos) {
                return "invalid";
            }
            if (isdigit(x[0])) {
                lastWasOperator = false;
                if (result == "") {
                    result = x;
                } else {
                    result = result + " " + x;
                }
            } else if (lastWasOperator == false || x == "(") {
                if (x == "+") {
                    lastWasOperator = true;
                    if (!s.empty()) {
                        if (s.top() == "*" || s.top() == "/" || s.top() == "%" || s.top() == "-" || s.top() == "+") {
                            result = result + " " + s.top();
                            s.pop();
                            s.push(x);
                        } else {
                            s.push(x);
                        }
                    } else {
                        s.push(x);
                    }
                } else if (x == "-") {
                    lastWasOperator = true;
                    if (!s.empty()) {
                        if (s.top() == "*" || s.top() == "/" || s.top() == "%" || s.top() == "-" || s.top() == "+") {
                            result = result + " " + s.top();
                            s.pop();
                            s.push(x);
                        } else {
                            s.push(x);
                        }
                    } else {
                        s.push(x);
                    }
                } else if (x == "*") {
                    lastWasOperator = true;
                    if (!s.empty()) {
                        if (s.top() == "*" || s.top() == "/" || s.top() == "%") {
                            result = result + " " + s.top();
                            s.pop();
                            s.push(x);
                        } else {
                            s.push(x);
                        }
                    } else {
                        s.push(x);
                    }
                } else if (x == "/") {
                    lastWasOperator = true;
                    if (!s.empty()) {
                        if (s.top() == "*" || s.top() == "/" || s.top() == "%") {
                            result = result + " " + s.top();
                            s.pop();
                            s.push(x);
                        } else {
                            s.push(x);
                        }
                    } else {
                        s.push(x);
                    }
                } else if (x == "%") {
                    lastWasOperator = true;
                    if (!s.empty()) {
                        if (s.top() == "*" || s.top() == "/" || s.top() == "%") {
                            result = result + " " + s.top();
                            s.pop();
                            s.push(x);
                        } else {
                            s.push(x);
                        }
                    } else {
                        s.push(x);
                    }
                } else if (x == "(") {
                    lastWasOperator = false;
                    s.push(x);
                } else if (x == ")") {
                    lastWasOperator = false;
                    if (!s.empty()) {
                        while (s.top() != "(") {
                            result = result + " " + s.top();
                            s.pop();
                        }
                        s.pop();
                    }
                } else {
                    return "invalid";
                }
            } else {
                return "invalid";
            }
        }
    } else {
        return "invalid";
    }
    while (!s.empty()) {
        if (result == "") {
            return "invalid";
        }
        result = result + " " + s.top();
        s.pop();
    }
    return result;
}

string ExpressionManager::postfixEvaluate(string postfixExpression) {
    stack<int> s;

    istringstream ss;
    ss.str(postfixExpression);
    string x;
    int result = 0;

    if (isBalanced(postfixExpression)) {
        while (!ss.eof()) {
            ss >> x;
            int number1 = 0;
            int number2 = 0;
            if (isdigit(x[0])) {
                int convert_to_int = atoi(x.c_str());
                s.push(convert_to_int);
                result = convert_to_int;
            } else if (!s.empty()) {
                if (x == "+") {
                    number2 = s.top();

                    s.pop();
                    if (s.empty()) {
                        return "invalid";
                    } else {
                        number1 = s.top();
                        s.pop();
                        result = number1 + number2;
                        s.push(result);
                    }
                } else if (x == "-") {
                    number2 = s.top();
                    s.pop();
                    if (s.empty()) {
                        return "invalid";
                    } else {
                        number1 = s.top();
                        s.pop();
                        result = number1 - number2;
                        s.push(result);
                    }
                } else if (x == "*") {
                    number2 = s.top();
                    s.pop();
                    if (s.empty()) {
                        return "invalid";
                    } else {
                        number1 = s.top();
                        s.pop();
                        result = number1 * number2;
                        s.push(result);
                    }
                } else if (x == "/") {
                    number2 = s.top();
                    s.pop();
                    if (s.empty()) {
                        return "invalid";
                    } else {
                        number1 = s.top();
                        s.pop();
                        if (number2 == 0) {
                            return "invalid";
                        } else {
                            result = number1 / number2;
                            s.push(result);
                        }
                    }
                } else if (x == "%") {
                    number2 = s.top();
                    s.pop();
                    if (s.empty()) {
                        return "invalid";
                    } else {
                        number1 = s.top();
                        s.pop();
                        if (number2 == 0) {
                            return "invalid";
                        } else {
                            result = number1 % number2;
                            s.push(result);
                        }
                    }
                }
            } else {
                return "invalid";
            }
        }

        if (s.size() == 1) {
            ostringstream strm;
            strm << result;
            return strm.str();
        } else {
            return "invalid";
        }
    } else {
        return "invalid";
    }
}

// std::string ExpressionManager::prefix(void) {
//    int l = getExpression().size();
//
//    // Reverse infix
//    reverse(getExpression().begin(), getExpression().end());
//
//    // Replace ( with ) and vice versa
//    for (int i = 0; i < l; i++) {
//
//        if (getExpression()[i] == '(') {
//            getExpression()[i] = ')';
//            i++;
//        }
//        else if (getExpression()[i] == ')') {
//            getExpression()[i] = '(';
//            i++;
//        }
//    }
//
//    string prefix = infixToPostfix(getExpression());
//
//    // Reverse postfix
//    reverse(prefix.begin(), prefix.end());
//
//    return prefix;
//}