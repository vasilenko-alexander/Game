#include "../include/engine.hpp"
#include "../include/SDL.h"
#include "../include/engine_constants.hpp"
#include <algorithm>
#include <exception>
#include <iostream>
#include <sstream>

namespace ge
{
    class Engine : public IEngine
    {
        SDL_Window* window = nullptr;
        std::map<std::string, uint> defined_options;

    public:
        Engine();
        std::string init_engine(std::string init_options) override;
        bool read_event(bool& run_loop) override;
        void uninit_engine() override;

    private:
        uint parseWndOptions(std::string init_options);
        void init_def_options();
    };

    Engine::Engine()
    {
        init_def_options();
    }

    void Engine::init_def_options()
    {
        defined_options[ge::timer]          = SDL_INIT_TIMER;
        defined_options[ge::audio]          = SDL_INIT_AUDIO;
        defined_options[ge::video]          = SDL_INIT_VIDEO;
        defined_options[ge::gamecontroller] = SDL_INIT_GAMECONTROLLER;
        defined_options[ge::events]         = SDL_INIT_EVENTS;
        defined_options[ge::joystick]       = SDL_INIT_JOYSTICK;
        defined_options[ge::haptic]         = SDL_INIT_HAPTIC;
        defined_options[ge::everything]     = SDL_INIT_EVERYTHING;
    }

    uint Engine::parseWndOptions(std::string init_options)
    {
        uint flags = 0;
        try
        {

            char delim = ' ';
            std::istringstream strStream(init_options);
            std::string option;
            while (std::getline(strStream, option, delim))
            {
                std::transform(
                    option.begin(), option.end(), option.begin(), ::tolower);
                flags |= defined_options.at(option);
            }

            return flags;
        }
        catch (const std::out_of_range& ex)
        {
            std::cerr << "Some err is occurred: " << ex.what() << std::endl;
            return flags;
        }
    }

    std::string Engine::init_engine(std::string init_options)
    {
        SDL_version linked_lib = {0, 0, 0};
        SDL_GetVersion(&linked_lib);
        if (SDL_COMPILEDVERSION != SDL_VERSIONNUM(linked_lib.major,
                                                  linked_lib.minor,
                                                  linked_lib.patch))
        {
            std::cerr << "SDL compiled and linked libs are mismatch"
                      << std::endl;
        }

        std::stringstream errMsg;
        uint wndFlags      = parseWndOptions(init_options);
        const int init_res = SDL_Init(wndFlags);

        if (init_res != 0)
        {
            errMsg << "SDL_INIT failed " << SDL_GetError() << std::endl;
            return errMsg.str();
        }

        const char* title_wnd = "SDL window";

        window = SDL_CreateWindow(title_wnd,
                                  SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED,
                                  640,
                                  480,
                                  ::SDL_WINDOW_OPENGL);

        if (window == nullptr)
        {
            errMsg << "Window creating failed " << SDL_GetError() << std::endl;
            return errMsg.str();
        }
        return errMsg.str();
    }

    bool Engine::read_event(bool& run_loop)
    {
        bool hasEvent = false;
        std::string event_msg;
        SDL_Event event;

        if (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    event_msg = "quit_event";
                    run_loop  = false;
                    break;
                case SDL_KEYUP:
                    event_msg = "key_release_event";
                    break;
                case SDL_KEYDOWN:
                    event_msg = "key_pressed_event";
                    break;
                default:
                    break;
            }
        }
        if (!event_msg.empty())
            std::cout << event_msg << std::endl;

        return hasEvent;
    }

    void Engine::uninit_engine()
    {
        if (window != nullptr)
        {
            SDL_DestroyWindow(window);
            window = nullptr;
        }
        SDL_Quit();
    }

    IEngine* getInstance()
    {
        static Engine engine_inst;
        return &engine_inst;
    }

    IEngine::~IEngine()
    {
    }
}
