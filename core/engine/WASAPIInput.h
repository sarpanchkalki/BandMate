#ifndef WASAPI_INPUT_H
#define WASAPI_INPUT_H

#include <functional>

class WASAPIInput {
public:
    bool start(const std::function<void(const float*, int)>& callback);
};

#endif
