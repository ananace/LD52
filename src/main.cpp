#include "Application.hpp"
#include <SFML/GpuPreference.hpp>

SFML_DEFINE_DISCRETE_GPU_PREFERENCE

int main(int argc, char** argv)
{
    Application app;

    app.init();
    app.run();

    return 0;
}
