#include <iostream>
#include <vector>
#include <iomanip>
#include <cassert>
#include <random>
#include <cmath>

class LinAlg
{
private:
    LinAlg(){};

    template <typename T>
    std::vector<std::vector<T>> IDotProduct(const std::vector<std::vector<T>> &matA, const std::vector<std::vector<T>> &matB)
    {
        assert(matA[0].size() == matB.size());

        std::vector<std::vector<T>> out(matA.size(), std::vector<T>(matB[0].size()));
        for (int i = 0; i < matA.size(); i++)
        {
            for (int j = 0; j < matB[0].size(); j++)
            {
                T sum{0};
                for (int k = 0; k < matB.size(); k++)
                {
                    sum += matA[i][k] * matB[k][j];
                }
                out[i][j] = sum;
            }
        }
        return out;
    }

    template <typename T>
    std::vector<std::vector<T>> IAddVecToMat(const std::vector<std::vector<T>> &mat, const std::vector<T> &vec)
    {
        assert(mat[0].size() == vec.size());
        std::vector<std::vector<T>> out(mat.size(), std::vector<T>(mat[0].size(), 0));
        for (int i = 0; i < out.size(); i++)
            for (int j = 0; j < out[0].size(); j++)
                out[i][j] = mat[i][j] + vec[j];

        return out;
    }

    template <typename T>
    std::vector<std::vector<T>> IAdd(const std::vector<std::vector<T>> &matA, const std::vector<std::vector<T>> &matB)
    {
        assert(matA.size() == matB.size() && matA[0].size() == matB[0].size());
        std::vector<std::vector<T>> out(matA.size(), std::vector<T>(matA[0].size(), 0));
        for (int i = 0; i < out.size(); i++)
            for (int j = 0; j < out[0].size(); j++)
                out[i][j] = matA[i][j] + matB[i][j];

        return out;
    }

    template <typename T>
    std::vector<T> IAdd(const std::vector<T> &vecA, const std::vector<T> &vecB)
    {
        assert(vecA.size() == vecB.size());
        std::vector<T> out(vecA.size(), 0.0);
        for (int i = 0; i < out.size(); i++)
            out[i] = vecA[i] + vecB[i];

        return out;
    }

    template <typename T>
    std::vector<std::vector<T>> IDiff(const std::vector<std::vector<T>> &matA, const std::vector<std::vector<T>> &matB)
    {
        assert(matA.size() == matB.size() && matA[0].size() == matB[0].size());
        std::vector<std::vector<T>> out(matA.size(), std::vector<T>(matA[0].size(), 0));
        for (int i = 0; i < out.size(); i++)
            for (int j = 0; j < out[0].size(); j++)
                out[i][j] = matA[i][j] - matB[i][j];

        return out;
    }

    template <typename T>
    std::vector<T> IDiff(const std::vector<T> &vecA, const std::vector<T> &vecB)
    {
        assert(vecA.size() == vecB.size());
        std::vector<double> out(vecA.size(), 0);
        for (int i = 0; i < out.size(); i++)
            out[i] = vecA[i] - vecB[i];

        return out;
    }

    template <typename T>
    std::vector<std::vector<T>> IMul(std::vector<std::vector<T>> matA, std::vector<std::vector<T>> matB)
    {
        assert(matA.size() == matB.size() && matA[0].size() == matB[0].size());
        std::vector<std::vector<T>> out(matA.size(), std::vector<T>(matA[0].size(), 0));
        for (int i = 0; i < out.size(); i++)
            for (int j = 0; j < out[0].size(); j++)
                out[i][j] = matA[i][j] * matB[i][j];

        return out;
    }

    template <typename T>
    std::vector<std::vector<T>> IMul(double scalar, std::vector<std::vector<T>> mat)
    {
        std::vector<std::vector<T>> out(mat.size(), std::vector<T>(mat[0].size(), 0));
        for (int i = 0; i < out.size(); i++)
            for (int j = 0; j < out[0].size(); j++)
                out[i][j] = scalar * mat[i][j];

        return out;
    }

    template <typename T>
    std::vector<T> IMul(double scalar, std::vector<T> vec)
    {
        std::vector<T> out(vec.size(), 0);
        for (int i = 0; i < out.size(); i++)
            out[i] = scalar * vec[i];

        return out;
    }

    template <typename T>
    std::vector<std::vector<T>> ITranspose(std::vector<std::vector<T>> mat)
    {
        std::vector<std::vector<T>> out(mat[0].size(), std::vector<T>(mat.size(), 0.0));
        for (int i = 0; i < out.size(); i++)
            for (int j = 0; j < out[0].size(); j++)
                out[i][j] = mat[j][i];

        return out;
    }

    double IGetRandomDouble()
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::normal_distribution<double> dis(0.0, 1.0);
        return dis(gen);
    }

public:
    LinAlg(const LinAlg &) = delete;

    static LinAlg &Get()
    {
        static LinAlg la_Instance;
        return la_Instance;
    }
    template <typename T>
    static std::vector<std::vector<T>> DotProduct(const std::vector<std::vector<T>> &matA, const std::vector<std::vector<T>> &matB) { return Get().IDotProduct(matA, matB); }
    template <typename T>
    static std::vector<std::vector<T>> AddVecToMat(const std::vector<std::vector<T>> &mat, const std::vector<T> &vec) { return Get().IAddVecToMat(mat, vec); };
    template <typename T>
    static std::vector<std::vector<T>> Add(const std::vector<std::vector<T>> &matA, const std::vector<std::vector<T>> &matB) { return Get().IAdd(matA, matB); }
    template <typename T>
    static std::vector<T> Add(const std::vector<T> &vecA, const std::vector<T> &vecB) { return Get().IAdd(vecA, vecB); }
    template <typename T>
    static std::vector<std::vector<T>> Diff(const std::vector<std::vector<T>> &matA, const std::vector<std::vector<T>> &matB) { return Get().IDiff(matA, matB); }
    template <typename T>
    static std::vector<T> Diff(const std::vector<T> &vecA, const std::vector<T> &vecB) { return Get().IDiff(vecA, vecB); }
    template <typename T>
    static std::vector<std::vector<T>> Mul(std::vector<std::vector<T>> matA, std::vector<std::vector<T>> matB) { return Get().IMul(matA, matB); };
    template <typename T>
    static std::vector<std::vector<T>> Mul(double scalar, std::vector<std::vector<T>> mat) { return Get().IMul(scalar, mat); };
    template <typename T>
    static std::vector<T> Mul(double scalar, std::vector<T> vec) { return Get().IMul(scalar, vec); };
    template <typename T>
    static std::vector<std::vector<T>> Transpose(std::vector<std::vector<T>> mat) { return Get().ITranspose(mat); };
    static double GetRandomDouble() { return Get().IGetRandomDouble(); }
};

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &vec)
{
    for (int i = 0; i < vec.size(); i++)
    {
        os << std::setw(15) << std::setprecision(10) << std::fixed << vec[i];
    }
    return os;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<std::vector<T>> &mat)
{
    for (int i = 0; i < mat.size(); i++)
    {
        os << mat[i] << std::endl;
    }
    return os;
}