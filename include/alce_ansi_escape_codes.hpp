/**
 *  @author  Anstro Pleuton (https://github.com/anstropleuton)
 *  @brief   Functionality to print ANSI Escape Code formatted text in terminal.
 *
 *  @copyright  Copyright (c) 2024 Anstro Pleuton
 *
 *      _    _
 *     / \  | | ___ ___    _    ___ ___ ___    _   _____   __
 *    / _ \ | |/ __/ _ \  | |  |_ _| _ ) _ \  /_\ | _ \ \ / /
 *   / ___ \| | (_|  __/  | |__ | || _ \   / / _ \|   /\ V /
 *  /_/   \_\_|\___\___|  |____|___|___/_|_\/_/ \_\_|_\ |_|
 *
 *  Alce Library is a collection of utils for Anstro Pleuton's programs.
 *
 *  This software is licensed under the terms of MIT License.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to
 *  deal in the Software without restriction, including without limitation the
 *  rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 *  sell copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 *  IN THE SOFTWARE.
 *
 *  Credits where credit's due:
 *  - ASCII Art generated using https://www.patorjk.com/software/taag with font
 *    "Standard" (for "Alce") and "Small" (for "LIBRARY").
 */

#pragma once

#include <ostream>
#include <string>

/**
 *  @brief  All Alce Library's contents in this namespace.  Just do
 *          `using namespace alce` to make your life easier.
 */
namespace alce {

/**
 *  @brief  ANSI Escape Codes.
 *  @see  https://en.wikipedia.org/wiki/Ansi_escape_code#Colors .
 */
namespace aec {

/**
 *  @brief  Control Sequence Initializer
 */
inline constinit std::string_view csi = "\x1b\x5b";

/**
 *  @brief  Format code for Select Graphics Rendition.
 *
 *  @param  code  An SGR code.
 *  @return  Formatted SGR code ready to be std::cout'd or std::print'd.
 */
[[nodiscard]] inline constexpr auto sgr(std::string_view code)
{
    ///  @todo  After C++26 remove this cast to std::string.
    return std::string(csi) + std::string(code) + "m";
}

/**
 *  @brief  Callable object for ANSI Escape Codes.
 *
 *  Easily use this to format the string with cleanness.  For example:
    ```cpp
    std::cout << red << "Red text" << reset_color << std::endl;
    std::cout << white("White text") << std::endl;
    std::cout << bold << "Bolded text" << !bold << std::endl;
    ```
 *
 *  You can also combine them with +, *, |, &, || and && operators:
    ```cpp
    std::cout << blue + italic + underline << "Blue italic underlined text"
              << reset << std::endl;
    ```
 *
 *  @todo  Make ! and ~ operators return reverse object instead of returning the
 *         resetter, if possible, to allow:
    ```cpp
    std::cout << bold << "Bold text, " << ~bold("Not bold text, ")
              << "Still bold text" << ~bold << std::endl;
    ```
 */
struct aec_t {

    /**
     *  @brief  Set up escape code sequence before text.
     */
    std::string setter;

    /**
     *  @brief  Reseting escape code sequence after text.
     */
    std::string resetter;

    /**
     *  @brief  Combine sequence with text to get ANSI Escape Code formatted
     *          text.
     *
     *  The setter sequence is placed before text, followed by the resetter
     *  sequence.
     *
     *  @param  text  The text to format.
     *  @return  Combined sequence for formatted text.
     */
    [[nodiscard]] inline constexpr auto operator() (std::string_view text) const
    {
        ///  @todo  After C++26 remove this cast to std::string.
        return setter + std::string(text) + resetter;
    }

    /**
     *  @brief  Object call without parameter to get only the setter.
     *  @return  Setter sequence string.
     */
    [[nodiscard]] inline constexpr auto operator() () const
    {
        return setter;
    }

    /**
     *  @brief  Logical NOT operator to get the resetter.
     *  @return  Resetter sequence string.
     */
    [[nodiscard]] inline constexpr auto operator! () const
    {
        return resetter;
    }

    /**
     *  @brief  Bitwise NOT operator to get the resetter.
     *  @return  Resetter sequence string.
     */
    [[nodiscard]] inline constexpr auto operator~ () const
    {
        return resetter;
    }

