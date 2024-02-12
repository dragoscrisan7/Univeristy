#include "Ui.h"
#include "Test.h"

using namespace std;

int main(){
    testAll();

    DynamicVector<task> dyn;
    auto repo = Repository(&dyn);
    auto srv = Services(&repo);
    auto user_interface = ui(&srv);
    user_interface.run();
    return 0;
}