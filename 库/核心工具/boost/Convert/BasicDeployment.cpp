/// 4

/// 对于顽固的boost::lexical_cast用户或作为 boost::convert的过渡路径，boost::convert部署之一与boost::lexical_cast没有什么不同。
/// 事实上，原来的boost::lexical_cast功能通过boost::convert接口很容易部署：

#include <boost/detail/lightweight_test.hpp>

//[getting_started_headers1
#include <boost/convert.hpp>
#include <boost/convert/lexical_cast.hpp>
//]

//[getting_started_using
using boost::convert;
using boost::lexical_cast;
using std::string;
//]

//[getting_started_default_converter
// Definition of the default converter (optional)
// 默认转换器的定义（可选）
struct boost::cnv::by_default : boost::cnv::lexical_cast
{
};
//]

void getting_started_example1()
{
    //[getting_started_example1
    try
    {
        auto cnv = boost::cnv::lexical_cast();  // boost::lexical_cast-based converter（boost::lexical_cast-based 转换器）
        int i1 = lexical_cast<int>("123");  // boost::lexical_cast standard deployment（boost::lexical_cast 标准部署）
        int i2 = convert<int>("123").value();  // boost::convert with the default converter（boost::convert 使用默认转换器）
        int i3 = convert<int>("123", cnv).value();  // boost::convert with an explicit converter（boost::convert 使用显式转换器）
        string s1 = lexical_cast<string>(123);  // boost::lexical_cast standard deployment（boost::lexical_cast 标准部署）
        string s2 = convert<string>(123).value();  // boost::convert with the default converter（boost::convert 使用默认转换器）
        string s3 = convert<string>(123, cnv).value();  // boost::convert with an explicit converter（boost::convert 使用显式转换器）

        BOOST_TEST(i1 == 123);
        BOOST_TEST(i2 == 123);
        BOOST_TEST(i3 == 123);
        BOOST_TEST(s1 == "123");
        BOOST_TEST(s2 == "123");
        BOOST_TEST(s3 == "123");
    }
    catch (std::exception const& ex)
    {
        // Please be aware that the conversion requests above can fail.
        // Use try'n'catch blocks to handle any exceptions thrown.
        // Ignore this at your peril!
        // 请注意，上述转换请求可能会失败。 使用try'n'catch块来处理抛出的任何异常。忽略这一点，后果自负！
        std::cerr << "Exception " << ex.what() << std::endl;
    }
    //] [/getting_started_example1]
}

/// [重要] 重要
/// 当我们进一步探索 boost::convert 行为和接口时，起初它们可能会显得过于复杂、冗长等等......不像 atoi()......因为所有错误的原因而如此出名。
/// :-) 重要的是要记住，转换请求只是一个可能成功但也可能失败的请求……这可能不像人们希望的那样罕见或例外。 
/// boost::convert（以及 boost::lexical_cast）行为和接口反映了这一现实。