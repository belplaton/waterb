#pragma once
#ifndef _LINEAR_ALGEBRA_
#define _LINEAR_ALGEBRA_

#include "linear_vector.hpp"
#include "matrix.hpp"
#include <stdexcept>
#include "../big_float/big_float.hpp"

static class linear_algebra
{

public:

    friend class linear_vector;
    friend class matrix;

#pragma region Arithmetic

    static linear_vector cross(const std::vector<linear_vector>& values)
    {
        auto resized_matrix = matrix(values);
        if (resized_matrix.row_size() < resized_matrix.col_size())
        {
            resized_matrix.resize(resized_matrix.row_size(), resized_matrix.row_size() + 1);
        }
        else
        {
            resized_matrix.resize(resized_matrix.col_size(), resized_matrix.col_size() + 1);
        }

        return cross(resized_matrix);
    }

    static linear_vector cross(const matrix& value)
    {
        auto resized_matrix = matrix(value);
        if (resized_matrix.row_size() < resized_matrix.col_size())
        {
            resized_matrix.resize(resized_matrix.row_size(), resized_matrix.row_size() + 1);
        }
        else
        {
            resized_matrix.resize(resized_matrix.col_size(), resized_matrix.col_size() + 1);
        }

        auto n = resized_matrix.row_size() + 1;
        auto result = linear_vector(n);

        // Create matrix for the determinant calculation
        for (int i = 0; i < n; i++)
        {
            auto temp = matrix(n - 1);
            for (int j = 0; j < n - 1; j++)
            {
                int col = 0;
                for (int k = 0; k < n; k++)
                {
                    if (k == i) continue;

                    temp[j][col++] = resized_matrix[j][k];
                }
            }

            auto sign = (i % 2 == 0) ? 1 : -1;
            result[i] = sign * temp.determinant();
        }

        return result;
    }

    static big_float mixed_product(const linear_vector& scalar, const std::vector<linear_vector>& values)
    {
        auto resized_vector = linear_vector(scalar);
        auto resized_matrix = matrix(values);
        if (resized_vector.size() < resized_matrix.col_size())
        {
            resized_vector.resize(resized_matrix.col_size());
        }
        else if (resized_vector.size() > resized_matrix.col_size())
        {
            resized_matrix.col_resize(resized_vector.size());
        }

        return mixed_product(scalar, resized_matrix);
    }

    static big_float mixed_product(const linear_vector& scalar, const matrix& value)
    {
        auto resized_vector = linear_vector(scalar);
        auto resized_matrix = matrix(value);
        if (resized_vector.size() < resized_matrix.col_size())
        {
            resized_vector.resize(resized_matrix.col_size());
        }
        else if (resized_vector.size() > resized_matrix.col_size())
        {
            resized_matrix.col_resize(resized_vector.size());
        }

        auto temp = cross(resized_matrix);
        auto result = linear_vector(resized_vector);
        for (auto i = 0; i < result.size(); i++)
        {
            result[i] *= temp[i];
        }

        return result.sum();
    }

    static matrix gram_schmidt(const matrix& value)
    {
        auto result = std::vector<linear_vector>(value.row_size());
        for (auto i = 0; i < value.row_size(); i++)
        {
            auto ortogonal = value[i];
            for (auto j = 0; j < i; j++)
            {
                auto temp = ortogonal.projection(result[j]);
                ortogonal -= temp;
            }

            result[i] = ortogonal.normalize();
        }

        return matrix(result);
    }

#pragma endregion

};

#endif // ! _LINEAR_ALGEBRA_
