#include "statemachine.h"

void lori_state_machine(struct StateMachineParams * arg)
{
	static Lori_States state = INIT, prev = INIT, pause = INIT;
    if(arg->status == 2)
    {
        prev = INIT;
        pause = state;
        state = PAUSED;
    }
	switch (state)
	{
        case INIT:
        {
//            if(arg->status == 1)
//            {
                state = BACK;
            //}
//            state = SWEEP;
            break;
        }
        case PAUSED:
        {
            if(arg->status == 3)
            {
                state = pause;
            }
            break;
        }
//		case STANDBY:
//		{
//			_state_machine_standby(&state, &prev, arg);
//			break;
//		}
//
//		case TURN_RIGHT:
//		{
//			_state_machine_turnright(&state, &prev, arg);
//			break;
//		}
//
//		case TARE:
//		{
//			_state_machine_tare(&state, &prev, arg);
//			break;
//		}
//
//		case SWEEP:
//		{
//			_state_machine_sweep(&state, &prev, arg);
//			break;
//		}

		case BACK:
		{
			_state_machine_back(&state, &prev, arg);
			break;
		}

//		case TURN_LEFT:
//		{
//			_state_machine_turnleft(&state, &prev, arg);
//			break;
//		}

		case PREDUMP:
		{
			_state_machine_predump(&state, &prev, arg);
			break;
		}

		case DUMP:
		{
			_state_machine_dump(&state, &prev, arg);
			break;
		}
        case POSTDUMP:
		{
			_state_machine_postdump(&state, &prev, arg);
			break;
		}
		default:
		{
			prev = END;
			break;
		}
	}
}
//
//void _state_machine_standby(Lori_States * state, Lori_States * prev, struct StateMachineParams * arg)
//{
//	if (*prev != STANDBY)
//	{
//		*prev = STANDBY;
//		Left_Motor_Distance(FORWARD, 35, 435 * arg->current_row);
//		Right_Motor_Distance(FORWARD, 35, 435 * arg->current_row);
//	}
//	if (Left_Is_Finish() && Right_Is_Finish())
//	{
//        
//		arg->standby = true;
//		*state = TURN_RIGHT;
//        _state_machine_send_status(prev, state);
//	}
//}
//
//void _state_machine_turnright(Lori_States * state, Lori_States * prev, struct StateMachineParams * arg)
//{
//	if (*prev != TURN_RIGHT)
//	{
//		*prev = TURN_RIGHT;
//		Left_Motor_Distance(FORWARD, 35, 540);
//		Right_Motor_Distance(BACKWARD, 35, 540);
//	}
//	if (Left_Is_Finish() && Right_Is_Finish())
//	{
//		if (arg->standby)
//		{
//			arg->standby = false;
//			*state = TARE;
//		}
//		else
//		{
//			*state = DUMP;
//		}
//        _state_machine_send_status(prev, state);
//	}
//}
//
//void _state_machine_tare(Lori_States * state, Lori_States * prev, struct StateMachineParams * arg)
//{
//    if(*prev != TARE)
//    {
//        *prev = TARE;
//        arg->bumper = false;
//    }
//    Left_Motor_PID(BACKWARD, 35);
//    Right_Motor_PID(BACKWARD, 35);
//	if (arg->bumper)
//	{
//        vTaskDelay(200);
//		*state = SWEEP;
//        _state_machine_send_status(prev, state);
//	}
//}
//
//void _state_machine_sweep(Lori_States * state, Lori_States * prev, struct StateMachineParams * arg)
//{
//	if (*prev != SWEEP)
//	{
//		*prev = SWEEP;
//		Left_Motor_Distance(FORWARD, 35, 6600);
//		Right_Motor_Distance(FORWARD, 35, 6600);
//	}
//	if (Left_Is_Finish() && Right_Is_Finish())
//	{
//        arg->bumper = false;
//		*state = BACK;
//        _state_machine_send_status(prev, state);
//	}
//}

