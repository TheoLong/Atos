#include "public.h"

 void Wait_Time(int time)
{
     Timing_Wait(time);
    while(!GetTimingFlag())
    {
    }
}