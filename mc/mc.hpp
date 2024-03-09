#pragma once
#define NOMINMAX
#include <windows.h>
#include <mmsystem.h>
#include <iostream>
#include <string>
#include <audioclient.h>
#include <endpointvolume.h>
#include <mmdeviceapi.h>

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "mmdevapi.lib")

namespace mc {

    void toggle_microphone_mute(int deviceIndex, bool mute)
    {
        IMMDeviceEnumerator* pEnumerator = nullptr;
        IMMDevice* pDevice = nullptr;
        IAudioEndpointVolume* pEndpointVolume = nullptr;

        CoInitialize(nullptr);

        if (CoCreateInstance(__uuidof(MMDeviceEnumerator), nullptr, CLSCTX_ALL, __uuidof(IMMDeviceEnumerator), (void**)&pEnumerator) != S_OK)
        {
            std::cerr << "error creating device enumerator" << std::endl;
            CoUninitialize();
            return;
        }

        if (pEnumerator->GetDefaultAudioEndpoint(eCapture, eConsole, &pDevice) != S_OK)
        {
            std::cerr << "error getting default audio endpoint" << std::endl;
            pEnumerator->Release();
            CoUninitialize();
            return;
        }

        if (pDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_ALL, nullptr, (void**)&pEndpointVolume) != S_OK)
        {
            std::cerr << "error activating endpoint volume interface" << std::endl;
            pDevice->Release();
            pEnumerator->Release();
            CoUninitialize();
            return;
        }

        float minVolume, maxVolume;
        pEndpointVolume->GetVolumeRange(&minVolume, &maxVolume, 0);

        if (mute)
        {
            pEndpointVolume->SetMasterVolumeLevelScalar(0.0f, nullptr);
            std::cout << "microphone muted" << std::endl;
        }
        else
        {
            pEndpointVolume->SetMasterVolumeLevelScalar(1.0f, nullptr);
            std::cout << "microphone unmuted" << std::endl;
        }

        pEndpointVolume->Release();
        pDevice->Release();
        pEnumerator->Release();

        CoUninitialize();
    }

    void show_device_list()
    {
        auto count = waveInGetNumDevs();

        if (count == 0)
        {
            std::cout << "no audio input devices found" << '\n';
            return;
        }

        std::cout << "available audio input devices: " << '\n';

        for (auto i = 0; i < count; ++i)
        {
            WAVEINCAPS dInfo;
            MMRESULT mmResult = waveInGetDevCaps(i, &dInfo, sizeof(dInfo));

            if (mmResult == MMSYSERR_NOERROR)
            {
                std::wstring wName(dInfo.szPname);
                std::string name(wName.begin(), wName.end());

                std::cout << i << ". " << name << ")" << '\n';
            }
            else
            {
                std::cerr << "error getting device information for device " << i << std::endl;
            }
        }
    }
}