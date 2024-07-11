//
// Created by kamui on 08.06.2022.
//

#include <QVBoxLayout>
#include <QFormLayout>
#include <QMessageBox>
#include <sstream>
#include "ProgrammerWindow.h"

ProgrammerWindow::ProgrammerWindow(QWidget *parent, CodeRepository &codeRepository, const Programmer &programmer)
        : QWidget(parent), codeRepository(codeRepository),
          programmer(programmer) {
    codeRepository.add(this); // subscribe to the subject
    initializeUI();
    connectSignalsAndSlots();
}

void ProgrammerWindow::initializeUI() {
    setWindowTitle(programmer.getName().c_str());
    auto mainLayout = new QVBoxLayout(this);

    // set up source files list widget
    sourceFilesList = new QListWidget(this);
    mainLayout->addWidget(sourceFilesList);

    // set up labels
    revisedLabel = new QLabel(this);
    mainLayout->addWidget(revisedLabel);
    toRevisedLabel = new QLabel(this);
    mainLayout->addWidget(toRevisedLabel);

    // set up add source file form
    auto addSourceFileForm = new QWidget(this);
    mainLayout->addWidget(addSourceFileForm);
    auto addSourceFileFormLayout = new QFormLayout(addSourceFileForm);

    // set up source file name line edit/input
    auto newSourceFileNameLabel = new QLabel("Source file &name:", addSourceFileForm);
    newSourceFileNameLineEdit = new QLineEdit(addSourceFileForm);
    newSourceFileNameLabel->setBuddy(newSourceFileNameLineEdit);
    addSourceFileFormLayout->addRow(newSourceFileNameLabel, newSourceFileNameLineEdit);

    // set up add new source file button
    addSourceFileButton = new QPushButton("&Add source file", this);
    mainLayout->addWidget(addSourceFileButton);

    // set up revise button
    reviseButton = new QPushButton("&Revise", this);
    mainLayout->addWidget(reviseButton);
    reviseButton->setDisabled(true);

    update();
}

void ProgrammerWindow::connectSignalsAndSlots() {
    QObject::connect(addSourceFileButton, &QPushButton::clicked, this, &ProgrammerWindow::handleAddSourceFileButton);
    QObject::connect(reviseButton, &QPushButton::clicked, this, &ProgrammerWindow::handleReviseButton);
    QObject::connect(sourceFilesList, &QListWidget::itemSelectionChanged, this, &ProgrammerWindow::handleListSelectionChanged);
}

void ProgrammerWindow::update() {
    updateSourceFilesList();
    updateLabels();
}

void ProgrammerWindow::updateSourceFilesList() {
    auto sourceFiles = codeRepository.getSortedSourceFiles();

    sourceFilesList->clear();
//    sourceFilesList->addItem("name,status,creator,reviewer");
    for (const auto &sourceFile: sourceFiles) {
        stringstream ss;
        ss << sourceFile;
        auto text = ss.str();
        auto item = new QListWidgetItem(text.c_str(), sourceFilesList);

        // add bold font to not revised source files
        if (sourceFile.isNotRevised()) {
            auto currentFont = item->font();
            item->setFont(QFont(currentFont.family(), currentFont.pointSize(), QFont::Bold));
        }
        sourceFilesList->addItem(item);
//        sourceFilesList->addItem(ss.str().c_str());
    }
}

void ProgrammerWindow::updateLabels() {
    revisedLabel->setText(("Revised: " + to_string(programmer.getRevised())).c_str());
    toRevisedLabel->setText(("To revise: " + to_string(programmer.getToRevise())).c_str());
}

void showMessageBox(const QString &title, const QString &text) {
    auto messageBox = QMessageBox(QMessageBox::Information, title, text, QMessageBox::Ok, nullptr);
    messageBox.exec();
}

void ProgrammerWindow::handleAddSourceFileButton() {
    try {
        auto name = newSourceFileNameLineEdit->text().toStdString();
        codeRepository.addSourceFile(name, programmer);
    }
    catch (std::exception& e) {
        showMessageBox("failed", e.what());
//        auto failureMessageBox = QMessageBox(QMessageBox::Information, "failed", e.what(), QMessageBox::Ok, this);
//        failureMessageBox.exec();
    }
}



void ProgrammerWindow::handleReviseButton() {
    try {
        auto sourceFile = codeRepository.findSortedSourceFileByIndex(sourceFilesList->currentRow());

        codeRepository.reviseSourceFile(sourceFile.getName(), programmer);

        // TODO: green background for the revised file (connect this, somehow, to updateList())
        //     IDEA: in codesRepository a field: unordered_set<string> namesOfNewRevisedFileNames which is updated in the revise method
        //          and, in ProgramWindow.updateList(), if the name of the SourceFile to add the list is contained in that set
        //                  then add a green background to that item

//        if (programmer.getRevised() >= programmer.getToRevise()) {
        if (programmer.getToRevise() == 0) {
            showMessageBox("Congratulations!", "You revised all the files!");
        }
    }
    catch (std::exception& e) { showMessageBox("failed", e.what()); }
}

void ProgrammerWindow::handleListSelectionChanged() {
    auto row = sourceFilesList->currentRow();
    auto sortedSourceFiles = codeRepository.getSortedSourceFiles();

//    if (row < 0 or row >= sortedSourceFiles.size()) {
    if (not codeRepository.isIndexValid(row)) {
        reviseButton->setDisabled(true);
        return;
    }

    auto sourceFile = sortedSourceFiles[row];
    auto shouldEnableReviseButton = sourceFile.isNotRevised() and programmer.getName() != sourceFile.getCreator();

    reviseButton->setEnabled(shouldEnableReviseButton);
}
