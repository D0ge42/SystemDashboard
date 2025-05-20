#include "infos.hpp"
#include <cmath>
#include <stdlib.h>
#include "worker.hpp"
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <ctime>

static std::vector <std::string> split(std::string str);
static void fill_cpu_info_vector(std::vector<std::string> vec, std::vector <int> *cpu_stats);
static void calculate_cpu_usage(std::vector <int> *cpu_stats,  double *perc, int *total_usage, int *total_idle, int *prev_total, int *prev_idle);

/*
 * Function used to retrieve and calculate cpu usage from /proc/stat file.
 * It is also responsible for emitting the dataReady signal which will then
 * trigger the updateGraph slot.
 * Workflow of the function is as follow:
 *
 * First we retrieve infos from /proc/stat and put them into a vector of strings.
 * Second. We take different snapshots of the cpu_usage.
 * Then we fill our time and usage vectors.
 * Finally emit the signal dataReady, which will call upgradeGraph slot.
*/

void Worker::retrieveCPUusage()
{
    time_t timestamp,start;
    std::vector<std::string> vec;
    std::vector<int> nums;
    QVector <double> usage,time_passed;
    int total_usage,total_idle,prev_usage,prev_idle = 0;
    double perc;
    time(&start);
    for (int i = 0; i < 1000; i++)
    {
        time(&timestamp);
        fill_cpu_info_vector(vec,&nums);
        calculate_cpu_usage(&nums,&perc,&total_usage,&total_idle,&prev_usage,&prev_idle);
        usage.push_back(perc);
        time_passed.push_back(difftime(timestamp,start));
        emit dataReady(time_passed, usage,perc);
        std::cout << perc << "%" << std::endl;
        nums.clear();
        vec.clear();
        sleep(1);
    }
}

/*
 * @Brief: Function used to fill a vector with the CPU info we need.
 * @Params: vec = info vector of strings
 * cpu_stats = values representing time the cpu spent doing something.
*/

static void fill_cpu_info_vector(std::vector<std::string> info, std::vector <int> *cpu_stats)
{
    std::string stats;

    std::ifstream infile("/proc/stat");
    std::getline(infile,stats);
    info = split(stats);
    for (int i = 1; i < info.size(); i++)
        cpu_stats->push_back(std::stoi(info[i]));
}

/*
 * @Brief: function responsible for calculating the percentage of cpu used.
 * It is calculated by getting the total usage and the idle time.
 * Then we retrieve the difference between the current and previous snapshot.
 * This way we can easily find the percentage in real time.
 * @Params:
 * Cpu_stats: previously created vector
 * double perc -> pointer to perc. A pointer is used so it can be updated directly into the function.
 * pointers to total_usage and idle, and prev_usage and idle.
*/

static void calculate_cpu_usage(std::vector <int> *cpu_stats, double *perc, int *total_usage, int *total_idle, int *prev_usage, int *prev_idle)
{
    *total_usage = calc_total_usage(*cpu_stats);
    *total_idle = calc_total_idle(*cpu_stats);
    *perc = (1 -  (1.0 * *total_idle - *prev_idle) / (*total_usage - *prev_usage)) * 100;
    *prev_idle = *total_idle;
    *prev_usage = *total_usage;
}

/*
 * @Brief: function used to split a string each time we meet a space.
 * Each string is saved into a vector of strings, effectively spltting the main string.
 * @Params:
 * std::string str -> the string to split.
 * @Return -> vector of splitted strings.
*/

static std::vector<std::string> split(std::string str)
{
    int start,end = 0;
    char del = ' ';
    std::vector<std::string> vec;

    while((start = str.find_first_not_of(del,end)) != std::string::npos)
    {
        end = str.find(del,start);
        vec.push_back(str.substr(start,end - start));
    }
    return vec;
}

/* Constructors */

Worker::Worker()
{
}

/* Destructors */

Worker::~Worker()
{
}
