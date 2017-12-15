#include "statemachine.h"

void cipango_state(struct StateMachineParams * arg)
{
	static Cipango_States state = INIT, prev = INIT;
    
    
    
//    struct JsonRequest jsr = {PIC_ID, 's', 0, 74, 0, state, 0, 0, 0};
//    SendOverWiFi(jsr);
    
	switch (state)
	{
        case INIT:
        {            
            prev = INIT;
            state = WAIT_FOR_START;
            
            struct JsonRequest jsr = {0, 's', 0, 79, 0, -1, -1, 0, 1};
            SendOverWiFi(jsr);   
            
            _state_machine_send_status(&prev, &state);
            break;
        }
        
        //pre-start
        case WAIT_FOR_START:
        {
            _state_machine_wait_for_start(&state, &prev, arg);
            break;
        }
        
        //lori
        case TRAVEL_TO_LORI:
        {
            _state_machine_travel_to_lori(&state, &prev, arg);
            break;
        }        
        case ARRIVE_AT_LORI:
        {
            _state_machine_arrive_at_lori(&state, &prev, arg);
            break;
        }        
        case WAIT_FOR_LORI:
        {
            _state_machine_wait_for_lori(&state, &prev, arg);
            break;
        }
        
        //crane
        case TRAVEL_TO_CRANE:
        {
            _state_machine_travel_to_crane(&state, &prev, arg);
            break;
        }        
        case ARRIVE_AT_CRANE:
        {
            _state_machine_arrive_at_crane(&state, &prev, arg);
            break;
        }        
        case WAIT_FOR_CRANE:
        {
            _state_machine_wait_for_crane(&state, &prev, arg);
            break;
        }
        
        //stop
        case STOP:
        {
            _state_machine_stop(&state, &prev, arg);
            break;
        }
	}
}

void _state_machine_wait_for_start(Cipango_States * state, Cipango_States * prev, struct StateMachineParams * arg)
{    
    if (*prev != WAIT_FOR_START)
    {
        Pause();        
        *prev = WAIT_FOR_START;
    }
    
    if (arg->status == 21)
    {
        arg->status = 0;
        
        if (arg->cipango_lori_ready)
        {
            arg->cipango_lori_ready = false;
            
            *state = ARRIVE_AT_LORI;
            *prev = WAIT_FOR_START;
            
            struct JsonRequest jsr = {0, 's', 0, 79, 0, -1, 1, 0, 3};
            SendOverWiFi(jsr);
            
            _state_machine_send_status(prev, state);
            return;
        }
        else
        {
            *prev = WAIT_FOR_START;
            *state = TRAVEL_TO_LORI;
            
            struct JsonRequest jsr = {0, 's', 0, 79, 0, -1, 0, 0, 2};
            SendOverWiFi(jsr);
            
            _state_machine_send_status(prev, state);
            return;
        }
    }
    else if (arg->status == 99)
    {
        arg->status = 0;
        
        *prev = WAIT_FOR_START;
        *state = STOP;
        _state_machine_send_status(prev, state);
        return;
    }
}

void _state_machine_travel_to_lori(Cipango_States * state, Cipango_States * prev, struct StateMachineParams * arg)
{    
    if (*prev != TRAVEL_TO_LORI)
    {
        Forward(35);
        *prev = TRAVEL_TO_LORI;
    }

    if (arg->status == 99)
    {
        arg->status = 0;
        
        *prev = TRAVEL_TO_LORI;
        *state = STOP;
        _state_machine_send_status(prev, state);
        return;
    }
    else if (arg->status == 50)
    {
        arg->status = 0;
        
        *prev = TRAVEL_TO_LORI;
        *state = WAIT_FOR_START;
        _state_machine_send_status(prev, state);
        return;
    }
    
    if (arg->lori_bumper)
	{
        arg->lori_bumper = false;	
        
        *prev = TRAVEL_TO_LORI;
        *state = ARRIVE_AT_LORI;
        
        struct JsonRequest jsr = {0, 's', 0, 79, 0, -1, 1, 0, 3};
        SendOverWiFi(jsr);   
        
        _state_machine_send_status(prev, state);

        return;
    }
}

void _state_machine_arrive_at_lori(Cipango_States * state, Cipango_States * prev, struct StateMachineParams * arg)
{
    if (*prev != ARRIVE_AT_LORI)
    {
        Pause();
        *prev = ARRIVE_AT_LORI;
    }
    
    if (arg->status == 99)
    {
        arg->status = 0;
        
        *prev = ARRIVE_AT_LORI;
        *state = STOP;
        _state_machine_send_status(prev, state);
        return;
    }
    else if (arg->status == 50)
    {
        arg->status = 0;
        
        *prev = ARRIVE_AT_LORI;
        *state = WAIT_FOR_START;
        _state_machine_send_status(prev, state);
        return;
    }

    if(arg->cipango_lori_ready)        
    {
        arg->cipango_lori_ready = false;
        
        *prev = ARRIVE_AT_LORI;
        *state = WAIT_FOR_LORI;
        
        struct JsonRequest jsr = {0, 's', 0, 79, 0, -1, 1, 0, 4};
        SendOverWiFi(jsr); 

        _state_machine_send_status(prev, state);
        return;
        
    }
}

