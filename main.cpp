
/*
    Imgus version 20170122
    Copyright (c) 2016-2017 Artur Szajdecki
*/

#include "src/headers/main.h"

int main(int argc, char *argv[])
{
    Operations::SETUP_OPERATIONS<>();
    MAIN_WINDOW_TYPE gui;
    return gui.execute(argc, argv);
    return 0;
}
