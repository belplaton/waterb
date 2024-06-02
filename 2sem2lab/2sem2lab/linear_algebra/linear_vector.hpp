#pragma once
#ifndef _LINEAR_VECTOR_
#define _LINEAR_VECTOR_

#include <vector>
#include <regex>
#include <stdexcept>
#include "../big_float/big_float.hpp"
#include "linear_algebra.hpp"

static std::regex linear_vector_pattern(R"([^,\]\[\s]+)");

class linear_vector
{

private:

    std::vector<big_float> _elements;

public:

#pragma region Constructors

    linear_vector()
    {
        _elements = std::vector<big_float>();
    }

    linear_vector(unsigned int size)
    {
        _elements = std::vector<big_float>(size);
    }

    linear_vector(const std::vector<big_float>& elements)
    {
        _elements = std::vector<big_float>(elements);
    }

    linear_vector(const std::vector<big_float>& elements, unsigned int virtual_size)
    {
        _elements = std::vector<big_float>(virtual_size);
        for (auto i = 0; i < virtual_size && i < elements.size(); i++)
        {
            _elements[i] = elements[i];
        }
    }

    linear_vector(const big_float* elements, unsigned int real_size)
    {
        _elements = std::vector<big_float>(real_size);
        for (auto i = 0; i < real_size; i++)
        {
            _elements[i] = elements[i];
        }
    }

    linear_vector(const big_float* elements, unsigned int real_size, unsigned int virtual_size)
    {
        _elements = std::vector<big_float>(real_size);
        for (auto i = 0; i < virtual_size && i < real_size; i++)
        {
            _elements[i] = elements[i];
        }
    }

    linear_vector(const std::string& other)
    {
        auto result = std::vector<big_float>();
        if (!std::regex_search(other, linear_vector_pattern))
        {
            throw std::invalid_argument("Invalid linear vector format! Use [<sign><numerator/denominator>, ...] with decimal format.");
        }

        std::sregex_token_iterator iter(other.begin(), other.end(), linear_vector_pattern);
        std::sregex_token_iterator end;
        while (iter != end)
        {
            if (!big_float::is_big_float((*iter).str()))
            {
                throw std::invalid_argument("Invalid linear vector format! Use [<sign><numerator/denominator>, ...] with decimal format.");
            }

            auto temp = big_float((*iter).str());
            result.push_back(temp);

            iter++;
        }

        _elements = result;
    }

    linear_vector(const linear_vector& other)
    {
        _elements = std::vector<big_float>(other._elements);
    }

    linear_vector(const linear_vector& other, unsigned int size)
    {
        _elements = std::vector<big_float>(other._elements);
        resize(size);
    }

    ~linear_vector()
    {

    }

#pragma endregion

#pragma region Indexators

    big_float& operator[](size_t index)
    {
        return _elements[index];
    }

    const big_float& operator[](size_t index) const
    {
        return _elements[index];
    }

#pragma endregion

#pragma region Arithmetic Operators

    linear_vector& operator += (const linear_vector& other)
    {
        if (_elements.size() != other._elements.size())
        {
            throw std::invalid_argument("Error! Vectors must be equal dimensions.");
        }

        std::vector<big_float> result(_elements.size());
        for (size_t i = 0; i < _elements.size(); ++i)
        {
            result[i] = _elements[i] + other._elements[i];
        }

        _elements = result;
    }

    linear_vector& operator -= (const linear_vector& other)
    {
        if (_elements.size() != other._elements.size())
        {
            throw std::invalid_argument("Error! Vectors must be equal dimensions.");
        }

        std::vector<big_float> result(_elements.size());
        for (size_t i = 0; i < _elements.size(); ++i)
        {
            result[i] = _elements[i] - other._elements[i];
        }

        _elements = result;
    }

    linear_vector& operator *= (const big_float& scalar)
    {
        std::vector<big_float> result(_elements.size());
        for (size_t i = 0; i < _elements.size(); ++i)
        {
            result[i] = _elements[i] * scalar;
        }

        _elements = result;
    }

    linear_vector operator + (const linear_vector& other)
    {
        auto temp(*this);
        temp += other;
        return temp;
    }

    linear_vector operator - (const linear_vector& other)
    {
        auto temp(*this);
        temp -= other;
        return temp;
    }

    linear_vector operator * (const big_float& scalar)
    {
        auto temp(*this);
        temp *= scalar;
        return temp;
    }

#pragma endregion

#pragma region IO Operators

    friend std::ostream& operator << (std::ostream& stream, const linear_vector& other)
    {
        stream << other.to_string(10);

        return stream;
    }

    friend std::istream& operator >> (std::istream& stream, linear_vector& other)
    {
        auto input = std::string();
        stream >> input;

        if (!std::regex_match(input, linear_vector_pattern))
        {
            stream.setstate(std::ios::failbit);
            return stream;
        }

        std::sregex_token_iterator iter(input.begin(), input.end(), linear_vector_pattern, -1);
        std::sregex_token_iterator end;
        while (iter != end)
        {
            if (!big_float::is_big_float((*iter).str()))
            {
                stream.setstate(std::ios::failbit);
                return stream;
            }

            iter++;
        }

        other = linear_vector(input);

        return stream;
    }

#pragma endregion

#pragma region Utility

    size_t size() const
    {
        return _elements.size();
    }

    void resize(unsigned int size)
    {
        _elements.resize(size);
    }

    std::string to_string(unsigned int base) const
    {
        std::string result;
        result += "[";

        for (auto i = 0; i < _elements.size(); i++)
        {
            if (i > 0) result += ",";

            result += _elements[i].to_string(10);
        }

        result += "]";

        return result;
    }

#pragma endregion

};

#endif // ! _LINEAR_VECTOR_
