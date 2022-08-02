/// 4

/// ������̵�boost::lexical_cast�û�����Ϊ boost::convert�Ĺ���·����boost::convert����֮һ��boost::lexical_castû��ʲô��ͬ��
/// ��ʵ�ϣ�ԭ����boost::lexical_cast����ͨ��boost::convert�ӿں����ײ���

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
// Ĭ��ת�����Ķ��壨��ѡ��
struct boost::cnv::by_default : boost::cnv::lexical_cast
{
};
//]

void getting_started_example1()
{
    //[getting_started_example1
    try
    {
        auto cnv = boost::cnv::lexical_cast();  // boost::lexical_cast-based converter��boost::lexical_cast-based ת������
        int i1 = lexical_cast<int>("123");  // boost::lexical_cast standard deployment��boost::lexical_cast ��׼����
        int i2 = convert<int>("123").value();  // boost::convert with the default converter��boost::convert ʹ��Ĭ��ת������
        int i3 = convert<int>("123", cnv).value();  // boost::convert with an explicit converter��boost::convert ʹ����ʽת������
        string s1 = lexical_cast<string>(123);  // boost::lexical_cast standard deployment��boost::lexical_cast ��׼����
        string s2 = convert<string>(123).value();  // boost::convert with the default converter��boost::convert ʹ��Ĭ��ת������
        string s3 = convert<string>(123, cnv).value();  // boost::convert with an explicit converter��boost::convert ʹ����ʽת������

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
        // ��ע�⣬����ת��������ܻ�ʧ�ܡ� ʹ��try'n'catch���������׳����κ��쳣��������һ�㣬����Ը���
        std::cerr << "Exception " << ex.what() << std::endl;
    }
    //] [/getting_started_example1]
}

/// [��Ҫ] ��Ҫ
/// �����ǽ�һ��̽�� boost::convert ��Ϊ�ͽӿ�ʱ��������ǿ��ܻ��Եù��ڸ��ӡ��߳��ȵ�......���� atoi()......��Ϊ���д����ԭ�����˳�����
/// :-) ��Ҫ����Ҫ��ס��ת������ֻ��һ�����ܳɹ���Ҳ����ʧ�ܵ����󡭡�����ܲ�������ϣ�����������������⡣ 
/// boost::convert���Լ� boost::lexical_cast����Ϊ�ͽӿڷ�ӳ����һ��ʵ��