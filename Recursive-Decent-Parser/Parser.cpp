#include "Parser.h"

Parser::Parser()
{
    _lparenthesis = new std::regex("^\\(");
    _rparenthesis = new std::regex("^\\)");
    _op = new std::regex("^[-+*\/]");
    _num = new std::regex("^[+-]?(0|[1-9]\\d*)(\\.\\d+)?");
    _sign = new std::regex("^[+-]");
}

void Parser::parse(const std::string string_stream)
{
    _EXPR(string_stream);
}

/**
* Shows that the input stream is invalid. Called when there's an
* parsing error occurred.
*/
void Parser::_error_input_stream()
{
    std::cout << "invalid input";
    exit(0);
}

/**
 * Shows all parsed tokens to user.
 */
void Parser::show_results()
{
    for (int i = 0; i < _results.size(); i++)
    {
        std::cout << _results[i] << std::endl;
    }
}

/**
 * Parses and derives the non-terminal EXPR rule. This function will consume
 * all matched tokens and return a pending string for further operation.
 * @param const string string_stream The input stream to be parsed.
 * @returns string Returns the pending string to be parsed.
 */
std::string Parser::_EXPR(const std::string string_stream)
{
    std::string pending_string;

    pending_string = _SIG(string_stream);
    pending_string = _VAL(pending_string);
    pending_string = _TERM(pending_string);

    return pending_string;
}

/**
 * Parses and derives the non-terminal TERM rule. This function will consume
 * all matched tokens and return a pending string for further operation.
 * @param const string string_stream The input stream to be parsed.
 * @returns string Returns the pending string to be parsed.
 */
std::string Parser::_TERM(const std::string string_stream)
{
    std::string pending_string_stream = string_stream;
    std::string peek = pending_string_stream.substr(0, 1);
    std::smatch match;

    if (std::regex_search(peek, match, *_op))
    {
        _results.push_back("op " + match.str());

        pending_string_stream = std::regex_replace(pending_string_stream, *_op, "");
        pending_string_stream = _SIG(pending_string_stream);
        pending_string_stream = _VAL(pending_string_stream);
        pending_string_stream = _TERM(pending_string_stream);

        return pending_string_stream;
    }

    if (string_stream.empty() ||
        std::regex_search(string_stream, *_rparenthesis))
    {
        return string_stream; // do nothing.
    }

    _error_input_stream();
    return "";
}

/**
 * Parses and derives the non-terminal VAL rule. This function will consume
 * all matched tokens and return a pending string for further operation.
 * @param const string string_stream The input stream to be parsed.
 * @returns string Returns the pending string to be parsed.
 */
std::string Parser::_VAL(const std::string string_stream)
{
    std::string pending_string_stream = string_stream;
    std::smatch match;

    if (std::regex_search(pending_string_stream, match, *_num))
    {
        _results.push_back("num " + match.str());
        return std::regex_replace(pending_string_stream, *_num, "");
    }

    if (std::regex_search(pending_string_stream, match, *_lparenthesis))
    {
        _results.push_back("lparenthesis " + match.str());
        pending_string_stream = std::regex_replace(pending_string_stream, *_lparenthesis, "");
        pending_string_stream = _EXPR(pending_string_stream);

        if (std::regex_search(pending_string_stream, match, *_rparenthesis))
        {
            _results.push_back("rparenthesis " + match.str());
            pending_string_stream = std::regex_replace(pending_string_stream, *_rparenthesis, "");
            return pending_string_stream;
        }

        _error_input_stream();
        return "";
    }

    _error_input_stream();
    return "";
}

/**
 * Parses and derives the non-terminal SIG rule. This function will consume
 * all matched tokens and return a pending string for further operation.
 * @param const string string_stream The input stream to be parsed.
 * @returns string Returns the pending string to be parsed.
 */
std::string Parser::_SIG(const std::string string_stream)
{
    std::string pending_string_stream = string_stream;
    std::string peek = pending_string_stream.substr(0, 1);
    std::smatch match;

    if (std::regex_search(pending_string_stream, match, *_sign))
    {
        _results.push_back("sign " + match.str());
        return std::regex_replace(pending_string_stream, *_sign, "");
    }

    if (std::regex_search(pending_string_stream, *_lparenthesis) ||
        std::regex_search(pending_string_stream, *_num))
    {
        return pending_string_stream; // do nothing.
    }

    _error_input_stream();
    return "";
}