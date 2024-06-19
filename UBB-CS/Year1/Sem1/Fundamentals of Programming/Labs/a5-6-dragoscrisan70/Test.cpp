#include "Test.h"
#include <cassert>
#include <iostream>
#include <cstring>

using namespace std;

void testDog()
{
    dog dog1("magician", "adrian", "www.adrian_magician.ro", 10);
    assert(dog1.get_name() == "adrian");
    assert(dog1.get_breed() == "magician");
    assert(dog1.get_photograph() == "www.adrian_magician.ro");
    assert(dog1.get_age() == 10);
    dog dog2("magician", "adrian", "www.adrian_magician.ro", 10);
    assert(dog1 == dog2);
    assert("Breed: magician | Name: adrian | Age: 10 | Photograph link: www.adrian_magician.ro" == dog1.toString());
}

void testDyn()
{
    auto* dyn = new DynamicVector<dog>;
    dog dog1("magician", "adrian", "www.adrian_magician.ro", 10);
    dog dog2("magician", "Toru", "www.toru_magician.ro", 10);
    dog dog3("magician1", "Dimi", "www.toru_magician.ro", 10);
    assert(dyn->getSize() == 0);
    dyn->add(dog1);
    dyn->add(dog2);
    assert(dyn->getSize() == 2);
    dyn->del(1);
    assert(dyn->getSize() == 1);
    dyn->add(dog3);
    assert((*dyn)[0].get_name() == "adrian");
    assert((*dyn)[1].get_breed() == "magician1");
    assert((*dyn)[1].get_photograph() == "www.toru_magician.ro");
    assert((*dyn)[1].get_age() == 10);
    dyn->update(1,dog2);
    assert((*dyn)[1].get_name() == "Toru");
    assert((*dyn)[1].get_breed() == "magician");
    try{
        cout<<(*dyn)[-10].toString();
    }
    catch(std::out_of_range& e){
        assert(!strcmp("index err",e.what()));
    }
    delete dyn;
}

void testRepo()
{
    DynamicVector<dog> dyn;
    auto repo = Repository(&dyn);
    dog dog1("magician", "adrian", "www.adrian_magician.ro", 10);
    dog dog2("magician", "Toru", "www.toru_magician.ro", 10);
    dog dog10("Corgi", "Jedi", "https://www.wowwow.ro/welsh-corgi-pembroke-caine/2332", 1);
    repo.addDog(dog1);
    assert(repo.getSize() == 1);
    repo.initialiseRepo();
    assert(repo.getSize() == 11);
    repo.addDog(dog2);
    assert((*repo.getAllRepo())[0].get_name() == "adrian");
    assert((*repo.getAllRepo())[10].get_name() == "Jedi");
    assert((*repo.getAllRepo())[10] == dog10);
    repo.deleteDog("Jedi");
    assert((*repo.getAllRepo())[10] == dog2);
    assert(repo.getSize() == 11);
    repo.updateDog("Toru", dog10);
    assert((*repo.getAllRepo())[10] == dog10);
    try{
        repo.deleteDog("araara");
    }
    catch (std::invalid_argument& e){
        assert(!strcmp("Dog not found", e.what()));
    }
    try{
        repo.updateDog("araara", dog10);
    }
    catch (std::invalid_argument& e){
        assert(!strcmp("Dog not found", e.what()));
    }
}
void testService()
{
    dog dog1("magician", "Adrian", "www.adrian_magician.ro", 10);
    DynamicVector<dog> dyn;
    auto repo = Repository(&dyn);
    auto srv = Service(&repo);
    srv.addDoggo("Adrian", "magician", "www.adrian_magician.ro", 10);
    assert((*repo.getAllRepo())[10].get_name() == "Adrian");
    srv.addDoggo("Toru", "magician", "www.toru_magician.ro", 10);
    assert(repo.getSize() == 12);
    assert((*repo.getAllRepo())[11].get_name() == "Toru");
    srv.delDoggo("Adrian");
    assert(repo.getSize() == 11);
    assert((*repo.getAllRepo())[10].get_name() == "Toru");
    srv.updateDoggo("Toru","Adrian", "magician", "www.adrian_magician.ro", 10);
    assert((*repo.getAllRepo())[10] == dog1);
    auto repo2 = srv.getRepo();
    assert((*repo2->getAllRepo())[10] == dog1);
    srv.delDoggo("Arcus");
    srv.updateDoggo("Arcus", "Adrian", "magician", "www.adrian_magician.ro", 10);
}
void testUserRepo()
{
    DynamicVector<dog> dyn;
    auto urepo = user_repo(&dyn);
    dog dog1("magician", "Adrian", "www.adrian_magician.ro", 10);
    urepo.addDog(dog1);
    assert(urepo.getSize() == 1);
    assert((*urepo.getAllAdopted())[0].get_name() == "Adrian");
}
void testUserService()
{
    DynamicVector<dog> udyn;
    auto urepo = user_repo(&udyn);
    DynamicVector<dog> dyn;
    auto repo = Repository(&dyn);
    auto srv = Service(&repo);
    auto usrv = UserService(&urepo, &repo);
    usrv.add_adopted_dog("a","a","www.a.com",10);
    auto * valid_dogs = new dog[2];
    srv.addDoggo("a","a","www.a.com",10);
    assert(usrv.get_all_filtered(valid_dogs,"b",11) == 0);
    assert(usrv.get_all_filtered(valid_dogs,"Corgi",11) == 1);
    auto repo2 = usrv.getRepo();
    assert((*repo2->getAllAdopted())[0].get_name() == "a");
}

void testAll()
{
    testDog();
    testDyn();
    testRepo();
    testService();
    testUserRepo();
    testUserService();
}
