#include <iostream>
#include <string>
#include <vector>
#include <regex>

using namespace std;

string EXPR(const string);
string TERM(const string);
string VAL(const string);
string SIG(const string);

regex lparenthesis("\\(");
regex rparenthesis("\\)");
regex op("[-+*\/]");
regex num("[+-]?(0|[1-9][0-9]*)(\.[0-9]+)?");
regex sign("[+-]");

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

        EXPR(current_line);

        cout << "Passed" << endl;
    }

    return 0;
}

void error_input_stream()
{
    cout << "invalid input";
    system("pause");
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
    
    if (regex_match(peek, op))
    {
        pending_string_stream = regex_replace(pending_string_stream, op, "");
        pending_string_stream = VAL(pending_string_stream);
        pending_string_stream = TERM(pending_string_stream);

        return pending_string_stream;
    }

    if (string_stream.empty())
    {
        // do nothing.
        return string_stream;
    }

    error_input_stream();
    return "";
}

string VAL(const string string_stream)
{
    string pending_string_stream = string_stream;

    if (regex_match(pending_string_stream, num))
    {
        return regex_replace(pending_string_stream, num, "");
    }

    if (regex_match(pending_string_stream, lparenthesis))
    {
        pending_string_stream = regex_replace(pending_string_stream, lparenthesis, "");
        pending_string_stream = EXPR(pending_string_stream);
        
        if (regex_match(pending_string_stream, rparenthesis))
        {
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

    if (regex_match(pending_string_stream, sign))
    {
        return regex_replace(pending_string_stream, sign, "");
    }

    if (regex_match(pending_string_stream, lparenthesis) ||
        regex_match(pending_string_stream, num))
    {
        // do nothing.
        return pending_string_stream;
    }

    error_input_stream();
    return "";
}