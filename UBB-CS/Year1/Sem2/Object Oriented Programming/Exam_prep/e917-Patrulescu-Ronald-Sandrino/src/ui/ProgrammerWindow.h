//
// Created by kamui on 08.06.2022.
//

#ifndef E917_PATRULESCU_RONALD_SANDRINO_PROGRAMMERWINDOW_H
#define E917_PATRULESCU_RONALD_SANDRINO_PROGRAMMERWINDOW_H


#include <QWidget>
#include <QListWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include "../domain/observer.h"
#include "../repository/CodeRepository.h"

class ProgrammerWindow: public QWidget, public Observer {
    Q_OBJECT
private:
    CodeRepository& codeRepository;
    Programmer programmer;
public:
    ProgrammerWindow(QWidget *parent, CodeRepository &codeRepository, const Programmer &programmer);

private:
    QListWidget* sourceFilesList;

    QLabel* revisedLabel;
    QLabel* toRevisedLabel;

    QLineEdit* newSourceFileNameLineEdit;
    QPushButton* addSourceFileButton;

    QPushButton* reviseButton;

    void initializeUI();
    void connectSignalsAndSlots();

private slots:
    void handleAddSourceFileButton();
    void handleReviseButton();
    void handleListSelectionChanged();

public:
    void update() override; // TODO: can this be private?
private:
    void updateSourceFilesList();
    void updateLabels();
};


#endif //E917_PATRULESCU_RONALD_SANDRINO_PROGRAMMERWINDOW_H
