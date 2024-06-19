#include <QApplication>
#include <QPushButton>
#include "Service.h"
#include "PRepository.h"
#include "Repository.h"
#include "presenter.h"
#include <iostream>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Repository repo{};
    ParticipantRepo participantRepo{};

    Service service{repo};
    Participant big_boy{"presenter", 0};
    std::vector<Participant> all_part = participantRepo.get_participants();
    for( int i=0; i<all_part.size(); i++)
    {
        Presenter* presenter = new Presenter{service, all_part[i]};
        presenter->show();
    }
    Presenter p{service, big_boy};
    p.show();
    return a.exec();
}
