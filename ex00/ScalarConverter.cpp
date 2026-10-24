/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/25 03:27:01 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/10/25 03:27:03 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <limits>
#include <cstdlib>
#include <cerrno>
#include <cctype>
#include <cmath>

ScalarConverter::ScalarConverter(void) {}

ScalarConverter::~ScalarConverter(void) {}

ScalarConverter::ScalarConverter(const ScalarConverter &other) {
    *this = other;
}

ScalarConverter &ScalarConverter::operator=(const ScalarConverter &other) {
    (void)other;
    return *this;
}

/* ---------------------------- type detection ----------------------------- */

static bool isCharLiteral(const std::string &s) {
    if (s.length() == 3 && s[0] == '\'' && s[2] == '\'')
        return true;
    return (s.length() == 1 && !std::isdigit(static_cast<unsigned char>(s[0])));
}

static bool isIntLiteral(const std::string &s) {
    size_t i = 0;

    if (s[i] == '+' || s[i] == '-')
        i++;
    if (i == s.length())
        return false;
    for (; i < s.length(); i++)
        if (!std::isdigit(static_cast<unsigned char>(s[i])))
            return false;
    return true;
}

// [+-]digits.digits (at least one digit, exactly one dot)
static bool isDecimal(const std::string &s) {
    size_t i = 0;
    bool hasDigit = false;
    bool hasDot = false;

    if (!s.empty() && (s[0] == '+' || s[0] == '-'))
        i++;
    for (; i < s.length(); i++) {
        if (std::isdigit(static_cast<unsigned char>(s[i])))
            hasDigit = true;
        else if (s[i] == '.' && !hasDot)
            hasDot = true;
        else
            return false;
    }
    return hasDigit && hasDot;
}

static bool isPseudoLiteral(const std::string &s) {
    return (s == "nan" || s == "inf" || s == "+inf" || s == "-inf");
}

static bool isFloatLiteral(const std::string &s) {
    if (s.length() < 2 || s[s.length() - 1] != 'f')
        return false;
    std::string base = s.substr(0, s.length() - 1);
    return isPseudoLiteral(base) || isDecimal(base);
}

static bool isDoubleLiteral(const std::string &s) {
    return isPseudoLiteral(s) || isDecimal(s);
}

static bool parseDouble(const std::string &s, double &out) {
    if (s == "nan") {
        out = std::numeric_limits<double>::quiet_NaN();
        return true;
    }
    if (s == "inf" || s == "+inf") {
        out = std::numeric_limits<double>::infinity();
        return true;
    }
    if (s == "-inf") {
        out = -std::numeric_limits<double>::infinity();
        return true;
    }
    errno = 0;
    out = std::strtod(s.c_str(), NULL);
    return errno != ERANGE;
}

/* -------------------------------- display -------------------------------- */

template <typename T>
static std::string formatNumber(T value) {
    std::ostringstream oss;

    if (std::floor(value) == value && std::fabs(value) < 1e16)
        oss << std::fixed << std::setprecision(1);
    oss << value;
    return oss.str();
}

static void printImpossible(void) {
    std::cout << "char: impossible" << std::endl;
    std::cout << "int: impossible" << std::endl;
    std::cout << "float: impossible" << std::endl;
    std::cout << "double: impossible" << std::endl;
}

static void printChar(double value) {
    std::cout << "char: ";
    if (value != value
        || value < std::numeric_limits<char>::min()
        || value > std::numeric_limits<char>::max())
        std::cout << "impossible";
    else {
        char c = static_cast<char>(value);
        if (std::isprint(static_cast<unsigned char>(c)))
            std::cout << "'" << c << "'";
        else
            std::cout << "Non displayable";
    }
    std::cout << std::endl;
}

static void printInt(double value) {
    std::cout << "int: ";
    if (value != value
        || value < std::numeric_limits<int>::min()
        || value > std::numeric_limits<int>::max())
        std::cout << "impossible";
    else
        std::cout << static_cast<int>(value);
    std::cout << std::endl;
}

static void printFloat(float value) {
    std::cout << "float: ";
    if (value != value)
        std::cout << "nanf";
    else if (value == std::numeric_limits<float>::infinity())
        std::cout << "+inff";
    else if (value == -std::numeric_limits<float>::infinity())
        std::cout << "-inff";
    else
        std::cout << formatNumber(value) << "f";
    std::cout << std::endl;
}

static void printDouble(double value) {
    std::cout << "double: ";
    if (value != value)
        std::cout << "nan";
    else if (value == std::numeric_limits<double>::infinity())
        std::cout << "+inf";
    else if (value == -std::numeric_limits<double>::infinity())
        std::cout << "-inf";
    else
        std::cout << formatNumber(value);
    std::cout << std::endl;
}

/* ------------------------------ conversions ------------------------------ */

static void fromChar(char c) {
    printChar(static_cast<double>(c));
    std::cout << "int: " << static_cast<int>(c) << std::endl;
    printFloat(static_cast<float>(c));
    printDouble(static_cast<double>(c));
}

static void fromInt(int i) {
    printChar(static_cast<double>(i));
    std::cout << "int: " << i << std::endl;
    printFloat(static_cast<float>(i));
    printDouble(static_cast<double>(i));
}

static void fromFloat(float f) {
    printChar(static_cast<double>(f));
    printInt(static_cast<double>(f));
    printFloat(f);
    printDouble(static_cast<double>(f));
}

static void fromDouble(double d) {
    printChar(d);
    printInt(d);
    if (d == d && std::fabs(d) != std::numeric_limits<double>::infinity()
        && std::fabs(d) > std::numeric_limits<float>::max())
        std::cout << "float: impossible" << std::endl;
    else
        printFloat(static_cast<float>(d));
    printDouble(d);
}

void ScalarConverter::convert(const std::string &literal) {
    double value;

    if (literal.empty()) {
        printImpossible();
        return;
    }
    if (isCharLiteral(literal)) {
        fromChar(literal.length() == 3 ? literal[1] : literal[0]);
    } else if (isIntLiteral(literal)) {
        errno = 0;
        long l = std::strtol(literal.c_str(), NULL, 10);
        if (errno != ERANGE
            && l >= std::numeric_limits<int>::min()
            && l <= std::numeric_limits<int>::max())
            fromInt(static_cast<int>(l));
        else if (parseDouble(literal, value))
            fromDouble(value);
        else
            printImpossible();
    } else if (isFloatLiteral(literal)) {
        if (parseDouble(literal.substr(0, literal.length() - 1), value)
            && (value != value
                || std::fabs(value) == std::numeric_limits<double>::infinity()
                || std::fabs(value) <= std::numeric_limits<float>::max()))
            fromFloat(static_cast<float>(value));
        else
            printImpossible();
    } else if (isDoubleLiteral(literal)) {
        if (parseDouble(literal, value))
            fromDouble(value);
        else
            printImpossible();
    } else {
        printImpossible();
    }
}
