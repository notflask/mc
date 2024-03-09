#include "mc.hpp"
#include <cxxopts.hpp>

int main(int argc, char* argv[])
{
    cxxopts::Options options("mc", "mc - microphone controller. utility, which will help to control your microphnones");
    
    options.add_options()
        ("m,mute", "mute the microphone")
        ("u,unmute", "unmute the microphone")
        ("d,device", "device index for editing", cxxopts::value<int>())
        ("list", "show all devices with their numbers");

    auto result = options.parse(argc, argv);

    if (result.count("list"))
    {
        mc::show_device_list();
        return 0;
    }

    if (!result.count("device"))
    {
        std::cerr << "device index not provided\nuse --list to see available devices" << std::endl;
        return 1;
    }

    auto choice = result["device"].as<int>();

    if (choice < 0 || choice >= waveInGetNumDevs())
    {
        std::cerr << "invalid device index" << std::endl;
        return 1;
    }

    bool mute = false;

    if (result.count("mute"))
    {
        mute = true;
    }
    else if (result.count("unmute"))
    {
        mute = false;
    }
    else
    {
        std::cerr << "please provide either --mute or --unmute" << std::endl;
        return 1;
    }

    mc::toggle_microphone_mute(choice, mute);

	return 0;
}
