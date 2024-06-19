#include "UI.h"
#include "Test.h"

int main()
{
    run_tests();

    IngredientRepo* repo = createIngredientRepo();
    Service* srv = createService(repo);
    Ui* ui = createUI(srv);


    ///TODO add some inputs to begin with in the repo

    run(ui);

    destroyUI(ui);

    return 0;
}