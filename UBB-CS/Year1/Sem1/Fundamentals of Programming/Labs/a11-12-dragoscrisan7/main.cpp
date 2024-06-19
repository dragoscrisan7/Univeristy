#include "Ui.h"

int main(){
    testAll();


    auto repo = Repository("Dogs.csv");
    auto srv = Service(&repo);
    auto usrv = UserService(&repo);
    auto user_interface = ui(&srv, &usrv);
    user_interface.run();

    return 0;
}
/*
Bond,German Shepherd,1,https://www.wowwow.ro/ciobanesc-german-caine/2145
Murray,Golden Retriever,3,https://www.wowwow.ro/golden-retriever-caine/2151
Baby,Poodle,2,https://www.wowwow.ro/pudel-standard-%28caniche%29-caine/2163
Ice,Husky,7,https://www.wowwow.ro/husky-caine/2152
Bear,Samoyed,0,https://www.wowwow.ro/samoyed-caine/2298
Hudson,Husky,10,https://www.wowwow.ro/husky-caine/2152
Dash,Akita Inu,3,https://www.wowwow.ro/akita-inu-caine/2131
Geo,Akita Inu,6,https://www.wowwow.ro/akita-inu-caine/2131
Jedi,Corgi,1,https://www.wowwow.ro/welsh-corgi-pembroke-caine/2332
*/