void _state_machine_wait_for_lori(Cipango_States * state, Cipango_States * prev, struct StateMachineParams * arg)
{        
    if (*prev != WAIT_FOR_LORI)
    {
        *prev = WAIT_FOR_LORI;
    }
        
    if (arg->status == 99)
    {
        arg->status == 0;
        
        *prev = WAIT_FOR_LORI;
        *state = STOP;
        _state_machine_send_status(prev, state);
    }
    else if (arg->status == 50)
    {
        arg->status == 0;
        
        *prev = WAIT_FOR_LORI;
        *state = WAIT_FOR_START;
        _state_machine_send_status(prev, state);
        return;
    }
    
    if (arg->lori_done)
    {
        arg->lori_done = false;
        
        *prev = WAIT_FOR_LORI;
        *state = TRAVEL_TO_CRANE;
        
        struct JsonRequest jsr = {0, 's', 0, 79, 0, -1, 0, 0, 5};
        SendOverWiFi(jsr); 

        _state_machine_send_status(prev, state);
    }
    
}

void _state_machine_travel_to_crane(Cipango_States * state, Cipango_States * prev, struct StateMachineParams * arg)
{
    if (*prev != TRAVEL_TO_CRANE)
    {
        Backward(35);
        *prev = TRAVEL_TO_CRANE;
    }

    if (arg->status == 99)
    {
        arg->status == 0;
        
        *prev = TRAVEL_TO_CRANE;
        *state = STOP;
        _state_machine_send_status(prev, state);
        return;
    }
    else if (arg->status == 50)
    {
        arg->status == 0;
                
        *prev = TRAVEL_TO_CRANE;
        *state = WAIT_FOR_START;
        _state_machine_send_status(prev, state);
        return;
    }
    
    if (arg->crane_bumper)
	{
        arg->crane_bumper = false;	
        
        *prev = TRAVEL_TO_CRANE;
        *state = ARRIVE_AT_CRANE;
        
        struct JsonRequest jsr = {0, 's', 0, 79, 0, -1, 0, 1, 6};
        SendOverWiFi(jsr);      
        
        _state_machine_send_status(prev, state);
        return;
    }
}

void _state_machine_arrive_at_crane(Cipango_States * state, Cipango_States * prev, struct StateMachineParams * arg)
{
    if (*prev != ARRIVE_AT_CRANE)
    {
        Pause();
        *prev = ARRIVE_AT_CRANE;
    }
    
    if (arg->status == 99)
    {
        arg->status = 0;
        
        *prev = ARRIVE_AT_CRANE;
        *state = STOP;
        _state_machine_send_status(prev, state);
        return;
    }
    else if (arg->status == 50)
    {
        arg->status = 0;
        
        *prev = ARRIVE_AT_CRANE;
        *state = WAIT_FOR_START;
        _state_machine_send_status(prev, state);
        return;
    }
    
    if (arg->cipango_crane_ready)
    {
        arg->cipango_crane_ready = false;
        
        *prev = ARRIVE_AT_CRANE;
        *state = WAIT_FOR_CRANE;
        
        struct JsonRequest jsr = {0, 's', 0, 79, 0, -1, 0, 1, 7};
        SendOverWiFi(jsr);   

        _state_machine_send_status(prev, state);
        return;
    }
    
}

void _state_machine_wait_for_crane(Cipango_States * state, Cipango_States * prev, struct StateMachineParams * arg)
{
    if (*prev != WAIT_FOR_CRANE)
    {
        *prev = WAIT_FOR_CRANE;
    }
        
    if (arg->status == 99)
    {
        arg->status = 0;
        
        *prev = WAIT_FOR_CRANE;
        *state = STOP;
        _state_machine_send_status(prev, state);
        return;
    }
    else if (arg->status == 50)
    {
        arg->status = 0;
        
        *prev = WAIT_FOR_CRANE;
        *state = WAIT_FOR_START;
        _state_machine_send_status(prev, state);
        return;
    }
    
    if (arg->crane_done)
    {
        arg->crane_done = false;
        
        *prev = WAIT_FOR_CRANE;
        *state = TRAVEL_TO_LORI;
        
        struct JsonRequest jsr = {0, 's', 0, 79, 0, -1, 0, 0, 2};
        SendOverWiFi(jsr);  

        _state_machine_send_status(prev, state);
    }
    
}

void _state_machine_stop(Cipango_States * state, Cipango_States * prev, struct StateMachineParams * arg)
{
    if (*prev != STOP)
    {
        Pause();
        _state_machine_send_status(prev, state);
        *prev = STOP;        
    }
    
    struct JsonRequest jsr = {0, 's', 0, 255, 0, 256, 256, 256, 256};
    SendOverWiFi(jsr);   
}

void _state_machine_send_status(Cipango_States * prev, Cipango_States * curr)
{
    struct JsonRequest jsr = {PIC_ID, 's', 0, 73, 0, *curr, *prev, 0, 0};
    SendOverWiFi(jsr);
}



void requeststatus(TimerHandle_t xTimer)
{
    struct JsonRequest jsr = {PIC_ID, 'r', 0, 79, 0, 0, 0, 0, 0};
    SendOverWiFi(jsr);
}