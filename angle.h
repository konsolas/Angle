//
// Created by Vincent on 04/12/2019.
//

#ifndef ANGLE_ANGLE_H
#define ANGLE_ANGLE_H

#include <concepts>
#include <cmath>

namespace ang {
    template<typename T> concept floating_point = std::is_floating_point_v<T>;
    constexpr double m_pi = 3.14159265358979323846;
    constexpr double m_2pi = 2 * m_pi;

    template<floating_point rep>
    rep wrap_fp(rep val) noexcept {
        return -m_pi + std::fmod(m_2pi + std::fmod(val + m_pi, m_2pi), m_2pi);
    }

    template<floating_point rep, auto wrap>
    class basic_angle {
        rep value; // [-pi, pi)
    public:
        constexpr basic_angle() = default;
        constexpr explicit basic_angle(rep value) noexcept(std::is_arithmetic_v<rep>)
                : value(std::invoke(wrap, value)) {};

        constexpr basic_angle &operator+=(const basic_angle &o) noexcept(std::is_arithmetic_v<rep>) {
            value = wrap(value + o.value);
            return *this;
        }

        constexpr basic_angle &operator-=(const basic_angle &o) noexcept(std::is_arithmetic_v<rep>) {
            value = wrap(value - o.value);
            return *this;
        }

        [[nodiscard]] constexpr rep radians() const noexcept(std::is_arithmetic_v<rep>) {
            return value;
        }

        [[nodiscard]] constexpr rep degrees() const noexcept(std::is_arithmetic_v<rep>) {
            return value * 180.0 / m_pi;
        }
    };

    template<floating_point rep, auto wrap>
    [[nodiscard]] constexpr basic_angle<rep, wrap>
    operator+(basic_angle<rep, wrap> l, const basic_angle<rep, wrap> &r) noexcept(std::is_arithmetic_v<rep>) {
        l += r;
        return l;
    }

    template<floating_point rep, auto wrap>
    [[nodiscard]] constexpr basic_angle<rep, wrap>
    operator-(basic_angle<rep, wrap> l, const basic_angle<rep, wrap> &r) noexcept(std::is_arithmetic_v<rep>) {
        l -= r;
        return l;
    }

    template<floating_point rep, auto wrap>
    [[nodiscard]] constexpr basic_angle<rep, wrap>
    operator-(const basic_angle<rep, wrap> &r) noexcept(std::is_arithmetic_v<rep>) {
        return basic_angle<rep, wrap>(-r.radians());
    }

    template<floating_point rep, auto wrap>
    [[nodiscard]] constexpr bool
    operator==(const basic_angle<rep, wrap> &l, const basic_angle<rep, wrap> &r) noexcept(std::is_arithmetic_v<rep>) {
        return l.value == r.value;
    }

    template<floating_point rep, auto wrap>
    [[nodiscard]] constexpr bool
    operator!=(const basic_angle<rep, wrap> &l, const basic_angle<rep, wrap> &r) noexcept(std::is_arithmetic_v<rep>) {
        return !(l == r);
    }

    template<floating_point rep, auto wrap>
    [[nodiscard]] constexpr bool
    operator<(const basic_angle<rep, wrap> &l, const basic_angle<rep, wrap> &r) noexcept(std::is_arithmetic_v<rep>) {
        return l.radians() < r.radians();
    }

    template<floating_point rep, auto wrap>
    [[nodiscard]] constexpr bool
    operator<=(const basic_angle<rep, wrap> &l, const basic_angle<rep, wrap> &r) noexcept(std::is_arithmetic_v<rep>) {
        return !(r < l);
    }

    template<floating_point rep, auto wrap>
    [[nodiscard]] constexpr bool
    operator>(const basic_angle<rep, wrap> &l, const basic_angle<rep, wrap> &r) noexcept(std::is_arithmetic_v<rep>) {
        return r < l;
    }

    template<floating_point rep, auto wrap>
    [[nodiscard]] constexpr bool
    operator>=(const basic_angle<rep, wrap> &l, const basic_angle<rep, wrap> &r) noexcept(std::is_arithmetic_v<rep>) {
        return !(l < r);
    }

    using angle = basic_angle<double, wrap_fp<double>>;

    namespace literals {
        constexpr angle operator ""_rad(long double value) {
            return angle(value);
        }

        constexpr angle operator ""_deg(long double value) {
            return angle(value * m_pi / 180.0);
        }
    }
}

#endif //ANGLE_ANGLE_H
