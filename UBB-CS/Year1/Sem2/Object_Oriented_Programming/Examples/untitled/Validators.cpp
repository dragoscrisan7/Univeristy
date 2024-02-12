#include <algorithm>
#include <utility>
#include "Validators.h"
#include <cassert>
#include <iostream>

using namespace std;

void testDog()
{
    dog dog1("adrian", "magician", "https://www.wowwow.ro/bulldog-francez-caine/2199", 10);
    assert(dog1.get_name() == "adrian");
    assert(dog1.get_breed() == "magician");
    assert(dog1.get_photograph() == "https://www.wowwow.ro/bulldog-francez-caine/2199");
    assert(dog1.get_age() == 10);
    dog dog2("Adrian", "Magician", "https://www.wowwow.ro/bulldog-francez-caine/2199", 10);
    dog1 = dog2;
    assert(dog1.get_name() == "Adrian");
    assert(dog1.get_breed() == "Magician");
}
void testRepo(){
    ///Repository repo2;
    std::string filename="test.csv";
    auto repo = Repository(filename);
    dog dog1("Adrian", "Magician", "https://www.wowwow.ro/bulldog-francez-caine/2199", 10);
    repo.addDog(dog1);
    dog dog2("Yoda", "Husky", "https://www.wowwow.ro/husky-caine/2152", 5);
    repo.addDog(dog2);
    dog dog3("Perciles", "Golden Retriever", "https://www.wowwow.ro/golden-retriever-caine/2151", 3);
    repo.addDog(dog3);
    dog dog11("adrian", "magician", "https://www.wowwow.ro/bulldog-francez-caine/2199", 10);
    repo.modDog(dog1.get_name(), dog1.get_breed(), dog11);
    assert(repo.getDog()[0].get_name() == "adrian");
    assert(repo.getDog()[0].toString() == "Breed: magician | Name: adrian | Age: 10 | Photograph link: https://www.wowwow.ro/bulldog-francez-caine/2199");
    repo.delDog(dog11.get_name(),dog11.get_breed());
    repo.delDog(dog2.get_name(),dog2.get_breed());
    repo.delDog(dog3.get_name(),dog3.get_breed());
    assert(repo.getSize() == 0);
}
void testService(){
    dog dog1("Adrian", "magician", "www.adrian_magician.ro", 10);
    auto repo = Repository("test.csv");
    auto srv = Service(&repo);
    srv.addDoggo("Adrian", "magician", "www.adrian_magician.ro", 10);
    assert(repo.getDog()[0].get_name() == "Adrian");
    srv.addDoggo("Toru", "magician", "www.toru_magician.ro", 10);
    assert(srv.getRepo()->getSize() == 2);
    srv.updateDoggo("Toru","magician","Arcus", "magician", "www.adrian_magician.ro", 10);
    assert(repo.getDog()[1].get_name() == "Arcus");
    srv.delDoggo("Arcus", "magician");
    srv.delDoggo("Adrian", "magician");
    assert(repo.getSize() == 0);
}
void testUserRepo(){
    vector<dog> dogs;
    std::string usefile = R"(C:\Users\Dragos\OneDrive\Facultate\GitHub\a8-9-dragoscrisan7\AdoptedList.csv)";
    auto * urepo = new csvfile{dogs,usefile};
    dog dog1("Adrian", "magician", "www.adrian_magician.ro", 10);
    urepo->addDog(dog1);
    assert(urepo->getSize() == 1);
    assert(urepo->getDog()[0].get_name() == "Adrian");
}
void testUserService(){
    vector<dog> dogs;
    auto repo = Repository("test.csv");
    auto usrv = UserService(&repo);
    usrv.repoType(1);
    dog dog1("Adrian", "magician", "www.adrian_magician.ro", 10);
    repo.addDog(dog1);
    usrv.add_adopted_dog("Adrian", "magician", "www.adrian_magician.ro", 10);
    assert(usrv.getRepo()->getSize() == 1);
    assert(usrv.getRepo()->getDog()[0].get_name() == "Adrian");
    dog dog2("Yoda", "Husky", "https://www.wowwow.ro/husky-caine/2152", 5);
    repo.addDog(dog2);
    usrv.add_adopted_dog("Yoda", "Husky", "https://www.wowwow.ro/husky-caine/2152", 5);
    vector<dog> valid_dogs;
    dog dog3("Ani", "Magician", "www.adrian_magician.ro", 10);
    repo.addDog(dog3);
    dog dog4("Adi", "magician", "www.adrian_magician.ro", 10);
    repo.addDog(dog4);
    auto filtered = usrv.get_all_filtered(valid_dogs,"magician",11);
    assert(filtered == 1);
    repo.delDog("Ani", "Magician");
    repo.delDog("Adi", "magician");
}
void testAll()
{
    testDog();
    testRepo();
    testService();
    testUserRepo();

    testUserService();
}


Validation_exception::Validation_exception(std::string message1): message{std::move(message1)}
{
}

std::string Validation_exception::getMessage() const{
    return this->message;
}


void dogVali::validate(const dog &d1) {
    std::string error;
    if(d1.get_name().size() < 1)
        error += "Name is too short\n";
    if(d1.get_breed().size() < 1)
        error += "breed is too short\n";
    if(std::any_of(d1.get_breed().begin(), d1.get_breed().end(), ::isdigit) || std::any_of(d1.get_name().begin(), d1.get_name().end(), ::isdigit))
        error += "breed and name cant have numbers in them\n";
    if(d1.get_age() < 0)
        error += "age cant be negative\n";
    if(d1.get_photograph().find("www") == std::string::npos)
        error += "photograph link must have www inside it\n";
    if(d1.get_photograph().find(".com") == std::string::npos && d1.get_photograph().find(".ro") == std::string::npos)
        error += "photograph link must contain .com or .ro in it\n";
    if(!error.empty())
        throw Validation_exception(error);
}

void repoVali::validateAdd(const Repository &repo, const dog &d1) {
    std::vector<dog> v = repo.getDog();
    auto pos = std::find(v.begin(), v.end(), d1);
    std::string error;
    if(pos != v.end())
        error += "dog already exists\n";
    if(!error.empty())
        throw Validation_exception(error);
}

void repoVali::validateDelete(const Repository &repo, const dog &d1) {
    std::vector<dog> v = repo.getDog();
    auto pos = std::find(v.begin(), v.end(), d1);
    std::string error;
    if(pos == v.end())
        error += "dog doesnt exist\n";
    if(!error.empty())
        throw Validation_exception(error);
}

void repoVali::validateMod(const Repository &repo, const dog &d1) {
    std::vector<dog> v = repo.getDog();
    auto pos = std::find(v.begin(), v.end(), d1);
    std::string error;
    if(pos == v.end())
        error += "dog doesnt exist\n";
    if(!error.empty())
        throw Validation_exception(error);
}

