#include "BMI.h"
#include "BP.h"
#include <iostream>
#include "UI.h"

using namespace std;

int main()
{
	Person p("Marcel");
	p.addAllAnalyses("BMI.txt", "");
	UI ui(p);

	ui.start();

	/*MedicalAanalysis* bmi = new BMI{"2022.04.13", 22};
	MedicalAanalysis* bp = new BP{ "2022.04.13", 65, 100 };

	cout << bmi->toString() << endl;
	cout << bmi->isResultOK() << endl;
	cout << bp->toString() << endl;
	cout << bp->isResultOK() << endl;

	delete bmi;
	delete bp;*/

	return 0;
}