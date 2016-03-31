#pragma once

#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <regex>
#include <string>
#include <vector>

class Parser {
public:
    Parser();
    void parse(const std::string);
    void show_results();
private:
    void _error_input_stream();

    std::string _EXPR(const std::string);
    std::string _TERM(const std::string);
    std::string _VAL(const std::string);
    std::string _SIG(const std::string);

    std::regex *_lparenthesis;
    std::regex *_rparenthesis;
    std::regex *_op;
    std::regex *_num;
    std::regex *_sign;

    std::vector<std::string> _results;
};

#endif // !PARSER_H