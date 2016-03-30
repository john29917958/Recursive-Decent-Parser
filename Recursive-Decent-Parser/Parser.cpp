/*-------------------------------------------------------
Author:     John Wang
E-mail:     john29917958@gmail.com
Purpose:    An example solution of the group competition 1
            problem A examination question.
University: National Central University
Lab:        Object-Oriented Lab
Advisor:    Yung-Pin, Cheng assistant professor
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

using namespace std;

void error_input_stream();
void show_results();

string EXPR(const string);
string TERM(const string);
string VAL(const string);
string SIG(const string);

regex lparenthesis("^\\(");
regex rparenthesis("^\\)");
regex op("^[-+*\/]");
regex num("^[+-]?(0|[1-9]\\d*)(\\.\\d+)?");
regex sign("^[+-]");

// Stores all parsed token types and the value of tokens.
vector<string> results;

// Entry of program.
int main()
{
    // Holds each line of inputs entered by user.
    vector<string> input_lines;

    // Holds current line of inputs for input iteration.
    string current_line = "";

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

        EXPR(current_line);
    }

    if (!results.empty())
    {
        show_results();
    }
    else
    {
        cout << "invalid input";
    }
    
    return 0;
}

/**
 * Displays all parsed tokens.
 */
void show_results()
{
    for (int i = 0; i < results.size(); i++)
    {
        cout << results[i] << endl;
    }
}

/**
 * Shows that the input stream is invalid. Called when there's an
 * parsing error occurred.
 */
void error_input_stream()
{
    cout << "invalid input";
    exit(0);
}

/**
 * Parses and derives the non-terminal EXPR rule. This function will consume
 * all matched tokens and return a pending string for further operation.
 * @param const string string_stream The input stream to be parsed.
 * @returns string Returns the pending string to be parsed.
 */
string EXPR(const string string_stream)
{
    string pending_string;

    pending_string = SIG(string_stream);
    pending_string = VAL(pending_string);
    pending_string = TERM(pending_string);

    return pending_string;
}

/**
* Parses and derives the non-terminal TERM rule. This function will consume
* all matched tokens and return a pending string for further operation.
* @param const string string_stream The input stream to be parsed.
* @returns string Returns the pending string to be parsed.
*/
string TERM(const string string_stream)
{
    string pending_string_stream = string_stream;
    string peek = pending_string_stream.substr(0, 1);
    smatch match;

    if (regex_search(peek, match, op))
    {
        results.push_back("op " + match.str());

        pending_string_stream = regex_replace(pending_string_stream, op, "");
        pending_string_stream = SIG(pending_string_stream);
        pending_string_stream = VAL(pending_string_stream);
        pending_string_stream = TERM(pending_string_stream);

        return pending_string_stream;
    }

    if (string_stream.empty() ||
        regex_search(string_stream, rparenthesis))
    {
        return string_stream; // do nothing.
    }

    error_input_stream();
    return "";
}

/**
* Parses and derives the non-terminal VAL rule. This function will consume
* all matched tokens and return a pending string for further operation.
* @param const string string_stream The input stream to be parsed.
* @returns string Returns the pending string to be parsed.
*/
string VAL(const string string_stream)
{
    string pending_string_stream = string_stream;
    smatch match;

    if (regex_search(pending_string_stream, match, num))
    {
        results.push_back("num " + match.str());
        return regex_replace(pending_string_stream, num, "");
    }

    if (regex_search(pending_string_stream, match, lparenthesis))
    {
        results.push_back("lparenthesis " + match.str());
        pending_string_stream = regex_replace(pending_string_stream, lparenthesis, "");
        pending_string_stream = EXPR(pending_string_stream);
        
        if (regex_search(pending_string_stream, match, rparenthesis))
        {
            results.push_back("rparenthesis " + match.str());
            pending_string_stream = regex_replace(pending_string_stream, rparenthesis, "");
            return pending_string_stream;
        }

        error_input_stream();
        return "";
    }

    error_input_stream();
    return "";
}

/**
* Parses and derives the non-terminal SIG rule. This function will consume
* all matched tokens and return a pending string for further operation.
* @param const string string_stream The input stream to be parsed.
* @returns string Returns the pending string to be parsed.
*/
string SIG(const string string_stream)
{
    string pending_string_stream = string_stream;
    string peek = pending_string_stream.substr(0, 1);
    smatch match;

    if (regex_search(pending_string_stream, match, sign))
    {
        results.push_back("sign " + match.str());
        return regex_replace(pending_string_stream, sign, "");
    }

    if (regex_search(pending_string_stream, lparenthesis) ||
        regex_search(pending_string_stream, num))
    {
        return pending_string_stream; // do nothing.
    }

    error_input_stream();
    return "";
}