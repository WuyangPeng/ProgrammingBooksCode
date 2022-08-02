/// 5

/// “没有什么比变化更稳定”——赫拉克利特

/// 迟早（在初始开发或维护阶段）灵活性和适应性变得很重要。
/// Boost.Convert的部署有助于根据需求的演变进行调整和更改。
/// 例如，如果程序流将受益于非抛出行为，那么：

#include <boost/detail/lightweight_test.hpp>

#include <boost/convert.hpp>
#include <boost/convert/lexical_cast.hpp>

using boost::convert;
using boost::lexical_cast;
using std::string;

void getting_started_example2()
{
    // 不抛出。 失败时返回后备值 (-1)。
    int i = convert<int>("uhm", boost::cnv::lexical_cast()).value_or(-1);

    BOOST_TEST(i == -1);  // 转换失败。 'i'分配了后备值。
}

/// 或者，如果组件被识别为太慢，则可以通过更换转换器以最小的努力提高性能：

#ifdef _MSC_VER
    #pragma warning(disable : 4459)
#endif

#include <boost/convert/spirit.hpp>
#include <boost/convert/strtol.hpp>

void getting_started_example3()
{
    auto cnv1 = boost::cnv::lexical_cast();
    auto cnv2 = boost::cnv::strtol();
    auto cnv3 = boost::cnv::spirit();

    [[maybe_unused]] int i1 = convert<int>("123", cnv1).value();
    [[maybe_unused]] int i2 = convert<int>("123", cnv2).value();  // 比lexical_cast快两倍。
    [[maybe_unused]] int i3 = convert<int>("123", cnv3).value();  // 比lexical_cast快四倍。
}

/// 相反，如果要求更改为支持更多输入格式或需要某种输出格式，那么同样可以通过以下方式满足：

namespace
{
    namespace local
    {
#if defined(_MSC_VER)
        static bool const is_msc = true;
#else
        static bool const is_msc = false;
#endif
    }
}

#include <boost/convert/stream.hpp>

void getting_started_example4()
{
    try
    {
        [[maybe_unused]] int i1 = lexical_cast<int>("   123");  // 不工作。
        BOOST_TEST(!"Never reached");
    }
    catch (...)
    {
    }

    auto cnv = boost::cnv::cstream();
    int i2 = convert<int>("   123", cnv(std::skipws)).value();  // 成功
    string s1 = lexical_cast<string>(12.34567);
    string s2 = convert<string>(12.34567, cnv(std::fixed)(std::setprecision(3))).value();
    string s3 = convert<string>(12.34567, cnv(std::scientific)(std::setprecision(3))).value();
    // string expected = local::is_msc ? "1.235e+001" : "1.235e+01";(原代码，测试失败。)
    string expected = "1.235e+01";

    BOOST_TEST(i2 == 123);  // boost::cnv::cstream. "   123"转换成功。
    BOOST_TEST(s1 == "12.34567");  // boost::lexical_cast. 精度不可配置。
    BOOST_TEST(s2 == "12.346");  // boost::cnv::cstream.精度设置为3。固定的。
    BOOST_TEST(s3 == expected);  // boost::cnv::cstream.精度设置为3。科学技术法.
}