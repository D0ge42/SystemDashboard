#include "infos.hpp"
#include <string.h>
#include <iostream>
#include <unistd.h>

/*
 * @Brief: function responsible for retrieving CPU info
 * from /proc/cpuinfo file.
 * Those info are then store inside the CPU class
 * and they can be used to provide more info to the user.
*/

void  CPUinfo::gatherInfo()
{
  FILE *cpuinfo = fopen("/proc/cpuinfo", "rb");
    if (cpuinfo == NULL)
        exit(EXIT_FAILURE);
    char *arg = 0;
    std::vector<std::string> infos;
    size_t size = 0;
    while(getline(&arg,&size,cpuinfo)!= -1)
        infos.push_back(arg);
    fillStruct(infos);
    free(arg);
    fclose(cpuinfo);
}

/*
 * @Brief: function responsible for filtering and retrieving
 * info from /proc/cpuinfo.
 * Info are stored inside the CPU class.
*/
void CPUinfo::fillStruct(std::vector <std::string> vec)
{
    for (int i = 0; i < vec.size(); i++)
    {
        size_t to_compare = vec[i].find(':',0);
        if (to_compare == std::string::npos)
            continue;
        std::string identifier = vec[i].substr(0,to_compare);
        if (identifier.compare(0,strlen("processor"),"processor") == 0)
            this->processors = atoi((vec[i].substr(to_compare + 2,vec[i].size() - to_compare).c_str()));
        if (identifier.compare(0,strlen("vendor_id"),"vendor_id") == 0)
            this->vendor_id = vec[i].substr(to_compare + 2,vec[i].size() - to_compare);
        if (identifier.compare(0,strlen("cpu family"),"cpu family") == 0)
            this->cpu_family = atoi((vec[i].substr(to_compare + 2,vec[i].size() - to_compare).c_str()));
        if (identifier.compare(0,strlen("model name"),"model name") == 0)
            this->model_name = vec[i].substr(to_compare + 2,vec[i].size() - to_compare - 4);
        if (identifier.compare(0,strlen("cpu MHz"),"cpu MHz") == 0)
            this->cpu_mhz = atof((vec[i].substr(to_compare + 2,vec[i].size() - to_compare).c_str()));
    }
}

/* Constructors and Destructors */

CPUinfo::CPUinfo(Ui::MainWindow *ui, QObject *parent):QObject(parent),ui(ui)
{
}

CPUinfo::CPUinfo()
{

}

CPUinfo::~CPUinfo()
{
}

/* getters and setters */

double CPUinfo::getUsage()
{
    return this->cpu_usage;
}

void CPUinfo::setUi(Ui::MainWindow *ptr)
{
    this->ui = ptr;
}

std::string CPUinfo::getModelName()
{
    return this->model_name;
}
