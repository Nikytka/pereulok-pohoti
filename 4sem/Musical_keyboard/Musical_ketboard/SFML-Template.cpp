#include <SFML/Audio.hpp>
#include <Windows.h>
#include <iostream>
#include <vector>

bool IsKeyDown(int Key)
{
    return (GetKeyState(Key) & 0x8000) != 0;
}

int main()
{
    std::vector<double> freq = { 261.63, 277.18, 293.66, 311.13, 329.63, 349.23, 369.99, 392.00, 415.30, 440.00, 466.16, 493.88 };
    const int duration = 1000000;
    std::vector<std::vector<sf::Int16>> samples(12);
    std::vector<sf::SoundBuffer> buff(12);
    std::vector<sf::Sound> sound(12);

    for (int j = 0; j < 12; j++) {
        for (double i = 0; i < duration; i += 1)
            samples[j].push_back(25000 * sin(2 * 3.141592 * freq[j] * (i + 1) / 2 / 44100));
        buff[j].loadFromSamples(&samples[j][0], samples[j].size(), 2, 44100);
        sound[j].setBuffer(buff[j]);
    }
    while (true) {
        if (IsKeyDown(70) && (sound[0].getStatus() != sf::Sound::Playing))
            sound[0].play();
        else if (!IsKeyDown(70))
            sound[0].stop();
        if (IsKeyDown(84) && (sound[1].getStatus() != sf::Sound::Playing))
            sound[1].play();
        else if (!IsKeyDown(84))
            sound[1].stop();
        if (IsKeyDown(71) && (sound[2].getStatus() != sf::Sound::Playing))
            sound[2].play();
        else if (!IsKeyDown(71))
            sound[2].stop();
        if (IsKeyDown(89) && (sound[3].getStatus() != sf::Sound::Playing))
            sound[3].play();
        else if (!IsKeyDown(89))
            sound[3].stop();
        if (IsKeyDown(72) && (sound[4].getStatus() != sf::Sound::Playing))
            sound[4].play();
        else if (!IsKeyDown(72))
            sound[4].stop();
        if (IsKeyDown(74) && (sound[5].getStatus() != sf::Sound::Playing))
            sound[5].play();
        else if (!IsKeyDown(74))
            sound[5].stop();
        if (IsKeyDown(73) && (sound[6].getStatus() != sf::Sound::Playing))
            sound[6].play();
        else if (!IsKeyDown(73))
            sound[6].stop();
        if (IsKeyDown(75) && (sound[7].getStatus() != sf::Sound::Playing))
            sound[7].play();
        else if (!IsKeyDown(75))
            sound[7].stop();
        if (IsKeyDown(79) && (sound[8].getStatus() != sf::Sound::Playing))
            sound[8].play();
        else if (!IsKeyDown(79))
            sound[8].stop();
        if (IsKeyDown(76) && (sound[9].getStatus() != sf::Sound::Playing))
            sound[9].play();
        else if (!IsKeyDown(76))
            sound[9].stop();
        if (IsKeyDown(80) && (sound[10].getStatus() != sf::Sound::Playing))
            sound[10].play();
        else if (!IsKeyDown(80))
            sound[10].stop();
        if (IsKeyDown(186) && (sound[11].getStatus() != sf::Sound::Playing))
            sound[11].play();
        else if (!IsKeyDown(186))
            sound[11].stop();
    }
    system("PAUSE");
    return 0;
}
