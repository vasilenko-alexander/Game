#include "../include/engine.hpp"
#include "../include/engine_constants.hpp"
#include <iostream>

int main(int /*argn*/, char* /*args*/ [])
{
    ge::IEngine* gameEngine = ge::getInstance();
    std::string errMsg      = gameEngine->init_engine(ge::everything);

    if (!errMsg.empty())
    {
        std::cerr << errMsg << std::endl;
        return EXIT_FAILURE;
    }

    bool run_loop = true;
    while (run_loop)
    {
        while (gameEngine->read_event(run_loop))
            ;
    }
    gameEngine->uninit_engine();
    return EXIT_SUCCESS;
}
