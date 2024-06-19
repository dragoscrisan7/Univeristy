#include "UI.h"
#include "Test.h"

using namespace std;

int main()
{
    //system("color f4");
    testAll();

    DynamicVector<dog> dyn;
    DynamicVector<dog> adyn;
    auto repo = Repository(&dyn);
    auto srv = Service(&repo);
    auto urepo = user_repo(&adyn);
    auto usrv = UserService(&urepo, &repo);
    auto user_interface= ui(&srv, &usrv);
    user_interface.run();
    return 0;
}

