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
        auto temp = matrix(values);
        return cross(temp);
    }

    static linear_vector cross(const matrix& value)
    {
        if (value.row_size() + 1 != value.col_size())
        {
            throw std::invalid_argument("Count of vectors should be less by one then they max length");
        }

        auto n = value.row_size() + 1;
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

                    temp[j][col++] = value[j][k];
                }
            }

            auto sign = (i % 2 == 0) ? 1 : -1;
            result[i] = sign * temp.determinant();
        }

        return result;
    }

#pragma endregion

};

#endif // ! _LINEAR_ALGEBRA_
