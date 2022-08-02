/// 2

/// ����
/// Boost.Convert������boost::lexical_cast����Ļ����ϣ�����һ������Щ����ת��/ת����ص��뷨

/// �����ڸ��㷺����ת����صĲ��𳡾���
/// �ṩ���������úͿ���չ������ת����ܣ�
/// �ṩͨ��һ�µ���Ϊ��
/// ͨ��һ��һ�µĽ���ͳһ��ͳһ�������ת����ʩ��

/// Boost.Convert�ṩ���µĺ���Ϥ����ת��/ת����صĹ��ܣ����磺

/// ��ʾ���𲻷���Ĭ�Ͽɹ�����Ҫ������ͣ�

/// �������͵�ת��ʧ�ܼ�⣺
/// ��Ϊͬһ���̵�һ���֡��������ĺ�ͨ�õģ�
/// ��Ϊһ����֧���̡��������쳣�ͻ��ں�����

/// ѡ���������ӳ��׳��쳣�Ͳ��׳�ת��ʧ�ܴ���

/// ͨ�����·�ʽ����ת��ʧ�ܣ�
/// �׳��쳣��
/// ���صĺ�ֵ��
/// ���õĺ󱸺�����

/// ֧�ֱ�׼�㷨��

/// Boost.Convert �����������ɣ�

/// boost::convert()�ӿڣ�
/// ����չ�Ŀɲ��ת�������ϡ�

/// boost::convert()�ӿ�

/// �������ṩ��ȷ��ĳЩһ�µ���Ϊ��
/// ͳһ��Ϊ����ת�������ṩһ��һ�µĽӿڡ�

/// �ɲ��ת�����ļ��϶����� boost::convert() API ���棬���ұ����Ϊ����չ����ʱ����չ��Ŀǰ�ṩ����ת������

/// ����boost::lexical_cast,
/// ���� printf/scanf��
/// ��strtol������
/// ����std::stringstream�ģ�
/// ����boost::spirit��

/// ��Щת�����ṩ���µĺ���Ϥ�Ĺ��ܣ�����ʾ����ν����еĶ���ת�����ߺϲ���Boost.Convert����С�
/// ���磬����std::stream��ת�������ñ�׼std::streams���ܲ��ṩ��

/// �ַ��������ͺ����͵��ַ�����ת����
/// ��ʽ֧�֣����� std::ios �ľ��ȡ���������д/Сд����ѧ�ȣ���
/// ֧�ֲ�ͬ�����Ի�����
/// char �� wchar_t ֧�֡�

/// ���´�����ʾ��������������ı�ʮ�����Ʊ�ʾ��ʽ��ת��������-1�������Щ�޷�ת���ģ�

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
      ���´�����ʾ��������������ı�ʮ�����Ʊ�ʾ��ʽ��ת��������-1�������Щ�޷�ת���ģ�
   */

    std::array<char const*, 3> strs = { { " 5", "0XF", "not an int" } };
    std::vector<int> ints;
    boost::cnv::cstream cnv;

    // Configure converter to read hexadecimal, skip (leading) white spaces.
    // ��ת��������Ϊ��ȡʮ�����ƣ�������ǰ�����ո�
    cnv(std::hex)(std::skipws);

    std::transform(strs.begin(), strs.end(), std::back_inserter(ints), boost::cnv::apply<int>(std::cref(cnv)).value_or(-1));

    BOOST_TEST(ints.size() == 3);  // Number of values processed.�������ֵ����������
    BOOST_TEST(ints[0] == 5);  // " 5"
    BOOST_TEST(ints[1] == 15);  // "0XF"
    BOOST_TEST(ints[2] == -1);  // "not an int"

    //]
}