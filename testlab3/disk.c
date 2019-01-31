
#include "randsim.h"

double seek_time(int current_track, int new_track)
{   
    int track_delta = 0;
    double time = 0.0;

    track_delta = current_track - new_track;
    if (track_delta < 0)
        track_delta *= -1;

    /* resettle region */
    time = 0.003;
    if (track_delta > 10)
    {
        /* accel region */
        time += (track_delta - 10) * 0.00001;
    }
    if (track_delta > 60)
    {
        /* linear region */
        time += (track_delta - 60) * 0.00000015;
    }
    return time;
}

int request_track()
{
    double g;
    int track;

    while(1)
    {
        g = randsim_gauss();
        if (g > 0 && g < 1000)
            break;
    }
    track = (int)g;
    return track;
}
