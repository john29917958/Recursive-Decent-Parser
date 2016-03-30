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

vector<string> results;

int main()
{
    
    vector<string> input_lines;
    string current_line = "";

    while (getline(cin, current_line))
    {
        if (current_line.empty())
        {
            break;
        }

        results.clear();

        EXPR(current_line);

        if (!results.empty())
        {
            show_results();
        }
        else
        {
            cout << "invalid input";
            break;
        }
    }

    return 0;
}

void show_results()
{
    for (int i = 0; i < results.size(); i++)
    {
        cout << results[i] << endl;
    }
}

void error_input_stream()
{
    cout << "invalid input";
    exit(0);
}

string EXPR(const string string_stream)
{
    string pending_string;

    pending_string = SIG(string_stream);
    pending_string = VAL(pending_string);
    pending_string = TERM(pending_string);

    return pending_string;
}

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