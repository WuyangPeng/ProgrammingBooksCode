#include "ProductPersistenceTestCase.h"
#include "assembly.h"
#include "persistentAssembly.h"
#include "persistentObject.h"
#include "persistentProduct.h"
#include "product.h"
#include <strstream>

void ProductPersistenceTestCase::setUp()
{
}

void ProductPersistenceTestCase::testWriteProduct()
{
    std::ostrstream s;
    Product* p = new PersistentProduct("Cheerios");
    PersistentObject* po = dynamic_cast<PersistentObject*>(p);
    assert(po);
    po->write(s);
    char* writtenString = s.str();
    assert(strcmp("<PRODUCT><NAME>Cheerios</NAME></PRODUCT>", writtenString) == 0);
}

void ProductPersistenceTestCase::testWriteAssembly()
{
    std::ostrstream s;
    Assembly* a = new PersistentAssembly("Wheaties", "7734");
    PersistentObject* po = dynamic_cast<PersistentObject*>(a);
    assert(po);
    po->write(s);
    char* writtenString = s.str();
    assert(strcmp("<ASSEMBLY><NAME>Wheaties</NAME><ASSYCODE>7734</ASSYCODE></ASSEMBLY>", writtenString) == 0);
}

//------------------------------------------
template <class T>
TestCaller<T>* makeTestCaller(const char* name, void (T::*f)())
{
    return new TestCaller<T>(name, f);
}

Test* ProductPersistenceTestCase::suite()
{
    TestSuite* testSuite = new TestSuite("ProductPersistenceTestCase");
    testSuite->addTest(makeTestCaller("testWriteProduct", &ProductPersistenceTestCase::testWriteProduct));
    testSuite->addTest(makeTestCaller("testWriteAssembly", &ProductPersistenceTestCase::testWriteAssembly));

    return testSuite;
}
