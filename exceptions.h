
#ifndef WET1_EXEPTIONS_H
#define WET1_EXEPTIONS_H

#include <stdexcept>

namespace Wet1{

    class Wet1Exeption {};

    namespace AVL {
        class AVLexeption : public  Wet1Exeption{};
        class IllegalArgument : public AVLexeption{};
        class KeyAlreadyExist : public AVLexeption{};
        class KeyDoesntExist : public AVLexeption{};
    }
}

#endif //WET1_EXEPTIONS_H
