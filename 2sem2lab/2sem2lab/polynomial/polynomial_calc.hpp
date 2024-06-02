#pragma once
#ifndef _POLYNOMIAL_CALC_PARSER_
#define _POLYNOMIAL_CALC_PARSER_

#include "polynomial.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <memory>
#include <algorithm>
#include <regex>

static std::regex unary_op_pattern(R"(diff|integr|\+|\-)");
static std::regex binary_op_pattern(R"(\+|\-|\*|\/|==|!=)");

class polynomial_calc_parser
{

private:
	
	std::ifstream _opened_file;
	std::string _file_path;

public:

#pragma region Constructors

	polynomial_calc_parser(std::string file_path)
	{
		_opened_file = std::ifstream(file_path);
		if (!_opened_file.is_open()) {
			std::cerr << "Could not open the file: " << std::endl;
			throw std::invalid_argument("Invalid file path or file is open already");
		}

		_file_path = file_path;
	}

	~polynomial_calc_parser()
	{
		_opened_file.close();
	}

#pragma endregion

	std::string parse_line()
	{
		std::string line;
		if (!std::getline(_opened_file, line))
		{
			return "";
		}

		auto elements_pattern = std::regex("\\s+");
		std::sregex_token_iterator iter(line.begin(), line.end(), elements_pattern, -1);
		std::sregex_token_iterator end;

		auto count = 0;
		while (iter != end)
		{
			count++;
			iter++;
		}

		std::string result;
		if (count == 2)
		{
			result = parse_unary(line);
		}
		else if (count == 3)
		{
			result = parse_binary(line);
		}

		return result;
	}

	void reset()
	{
		_opened_file.close();
		_opened_file = std::ifstream(_file_path);
		if (!_opened_file.is_open()) {
			std::cerr << "Could not open the file: " << std::endl;
			throw std::invalid_argument("Invalid file path or file is open already");
		}
	}

	bool check_next()
	{
		return !_opened_file.eof();
	}

private:


#pragma region Parse

	std::string parse_unary(std::string line)
	{
		auto elements_pattern = std::regex("\\s+");
		std::sregex_token_iterator iter(line.begin(), line.end(), elements_pattern, -1);
		std::sregex_token_iterator end;

		polynomial* first;
		std::string* op;

		first = string_to_polynomial((*iter++).str());
		op = string_to_unary((*iter++).str());

		if (first == nullptr || op == nullptr)
		{
			return "Failed";
		}

		std::string result;
		if (*op == "diff")
		{
			result = polynomial::diff(*first).to_string(10);
		}
		else if (*op == "integr")
		{
			result = polynomial::integr(*first).to_string(10);
		}
		else if (*op == "+")
		{
			result = (+*first).to_string(10);
		}
		else if (*op == "-")
		{
			result = (-*first).to_string(10);
		}

		return result;
	}

	std::string parse_binary(std::string line)
	{
		auto elements_pattern = std::regex("\\s+");
		std::sregex_token_iterator iter(line.begin(), line.end(), elements_pattern, -1);
		std::sregex_token_iterator end;

		polynomial* first;
		polynomial* second;
		std::string* op;

		first = string_to_polynomial((*iter++).str());
		op = string_to_unary((*iter++).str());
		second = string_to_polynomial((*iter++).str());

		if (first == nullptr || second == nullptr || op == nullptr)
		{
			return "Failed";
		}

		std::string result;
		if (*op == "+")
		{
			result = (*first + *second).to_string(10);
		}
		else if (*op == "-")
		{
			result = (*first - *second).to_string(10);
		}
		else if (*op == "*")
		{
			result = (*first * *second).to_string(10);
		}
		else if (*op == "/")
		{
			result = (*first / *second).to_string(10);
		}
		else if (*op == "==")
		{
			result = (*first == *second) ? "true" : "false";
		}
		else if (*op == "!=")
		{
			result = (*first != *second) ? "false" : "true";
		}

		return result;
	}

	static polynomial* string_to_polynomial(const std::string& value)
	{
		if (polynomial::is_polynomial(value))
		{
			return new polynomial(value);
		}

		return nullptr;
	}

	static std::string* string_to_unary(const std::string& value)
	{
		if (std::regex_match(value, unary_op_pattern))
		{
			return new std::string(value);
		}

		return nullptr;
	}

	static std::string* string_to_binary(const std::string& value)
	{
		std::string* result = nullptr;
		if (std::regex_match(value, binary_op_pattern))
		{
			auto temp = std::string(value);
			result = &temp;
		}

		return result;
	}

#pragma endregion

};

#endif // ! _POLYNOMIAL_
