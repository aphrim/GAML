#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <chrono>

struct call {
    std::string line;
    int scopeDepth;
    struct call * next;
}; 

struct variable {
    int type;
    int intVal;
};

std::map<std::string, variable*> vars;

template<typename T>
bool isVariable(T const v) {
    if (vars.find(v) == vars.end()) {
        return false;
    }
    return true;
}

std::string trim(const std::string& str)
{
    size_t first = str.find_first_not_of(' ');
    if (std::string::npos == first)
    {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}
class Interpreter {

public:
    void proccessBody(call* startCall)
    {
        call* curCall = new call;
        int callScopeDepth = startCall->scopeDepth;
        int curScopeDepth = startCall->scopeDepth;
        curCall = startCall;
        while (curScopeDepth >= callScopeDepth) {
            if (curScopeDepth == callScopeDepth) {
                proccessCall(curCall->line, curCall);
            }
            curCall = curCall->next;
            curScopeDepth = curCall->scopeDepth;
        }
    }

    void proccessCall(std::string line, call* thisCall)
    {
        line = trim(line);
        std::string start = line.substr(0, line.find(" "));
        std::string funcStart = line.substr(0, line.find("("));
        if (funcStart.size() > 0 && funcStart.size() < start.size()) {
            start = funcStart;
        }
        start = trim(start);


        //Please forgive me for this code, this is a abomination upon the earth, I'm sorry, these if statements instead of switch cases, why, I don't know, I just wanted to get this done, why, why doesn't the original run through of the code just assign a function to each call instead of all these if statements that are extremely slow?
        if (start == "let" || start == "set") 
        {
            std::string varName = line.substr(line.find(" ") + 1, line.find("=") - line.find(" ") - 1);
            varName = trim(varName);
            std::string varValue = trim(line.substr(line.find("=") + 1, line.length() - line.find("=") - 1));
            if (isVariable(varName))
            {
                if (isVariable(varValue)) {
                    vars[varName]->intVal = vars[varValue]->intVal;
                } else {
                    vars[varName]->intVal = std::stoi(varValue);
                }
            }
            else
            {
                variable* newVar = new variable;
                if (isVariable(varValue)) {
                    newVar->intVal = vars[varValue]->intVal;
                } else {
                    newVar->intVal = std::stoi(varValue);
                }
                vars[varName] = newVar;
            }
        }
        else if (start == "print")
        {
            std::string varName = line.substr(line.find("(") + 1, line.find(")") - line.find("(") - 1);
            varName = trim(varName);
            if (isVariable(varName))
            {

                std::cout << vars[varName]->intVal << std::endl;
            }
            else
            {

                std::cout << varName << std::endl;
            }
        } 
        else if (start == "printch")
        {
            std::string varName = line.substr(line.find("(") + 1, line.find(")") - line.find("(") - 1);
            varName = trim(varName);
            if (isVariable(varName))
            {

                std::cout << (char) vars[varName]->intVal;
            }
            else
            {

                std::cout << (char) stoi(varName);
            }
        }
        else if (start == "loop") 
        {
            std::string varName = trim(line.substr(line.find("(") + 1, line.find(",") - line.find("(") - 1));
            std::string countString = trim(line.substr(line.find(",") + 1, line.find(")") - line.find(",") - 1));
            int count = 0;
            if (isVariable(countString))
            {
                count = vars[countString]->intVal;
            }
            else
            {
                try {
                    count = std::stoi(countString);
                } catch (std::invalid_argument) {
                    std::cout << "Invalid argument: " << countString << std::endl;
                }
            }
            for (int i = vars[varName]->intVal; i <= count; ++i)
            {   
                vars[varName]->intVal = i;
                proccessBody(thisCall->next);
            }
        }
        else if (start == "ifeq") 
        {
            std::string varName = line.substr(line.find("(") + 1, line.find(",") - line.find("(") - 1);
            std::string varName2 = line.substr(line.find(",") + 1, line.find(")") - line.find(",") - 1);
            varName = trim(varName);
            varName2 = trim(varName2);
            int val1;
            int val2;

            if (isVariable(varName))
            {
                val1 = vars[varName]->intVal;
            }
            else
            {
                try {
                    val1 = std::stoi(varName);
                } catch (std::invalid_argument) {
                    std::cout << "Invalid argument: " << varName << std::endl;
                }
            }
            if (isVariable(varName2))
            {
                val2 = vars[varName]->intVal;
            }
            else
            {
                try {
                    val2 = std::stoi(varName2);
                } catch (std::invalid_argument) {
                    std::cout << "Invalid argument: " << varName << std::endl;
                }
            }


            if (val1 == val2)
            {
                proccessBody(thisCall->next);
            }
        }
        else if (start == "ifneq")
        {
            std::string varName = line.substr(line.find("(") + 1, line.find(",") - line.find("(") - 1);
            std::string varName2 = line.substr(line.find(",") + 1, line.find(")") - line.find(",") - 1);
            varName = trim(varName);
            varName2 = trim(varName2);
            int val1;
            int val2;

            if (isVariable(varName))
            {
                val1 = vars[varName]->intVal;
            }
            else
            {
                try {
                    val1 = std::stoi(varName);
                } catch (std::invalid_argument) {
                    std::cout << "Invalid argument: " << varName << std::endl;
                }
            }
            if (isVariable(varName2))
            {
                val2 = vars[varName]->intVal;
            }
            else
            {
                try {
                    val2 = std::stoi(varName2);
                } catch (std::invalid_argument) {
                    std::cout << "Invalid argument: " << varName << std::endl;
                }
            }


            if (val1 != val2)
            {
                proccessBody(thisCall->next);
            }
        }
        else if (start == "div")
        {
            std::string varName = line.substr(line.find("(") + 1, line.find(",") - line.find("(") - 1);
            std::string varName2 = line.substr(line.find(",") + 1, line.find(")") - line.find(",") - 1);
            varName = trim(varName);
            varName2 = trim(varName2);
            int val2;

            if (isVariable(varName2))
            {
                val2 = vars[varName]->intVal;
            }
            else
            {
                try {
                    val2 = std::stoi(varName2);
                } catch (std::invalid_argument) {
                    std::cout << "Invalid argument: " << varName << std::endl;
                }
            }
            if (isVariable(varName))
            {
                vars[varName]->intVal /= val2;
            }
        }
        else if (start == "mod")
        {
            std::string varName = line.substr(line.find("(") + 1, line.find(",") - line.find("(") - 1);
            std::string varName2 = line.substr(line.find(",") + 1, line.find(")") - line.find(",") - 1);
            varName = trim(varName);
            varName2 = trim(varName2);
            int val2 = 0;

            if (isVariable(varName2))
            {
                val2 = vars[varName2]->intVal;
            }
            else
            {
                try {
                    val2 = std::stoi(varName2);
                } catch (std::invalid_argument) {
                    std::cout << "Invalid argument: " << varName << std::endl;
                }
            }
            if (isVariable(varName))
            {
                vars[varName]->intVal %= val2;
            }
        }
        else if (start == "//")
        {
            
        }
        else 
        {
            if (isVariable(start)) {
                std::string varValue = trim(line.substr(line.find("=") + 1, line.length() - line.find("=") - 1));
                if (varValue.size() > 0) {
                    if (isVariable(varValue)) {
                        vars[start]->intVal = vars[varValue]->intVal;
                    } else {
                        vars[start]->intVal = std::stoi(varValue);
                    }
                }
            }
        }

    }

    void proccessCalls(call* execStart)
    {
        call * curCall = execStart;
        while ( curCall -> next) {
            proccessCall(curCall->line, curCall);
            curCall = curCall->next;
            while (curCall->scopeDepth != 0 && curCall->next) {
                curCall = curCall->next;
            }
        }
    }

    void parse(std::string fileName)
    {   
        std::fstream file;

        file.open(fileName, std::ios::in);
        if (!file)
        {
            std::cout << "File not found" << std::endl;
            return;
        }
        else
        {
            char ch;

            std::string curCallString;
            struct call * curCall = new call;
            struct call * execStart = new call;
            int scopeDepth = 0;
            execStart -> next = curCall;
            execStart -> line = "";

            while ( true )
            {
                file.get(ch);
                if (file.eof())
                    break;
                if ( ch == ';') 
                {
                    curCall->line = curCallString;
                    curCall->scopeDepth = scopeDepth;
                    curCallString = "";
                    curCall->next = new call;
                    curCall = curCall->next;
                } 
                else if (ch == '{') 
                {
                    curCall->line = curCallString;
                    curCall->scopeDepth = scopeDepth;
                    curCallString = "";
                    curCall->next = new call;
                    curCall = curCall->next;
                    scopeDepth++;
                } 
                else if (ch == '}')
                {
                    curCall->line = curCallString;
                    curCall->scopeDepth = scopeDepth;
                    curCallString = "";
                    curCall->next = new call;
                    curCall = curCall->next;
                    scopeDepth--;
                }
                else
                {
                    if (ch != '\n')
                    {
                        curCallString += ch;
                    }
                }
            }

            curCall = execStart;
            proccessCalls(execStart);
        }
        file.close();
    }
};

long double curtime() {
  return std::chrono::duration_cast<std::chrono::milliseconds>(
    std::chrono::system_clock::now().time_since_epoch()
  ).count();
}

int main() {
    long double begin = curtime();
    Interpreter* interp = new Interpreter();
    interp->parse("helloworld.gmal");
    long double end = curtime();
    std::cout << "Executed in " << end - begin << " milliseconds" << std::endl;
}
