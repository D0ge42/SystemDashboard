#include "infos.hpp"
#include <cmath>
#include <stdlib.h>

/* Numbers that can be found inside /proc/stat file.
 * [0]user: normal processes executing in user mode
 * [1]nice: niced processes executing in user mode
 * [2]system: processes executing in kernel mode
 * [3]idle: twiddling thumbs
 * [4]iowait: waiting for I/O to complete
 * [5]irq: servicing interrupts
 * [6]softirq: servicing softirqs
*/

int calc_total_usage(std::vector<int> num)
{
    return num[0] + num[1] + num[2] + num[3] + num[4] + num[5] + num[6];
}

int calc_total_idle(std::vector<int> num)
{
    return num[3];
}

