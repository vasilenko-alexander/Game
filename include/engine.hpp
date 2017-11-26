#pragma once

#include <cstdlib>
#include <map>
#include <string>

namespace ge
{
    class IEngine
    {
    public:
        virtual ~IEngine();
        /**
         * init_options you can find in engine_constants.hpp
         */
        virtual std::string init_engine(std::string init_options) = 0;
        virtual bool read_event(bool& run_loop)                   = 0;
        virtual void uninit_engine()                              = 0;
    };

    IEngine* getInstance();
}