    /**
     *  @brief  Conversion operator to get setter.
     *  @return  Setter sequence string.
     */
    [[nodiscard]] inline constexpr operator auto () const
    {
        return setter;
    }
};

/**
 *  @brief  Combine two AECs to get a combined AEC.
 *
 *  @param  a  The first AEC.
 *  @param  b  The second AEC.
 *  @return  Combined AEC.
 */
[[nodiscard]] inline constexpr auto combine(const aec_t a, const aec_t b)
{
    return aec_t { a.setter + b.setter, a.resetter + b.resetter };
}

///  @todo  Add more AECs.

inline const aec_t reset         = { sgr("0"), sgr("0") };
inline const aec_t bold          = { sgr("1"), sgr("22") };
inline const aec_t faint         = { sgr("2"), sgr("22") };
inline const aec_t italic        = { sgr("3"), sgr("23") };
inline const aec_t underline     = { sgr("4"), sgr("24") };
inline const aec_t reverse_video = { sgr("7"), sgr("27") };
inline const aec_t strike        = { sgr("9"), sgr("29") };

inline const aec_t black          = { sgr("30"), sgr("39") };
inline const aec_t red            = { sgr("31"), sgr("39") };
inline const aec_t green          = { sgr("32"), sgr("39") };
inline const aec_t yellow         = { sgr("33"), sgr("39") };
inline const aec_t blue           = { sgr("34"), sgr("39") };
inline const aec_t magenta        = { sgr("35"), sgr("39") };
inline const aec_t cyan           = { sgr("36"), sgr("39") };
inline const aec_t white          = { sgr("37"), sgr("39") };
inline const aec_t gray           = { sgr("90"), sgr("39") };
inline const aec_t bright_red     = { sgr("91"), sgr("39") };
inline const aec_t bright_green   = { sgr("92"), sgr("39") };
inline const aec_t bright_yellow  = { sgr("93"), sgr("39") };
inline const aec_t bright_blue    = { sgr("94"), sgr("39") };
inline const aec_t bright_magenta = { sgr("95"), sgr("39") };
inline const aec_t bright_cyan    = { sgr("96"), sgr("39") };
inline const aec_t bright_white   = { sgr("97"), sgr("39") };

inline const aec_t black_bg          = { sgr("40"), sgr("49") };
inline const aec_t red_bg            = { sgr("41"), sgr("49") };
inline const aec_t green_bg          = { sgr("42"), sgr("49") };
inline const aec_t yellow_bg         = { sgr("43"), sgr("49") };
inline const aec_t blue_bg           = { sgr("44"), sgr("49") };
inline const aec_t magenta_bg        = { sgr("45"), sgr("49") };
inline const aec_t cyan_bg           = { sgr("46"), sgr("49") };
inline const aec_t white_bg          = { sgr("47"), sgr("49") };
inline const aec_t gray_bg           = { sgr("100"), sgr("49") };
inline const aec_t bright_red_bg     = { sgr("101"), sgr("49") };
inline const aec_t bright_green_bg   = { sgr("102"), sgr("49") };
inline const aec_t bright_yellow_bg  = { sgr("103"), sgr("49") };
inline const aec_t bright_blue_bg    = { sgr("104"), sgr("49") };
inline const aec_t bright_magenta_bg = { sgr("105"), sgr("49") };
inline const aec_t bright_cyan_bg    = { sgr("106"), sgr("49") };
inline const aec_t bright_white_bg   = { sgr("107"), sgr("49") };

} // namespace aec

/**
 *  @brief  ANSI Escape Code formatter, easer operators.
 */
namespace aec_operators {

/**
 *  @brief  Overload << operator for streams and AEC.
 *
 *  @param  ostream  An output stream.
 *  @param  aec      An AEC.
 *  @return  Output stream.
 */
[[nodiscard]] inline constexpr auto operator<< (
    std::ostream     &ostream,
    const aec::aec_t &aec
) -> std::ostream &
{
    ostream << std::string(aec);
    return ostream;
}

/**
 *  @brief  Operator to combine AECs.
 *
 *  @param  a  The first AEC.
 *  @param  b  The second AEC.
 *  @return  Combined AEC.
 */
[[nodiscard]] inline constexpr auto operator+ (
    const aec::aec_t &a,
    const aec::aec_t &b
)
{
    return aec::combine(a, b);
}

/**
 *  @brief  Operator to combine AECs.
 *
 *  @param  a  The first AEC.
 *  @param  b  The second AEC.
 *  @return  Combined AEC.
 */
[[nodiscard]] inline constexpr auto operator* (
    const aec::aec_t &a,
    const aec::aec_t &b
)
{
    return aec::combine(a, b);
}

/**
 *  @brief  Operator to combine AECs.
 *
 *  @param  a  The first AEC.
 *  @param  b  The second AEC.
 *  @return  Combined AEC.
 */
[[nodiscard]] inline constexpr auto operator& (
    const aec::aec_t &a,
    const aec::aec_t &b
)
{
    return aec::combine(a, b);
}

/**
 *  @brief  Operator to combine AECs.
 *
 *  @param  a  The first AEC.
 *  @param  b  The second AEC.
 *  @return  Combined AEC.
 */
[[nodiscard]] inline constexpr auto operator| (
    const aec::aec_t &a,
    const aec::aec_t &b
)
{
    return aec::combine(a, b);
}

/**
 *  @brief  Operator to combine AECs.
 *
 *  @param  a  The first AEC.
 *  @param  b  The second AEC.
 *  @return  Combined AEC.
 */
[[nodiscard]] inline constexpr auto operator&& (
    const aec::aec_t &a,
    const aec::aec_t &b
)
{
    return aec::combine(a, b);
}

/**
 *  @brief  Operator to combine AECs.
 *
 *  @param  a  The first AEC.
 *  @param  b  The second AEC.
 *  @return  Combined AEC.
 */
[[nodiscard]] inline constexpr auto operator|| (
    const aec::aec_t &a,
    const aec::aec_t &b
)
{
    return aec::combine(a, b);
}

} // namespace aec_operators

} // namespace alce

namespace std {

/**
 *  @brief  Formatter for @c aec::aec .
 *
 *  @param  char_type  The character type.
 */
template<typename char_type>
struct formatter<alce::aec::aec_t, char_type> {

    /**
     *  @brief  Parse the format specifiers (none).
     *
     *  @tparam  parse_context  A parse context type.
     *  @param   ctx           A parse context.
     *  @return  Iterator to begin of parse context.
     */
    template<typename parse_context>
    [[nodiscard]] inline constexpr auto parse(parse_context &ctx)
    -> parse_context::iterator
    {
        // No format specifiers
        return ctx.begin();
    }

    /**
     *  @brief  Format the string using parsed specifiers (none).
     *
     *  @tparam  format_context  A format context type.
     *  @param   aec            The AEC to format.
     *  @param   ctx            A format context.
     *  @return  Iterator to end of format context.
     */
    template<typename format_context>
    [[nodiscard]] inline constexpr auto format(
        const alce::aec::aec_t &aec,
        format_context          &ctx
    ) const
    {
        return std::ranges::copy((std::string)aec, ctx.out()).out;
    }
};

} // namespace std