//void _state_machine_turnleft(Lori_States * state, Lori_States * prev, struct StateMachineParams * arg)
//{
//	if (*prev != TURN_LEFT)
//	{
//		*prev = TURN_LEFT;
//		Left_Motor_Distance(BACKWARD, 35, 540);
//		Right_Motor_Distance(FORWARD, 35, 540);
//	}
//	if (Left_Is_Finish() && Right_Is_Finish())
//	{
//		if (arg->dump)
//		{
//			arg->dump = false;
//			*state = PREDUMP;
//		}
//		else
//		{
//            Left_Motor_PID(BACKWARD, 35);
//            Right_Motor_PID(BACKWARD, 35);
//            vTaskDelay(400);
//            Left_Motor_Distance(FORWARD, 35, 550);
//            Right_Motor_Distance(FORWARD, 35, 550);
//            vTaskDelay(400);
//			*state = STANDBY;
//		}
//        _state_machine_send_status(prev, state);
//	}
//}

void _state_machine_back(Lori_States * state, Lori_States * prev, struct StateMachineParams * arg)
{
	*prev = BACK;
    Left_Motor_PID(BACKWARD, 35);
    Right_Motor_PID(BACKWARD, 35);
	if (arg->bumper)
	{
        vTaskDelay(100);
//		Left_Motor_Distance(FORWARD, 35, 425);
//		Right_Motor_Distance(FORWARD, 35, 425);
//		vTaskDelay((TickType_t) 335);
           
		arg->bumper = false;
		//arg->dump = true;
        
        struct JsonRequest jsr = {0, 's', 0, 79, 0, 1, -1, -1, -1};
        SendOverWiFi(jsr);
		
	}
    
    
    
    if (arg->loriready)
    {
        arg->loriready = false;
        *state = PREDUMP;
        _state_machine_send_status(prev, state);
    }
}


void _state_machine_predump(Lori_States * state, Lori_States * prev, struct StateMachineParams * arg)
{
	if (*prev != PREDUMP)
    {
        Left_Motor_PID(BACKWARD, 0);
        Right_Motor_PID(BACKWARD, 0);
        *prev = PREDUMP;
    }
    
	if (arg->cipangoready)
	{
        arg->cipangoready = false;
		*state = DUMP;
        
        _state_machine_send_status(prev, state);
	}
}

void _state_machine_dump(Lori_States * state, Lori_States * prev, struct StateMachineParams * arg)
{
	if (*prev != DUMP)
    {
        *prev = DUMP;
        SetServo2PWM(800);
        vTaskDelay((TickType_t) 225);
        SetServo2PWM(35);
        vTaskDelay((TickType_t) 225);
        SetServo2PWM(0);
        //Left_Motor_Distance(FORWARD, 35, 200);
        //Right_Motor_Distance(FORWARD, 35, 200);
        //vTaskDelay((TickType_t) 225);
        //arg->cipangoready = false;

        struct JsonRequest jsr = {0, 's', 0, 79, 0, 0, 0, -1, -1};
        SendOverWiFi(jsr);

        arg->bumper = false;
        arg->current_row++;
        arg->dump = false;
        arg->standby = false;
        *state = POSTDUMP;
        _state_machine_send_status(prev, state);
    }
    
    

//    Left_Motor_PID(FORWARD, 0);
//    Right_Motor_PID(FORWARD, 0);
    
    
    
}

void _state_machine_postdump(Lori_States * state, Lori_States * prev, struct StateMachineParams * arg)
{
    if (*prev != POSTDUMP)
    {
        *prev = POSTDUMP;
    }
    if (!arg->postdump)
    {
        struct JsonRequest jsr = {0, 's', 0, 79, 0, 0, 0, -1, -1};
        SendOverWiFi(jsr);
    }
}


void _state_machine_send_status(Lori_States * prev, Lori_States * curr)
{
    struct JsonRequest jsr = {PIC_ID, 's', 0, 63, 0, *curr, *prev, 0, 0};
    SendOverWiFi(jsr);
}

void requeststatus(TimerHandle_t xTimer)
{
    struct JsonRequest jsr = {PIC_ID, 'r', 0, 79, 0, 0, 0, 0, 0};
    SendOverWiFi(jsr);
}