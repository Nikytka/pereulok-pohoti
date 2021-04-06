#include <cmath>
#include <future>
#include <iostream>
#include <random>
#include <thread>
#include <time.h>
#include <vector>

long long factorial(int x)
{
    if (x == 0)
        return 1;
    return x * factorial(x - 1);
}

int inside_check(float r, int n, int num_dots)
{
    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_real_distribution<float> distribution(-r, r);
    std::vector<float> coord(n);

    float dist = 0;
    int k = 0;

    for (int j = 0; j < num_dots; j++) {
        dist = 0;
        for (int i = 0; i < n; i++) {
            coord[i] = distribution(generator);
            //std::cout << coord[i] << " ";
            dist += coord[i] * coord[i];
        }
        dist = sqrt(dist);
        //std::cout << dist << std::endl;
        if (dist < r)
            k++;
    }
    return k;
}

float calc_real_vol(float r, int n)
{
    float real_volume;
    const double PI = acos(-1.0);

    if (n % 2 == 1)
        real_volume = (float)2 * factorial(n / 2) * pow(4 * PI, n / 2) / factorial(n) * pow(r, n);
    else
        real_volume = (float)pow(PI, n / 2) / factorial(n / 2) * pow(r, n);

    return real_volume;
}

int main()
{
    float r, volume;
    int n, k = 0, num_thread, num_dots;
    std::cin >> r >> n >> num_thread >> num_dots;

    std::vector<std::future<int>> futures;

    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < num_thread; i++)
        futures.push_back(std::async(inside_check, r, n, num_dots / num_thread));

    if (num_dots % num_thread != 0)
        futures.push_back(std::async(inside_check, r, n, num_dots % num_thread));

    for (int i = 0; i < futures.size(); i++)
        k += futures[i].get();

    volume = (float)k / num_dots * pow(2 * r, n);

    std::chrono::duration<double> diff = std::chrono::high_resolution_clock::now() - start;

    std::cout << "Number of dots inside: " << k << std::endl
              << "Number of all dots: " << num_thread * num_dots << std::endl
              << "Calculated volume: " << volume << std::endl
              << "Real volume: " << calc_real_vol(r, n) << std::endl
              << diff.count() << "s";
    return 0;
}
