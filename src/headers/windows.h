
#ifndef WINDOWS_H
#define WINDOWS_H

namespace Windows
{
    class GUI
    {
    public:
        virtual int execute(int argc, char *argv[]) = 0;
    };
}

#endif //WINDOWS_H
