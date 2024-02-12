#include "Test.h"
#include <assert.h>

void testAdd()
{
    DynamicVector<task> dyn;
    auto repo = Repository(&dyn);
    auto srv= Services(&repo);
    std::string desc = "ALA";
    assert(srv.add(desc, 10, 1) == 1);
    assert(srv.getRepo()->getSize() == 6);
    assert((*srv.getRepo()->getAllRepo())[5].getDescription() == "ALA");
}


void testAll()
{
    testAdd();
}