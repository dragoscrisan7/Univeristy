#include <QApplication>
#include <QPushButton>
#include "Service.h"
#include "ParticipantRepo.h"
#include "QuestionRepo.h"
#include "presenter.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QuestionRepo repo{};
    ParticipantRepo participantRepo{};

    Service service{repo};
    Participant big_boy{"presenter", 0};
    std::vector<Participant> all_part = participantRepo.get_participants();
    for( int i=0; i<all_part.size(); i++)
    {
        Presenter* presenter = new Presenter{service, all_part[i]};
        presenter->show();
    }
    Presenter main{service, big_boy};
    main.show();
    return QApplication::exec();
}
