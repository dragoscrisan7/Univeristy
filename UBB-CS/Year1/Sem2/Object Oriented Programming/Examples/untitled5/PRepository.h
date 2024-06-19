#pragma once
#include "Participant.h"
#include <vector>

class ParticipantRepo {
private:
    std::vector<Participant> arr;
    std::string file_name = "C:/Users/Oana/CLionProjects/practice_for_exam/part.txt";
    void read_from_file();
    void save_to_file();
public:
    ParticipantRepo();
    ~ParticipantRepo();

    std::vector<Participant>& get_participants();


};
