#ifndef QUESTIONS_AND_ANSWERS_SERVICE_H
#define QUESTIONS_AND_ANSWERS_SERVICE_H
#include "Repository.h"
#include "Observer.h"
#include <algorithm>

class Service: public Subject {
private:
    Repository& repo;
public:
    Service(Repository &repo);

    int number_answers(int qid);
    void add_question(string text, string user_name);
    void add_answer(int qid, string text, string user_name);

    virtual ~Service();
    vector<Question> sort_questions();
    vector<Answer> answers_to_q(int qid);
    void change_votes(int aid, int votes);
};


#endif //QUESTIONS_AND_ANSWERS_SERVICE_H
