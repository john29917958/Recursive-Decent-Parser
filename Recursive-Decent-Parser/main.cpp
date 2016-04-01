/*-------------------------------------------------------
Author:     John Wang
E-mail:     john29917958@gmail.com
Purpose:    An example solution of the group competition 1
            problem A examination question of NCU compiler
            course.
University: National Central University
Lab:        Object-Oriented Lab
Course:     Compiler
Teacher:    Yung-Pin, Cheng assistant professor
Date:       2016-03-30
Grammar:
- Non-terminals
    EXPR -> SIG VAL TERM $
    TERM -> op SIG VAL TERM
          | £f
    VAL -> num
          | lparenthesis EXPR rparenthesis
    SIG -> sign
          | £f
- Terminals
    lparenthesis  (
    rparenthesis  )
    op            [-+*\/]
    num           (0|[1-9]\d*)(\.\d+)?
    sign          [+-]
-------------------------------------------------------*/
#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include "Parser.h"

using namespace std;

// Entry of program.
int main()
{
    // Holds each line of inputs entered by user.
    vector<string> input_lines;

    // Holds current line of inputs for input iteration.
    string current_line = "";

    Parser parser;

    // Try to retrieve everything that user inputs.
    while (getline(cin, current_line))
    {
        if (current_line.empty())
        {
            break; // The input stream is ended.
        }

        // Filters out unnecessary spaces.
        current_line.erase(remove(current_line.begin(), current_line.end(), ' '), current_line.end());
        input_lines.push_back(current_line);
    }

    // Parses each line of inputs.
    for (int i = 0; i < input_lines.size(); i++)
    {
        current_line = input_lines[i];
        parser.parse(current_line);
    }

    parser.show_results();

    return 0;
}