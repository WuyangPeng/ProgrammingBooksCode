/// 2

/// 介绍
/// Boost.Convert建立在boost::lexical_cast经验的基础上，并进一步将那些类型转换/转换相关的想法

/// 适用于更广泛的与转换相关的部署场景，
/// 提供更灵活、可配置和可扩展的类型转换框架，
/// 提供通用一致的行为，
/// 通过一个一致的界面统一和统一部署各种转换设施。

/// Boost.Convert提供了新的和熟悉的与转换/转换相关的功能，例如：

/// 表示部署不符合默认可构造性要求的类型；

/// 四种类型的转换失败检测：
/// 作为同一流程的一部分——基本的和通用的；
/// 作为一个分支流程——基于异常和基于函数；

/// 选择立即或延迟抛出异常和不抛出转换失败处理；

/// 通过以下方式灵活处理转换失败：
/// 抛出异常；
/// 返回的后备值；
/// 调用的后备函数；

/// 支持标准算法。

/// Boost.Convert 由两个组件组成：

/// boost::convert()接口；
/// 可扩展的可插拔转换器集合。

/// boost::convert()接口

/// 宣传、提供和确保某些一致的行为；
/// 统一并为各种转换工具提供一个一致的接口。

/// 可插拔转换器的集合独立于 boost::convert() API 门面，并且被设计为可扩展和随时间扩展。目前提供以下转换器：

/// 基于boost::lexical_cast,
/// 基于 printf/scanf，
/// 受strtol启发，
/// 基于std::stringstream的，
/// 基于boost::spirit。

/// 这些转换器提供了新的和熟悉的功能，并演示了如何将现有的独立转换工具合并到Boost.Convert框架中。
/// 例如，基于std::stream的转换器利用标准std::streams功能并提供：

/// 字符串到类型和类型到字符串的转换；
/// 格式支持（基于 std::ios 的精度、基数、大写/小写、科学等）；
/// 支持不同的语言环境；
/// char 和 wchar_t 支持。

/// 以下代码演示了整数数组从其文本十六进制表示形式的转换。它将-1分配给那些无法转换的：

#include <boost/convert.hpp>
#include <boost/convert/lexical_cast.hpp>
#include <boost/convert/stream.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <array>
#include <functional>
#include <vector>

using std::string;

void introduction()
{
    //[algorithm_introduction

    /*`The following code demonstrates conversion of an array of integers from their textual ['hexadecimal]
      representation. It assigns -1 to those which fail to convert:
      以下代码演示了整数数组从其文本十六进制表示形式的转换。它将-1分配给那些无法转换的：
   */

    std::array<char const*, 3> strs = { { " 5", "0XF", "not an int" } };
    std::vector<int> ints;
    boost::cnv::cstream cnv;

    // Configure converter to read hexadecimal, skip (leading) white spaces.
    // 将转换器配置为读取十六进制，跳过（前导）空格。
    cnv(std::hex)(std::skipws);

    std::transform(strs.begin(), strs.end(), std::back_inserter(ints), boost::cnv::apply<int>(std::cref(cnv)).value_or(-1));

    BOOST_TEST(ints.size() == 3);  // Number of values processed.（处理的值的数量。）
    BOOST_TEST(ints[0] == 5);  // " 5"
    BOOST_TEST(ints[1] == 15);  // "0XF"
    BOOST_TEST(ints[2] == -1);  // "not an int"

    //]
}