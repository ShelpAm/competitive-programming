#pragma once

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <numbers>
#include <vector>

namespace shelpam::math {

template <typename Value, std::size_t Dimension> struct Vector {
    friend auto operator+(Vector lhs, Vector const &rhs)
    {
        return lhs += rhs;
    }

    friend auto operator-(Vector lhs, Vector const &rhs)
    {
        return lhs -= rhs;
    }

    friend auto dot(Vector const &lhs, Vector const &rhs) -> Value
    {
        Value result{};
        for (std::size_t i{}; i != Dimension; ++i) {
            result += lhs.coordinate[i] * rhs.coordinate[i];
        }
        return result;
    }

    // 向量 * 标量
    friend auto operator*(Vector lhs, Value const &scalar)
    {
        return lhs *= scalar;
    }

    // 标量 * 向量
    friend auto operator*(Value const &scalar, Vector const &rhs)
    {
        Vector result = rhs;
        return result *= scalar;
    }

    // 向量 / 标量
    friend auto operator/(Vector lhs, Value const &scalar)
    {
        return lhs /= scalar;
    }

    friend std::istream &operator>>(std::istream &is, Vector &self)
    {
        for (auto &v : self.coordinate) {
            is >> v;
        }
        return is;
    }

    Vector &operator+=(Vector const &rhs)
    {
        for (std::size_t i{}; i != Dimension; ++i) {
            coordinate.at(i) += rhs.coordinate.at(i);
        }
        return *this;
    }

    Vector &operator-=(Vector const &rhs)
    {
        for (std::size_t i{}; i != Dimension; ++i) {
            coordinate.at(i) -= rhs.coordinate.at(i);
        }
        return *this;
    }

    // 数乘赋值运算符
    Vector &operator*=(Value const &scalar)
    {
        for (std::size_t i{}; i != Dimension; ++i) {
            coordinate.at(i) *= scalar;
        }
        return *this;
    }

    // 数除赋值运算符
    Vector &operator/=(Value const &scalar)
    {
        if (scalar == Value{}) {
            throw std::invalid_argument("Division by zero");
        }
        for (std::size_t i{}; i != Dimension; ++i) {
            coordinate.at(i) /= scalar;
        }
        return *this;
    }

    bool operator==(Vector const &rhs) const
    {
        return coordinate == rhs.coordinate;
    }

    [[nodiscard]] Value x() const
    {
        return coordinate.at(0);
    }

    [[nodiscard]] Value y() const
    {
        return coordinate.at(1);
    }

    [[nodiscard]] Value z() const
    {
        return coordinate.at(2);
    }

    [[nodiscard]] auto length() const
    {
        Value result{};
        for (auto e : coordinate) {
            result += e * e;
        }
        return std::sqrt(result);
    }

    std::array<Value, Dimension> coordinate{};
};

template <typename Value_type> using Vector2d = Vector<Value_type, 2>;

template <typename T> T cross(Vector2d<T> const &a, Vector2d<T> const &b)
{
    return (a.coordinate[0] * b.coordinate[1]) -
           (a.coordinate[1] * b.coordinate[0]);
}

template <typename Value_type> class Line2d {
    friend Vector<Value_type, 2> intersect(Line2d const &lhs, Line2d const &rhs)
    {
    }

    std::array<Vector<Value_type, 2>, 2> points;
};

/// @return angle in Radians
double polar_angle(Vector2d<std::int_least64_t> v)
{
    auto result = std::atan2(v.coordinate[1], v.coordinate[0]);
    if (result < 0) {
        result += 2 * std::numbers::pi;
    }
    return result;
}

// 计算凸包，返回凸包顶点索引的顺序
template <typename T>
std::vector<Vector2d<T>> convex_hull(std::vector<Vector2d<T>> points)
{
    if (points.size() <= 3) {
        return points;
    }

    // 1. 找到最低的点（Y最小，Y相同X最小）
    auto it = std::min_element(points.begin(), points.end(),
                               [](auto const &a, auto const &b) {
                                   return (a.coordinate[1] < b.coordinate[1]) ||
                                          (a.coordinate[1] == b.coordinate[1] &&
                                           a.coordinate[0] < b.coordinate[0]);
                               });
    std::swap(points[0], *it);
    Vector2d<T> base = points[0];

    // 2. 按极角排序（以 base 点为原点）
    std::sort(points.begin() + 1, points.end(),
              [&base](auto const &a, auto const &b) {
                  Vector2d<T> va = a - base;
                  Vector2d<T> vb = b - base;
                  auto c = cross(va, vb);
                  if (c == 0) { // 共线，离base近的排前面
                      auto da = (va.coordinate[0] * va.coordinate[0]) +
                                (va.coordinate[1] * va.coordinate[1]);
                      auto db = (vb.coordinate[0] * vb.coordinate[0]) +
                                (vb.coordinate[1] * vb.coordinate[1]);
                      return da < db;
                  }
                  return c > 0;
              });

    // 3. 使用栈构造凸包
    std::vector<Vector2d<T>> hull;
    hull.push_back(points[0]);
    hull.push_back(points[1]);

    for (size_t i = 2; i < points.size(); ++i) {
        while (hull.size() > 1) {
            Vector2d<T> v1 = hull.back() - hull[hull.size() - 2];
            Vector2d<T> v2 = points[i] - hull.back();
            if (cross(v1, v2) > 0) {
                break; // 左转，保持凸包
            }
            hull.pop_back(); // 右转，pop
        }
        hull.push_back(points[i]);
    }
    return hull;
}

} // namespace shelpam::math
