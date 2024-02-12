#include "Problem.h"

void Zeitdauer::filter(int mod, std::vector<Zeitdauer> durations) {
    durations.erase(std::remove_if(durations.begin(), durations.end(), [&mod](Zeitdauer x){
        return x.Minuten%mod == 0 || x.Stunden%mod == 0;
    }));
}
