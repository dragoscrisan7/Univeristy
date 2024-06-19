#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_PlaylistGUI.h"

class PlaylistGUI : public QMainWindow{
    Q_OBJECT

public:
    PlaylistGUI(QWidget *parent = Q_NULLPTR);

private:
    Ui::PlaylistGUIClass ui;
};