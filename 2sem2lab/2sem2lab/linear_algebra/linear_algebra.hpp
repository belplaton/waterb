#pragma once
#ifndef _LINEAR_ALGEBRA_
#define _LINEAR_ALGEBRA_

#include "linear_vector.hpp"
#include "matrix.hpp"
#include <stdexcept>
#include <tuple>
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

    static matrix gram_schmidt(const matrix& value, const big_float& epsilon)
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

            result[i] = ortogonal.normalize(epsilon);
        }

        return matrix(result);
    }

    static linear_vector gauss(const matrix& first, const linear_vector& second)
    {
        auto n = first.row_size();
        auto temp_first(first);
        auto temp_second(second);
        for (auto i = 0; i < n; i++)
        {
            auto pivot = big_float(temp_first[i][i]);
            for (auto j = i; j < n; ++j)
            {
                temp_first[i][j] /= pivot;
            }

            temp_second[i] /= pivot;
            for (auto j = i + 1; j < n; j++)
            {
                auto factor = big_float(temp_first[j][i]);
                for (auto k = i; k < n; k++)
                {
                    temp_first[j][k] -= factor * temp_first[i][k];
                }

                temp_second[j] -= temp_second[i] * factor;
            }
        }

        linear_vector result(n);
        for (int i = n - 1; i >= 0; i--)
        {
            result[i] = temp_second[i];
            for (int j = i + 1; j < n; j++)
            {
                result[i] -= temp_first[i][j] * result[j];
            }
        }

        return result;
    }

    static linear_vector jordan_gauss(const matrix& first, const linear_vector& second)
    {
        auto n = first.row_size();
        auto temp_first(first);
        auto temp_second(second);
        for (auto i = 0; i < n; i++)
        {
            auto pivot = big_float(temp_first[i][i]);
            for (auto j = 0; j < n; ++j)
            {
                temp_first[i][j] /= pivot;
            }

            temp_second[i] /= pivot;
            for (auto j = 0; j < n; j++)
            {
                if (j == i) continue;

                auto factor = big_float(temp_first[j][i]);
                for (auto k = 0; k < n; k++)
                {
                    temp_first[j][k] -= factor * temp_first[i][k];
                }

                temp_second[j] -= temp_second[i] * factor;
            }
        }

        return temp_second;
    }

    static std::tuple<matrix, matrix> qr_decomposition(const matrix& value, const big_float& epsilon)
    {
        if (value.row_size() != value.col_size())
        {
            throw std::invalid_argument("Error! Matrix must be equals by rows and collumns.");
        }

        auto n = value.row_size();
        matrix q_matrix(value);
        matrix r_matrix(n, n);

        for (int i = 0; i < n; i++)
        {
            auto norm = q_matrix[i].magnitude(epsilon);
            
            r_matrix[i][i] = norm;
            q_matrix[i] /= norm;

            for (int j = i + 1; j < n; j++)
            {
                auto dotProduct = q_matrix[i].dot_product(q_matrix[j]);
                r_matrix[j][i] = dotProduct;
                for (int k = 0; k < n; k++)
                {
                    auto temp = q_matrix[k] * dotProduct;
                    q_matrix[j] -= temp;
                }
            }

            for (int j = 0; j < n; j++)
            {
                q_matrix[i][j] = round(q_matrix[i][j], epsilon);
            }
        }

        return std::make_tuple(q_matrix, r_matrix);
    }

    static linear_vector eigen_values(const matrix& value, const big_float& epsilon, int max_iterations = 1000)
    {
        if (value.row_size() != value.col_size())
        {
            throw std::invalid_argument("Error! Matrix must be equals by rows and collumns.");
        }

        int n = value.row_size();
        auto A(value);
        matrix Q(n, n);
        matrix R(n, n);
        auto eps = big_float("1/10000");

        for (int iter = 0; iter < max_iterations; iter++)
        {
            std::tie(Q, R) = qr_decomposition(A, epsilon);;
            A = R * Q;

            // Проверка сходимости
            bool converged = true;
            for (int i = 0; i < n - 1; i++)
            {
                if (big_float::abs(A[i + 1][i]) > eps)
                {
                    converged = false;
                    break;
                }
            }

            if (converged) break;
        }

        linear_vector result(n);
        for (int i = 0; i < n; i++)
        {
            result[i] = A[i][i];
        }

        return result;
    }

#pragma endregion

};

#endif // ! _LINEAR_ALGEBRA_
