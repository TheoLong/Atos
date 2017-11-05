#include "statemachine.h"

void lori_state_machine(struct StateMachineParams * arg)
{
	static Lori_States state = INIT, prev = INIT, paused = INIT;
    if(arg->status == 2)
    {
        if(state != PAUSED)
        {
            if(state == SWEEP || state == BACK)
            {
                Left_Motor_PID(FORWARD, 0);
                Right_Motor_PID(FORWARD, 0);
            }
            paused = state;
            state = PAUSED;
        }
    }
	switch (state)
	{
        case PAUSED:
        {
            if(arg->status == 1)
            {
                
            }
        }
        case INIT:
        {
            
            if(arg->status == 1)
            {
                SetServo1PWM(150);
                state = SWEEP;
            }
//            state = SWEEP;
            break;
        }
		case STANDBY:
		{
			_state_machine_standby(&state, &prev, arg);
			break;
		}

		case TURN_RIGHT:
		{
			_state_machine_turnright(&state, &prev, arg);
			break;
		}

		case TARE:
		{
			_state_machine_tare(&state, &prev, arg);
			break;
		}

		case SWEEP:
		{
			_state_machine_sweep(&state, &prev, arg);
			break;
		}

		case BACK:
		{
			_state_machine_back(&state, &prev, arg);
			break;
		}

		case TURN_LEFT:
		{
			_state_machine_turnleft(&state, &prev, arg);
			break;
		}

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
        
        case FORWARDTARE:
        {
            _state_machine_forwardtare(&state, &prev, arg);
			break;
        }
		default:
		{
			prev = END;
			break;
		}
	}
}

void _state_machine_standby(Lori_States * state, Lori_States * prev, struct StateMachineParams * arg)
{
	if (*prev != STANDBY)
	{
		*prev = STANDBY;
		Left_Motor_Distance(FORWARD, 35, 500 * (arg->current_row+1));
		Right_Motor_Distance(FORWARD, 35, 500 * (arg->current_row+1));
	}
	if (Left_Is_Finish() && Right_Is_Finish())
	{
		arg->standby = true;
		*state = TURN_RIGHT;
        _state_machine_send_status(prev, state);
	}
}

void _state_machine_turnright(Lori_States * state, Lori_States * prev, struct StateMachineParams * arg)
{
	if (*prev != TURN_RIGHT)
	{
		*prev = TURN_RIGHT;
		Left_Motor_Distance(FORWARD, 35, 590);
		Right_Motor_Distance(BACKWARD, 35, 590);
	}
	if (Left_Is_Finish() && Right_Is_Finish())
	{
		if (arg->standby)
		{
			arg->standby = false;
			*state = TARE;
		}
		else
		{
			*state = DUMP;
		}
        _state_machine_send_status(prev, state);
	}
}

void _state_machine_tare(Lori_States * state, Lori_States * prev, struct StateMachineParams * arg)
{
    if(*prev != TARE)
    {
        *prev = TARE;
        arg->bumper = false;
    }
    Left_Motor_PID(BACKWARD, 40);
    Right_Motor_PID(BACKWARD, 40);
	if (arg->bumper)
	{
        vTaskDelay(200);
		*state = SWEEP;
        _state_machine_send_status(prev, state);
	}
}

void _state_machine_sweep(Lori_States * state, Lori_States * prev, struct StateMachineParams * arg)
{
	if (*prev != SWEEP)
	{
		*prev = SWEEP;
        Left_Motor_PID(FORWARD, 35);
        Right_Motor_PID(FORWARD, 35);
//        SetIRPID(FORWARD, 35, GetSideIR());
	}
    if (GetFrontIR() > 700)
    {
        *state = FORWARDTARE;
    }
}

void _state_machine_forwardtare(Lori_States * state, Lori_States * prev, struct StateMachineParams * arg)
{
    if (*prev != FORWARDTARE)
    {
        *prev = FORWARDTARE;
        SetServo1PWM(760);
        *state = BACK;
        arg->bumper = false;
        vTaskDelay(750);
    }
}

void _state_machine_back(Lori_States * state, Lori_States * prev, struct StateMachineParams * arg)
{
    if(*prev != BACK)
    {
        *prev = BACK;
        Left_Motor_PID(BACKWARD, 36);
        Right_Motor_PID(BACKWARD, 35);
//        SetIRPID(BACKWARD, 35, GetSideIR());
    }
	if (arg->bumper)
	{
        vTaskDelay(100);
//        StopIRPID();
		Left_Motor_Distance(FORWARD, 35, 425);
		Right_Motor_Distance(FORWARD, 35, 425);
		vTaskDelay((TickType_t) 500);
		arg->bumper = false;
		arg->dump = true;
		*state = TURN_LEFT;
        _state_machine_send_status(prev, state);
	}
}

void _state_machine_turnleft(Lori_States * state, Lori_States * prev, struct StateMachineParams * arg)
{
	if (*prev != TURN_LEFT)
	{
		*prev = TURN_LEFT;
		Left_Motor_Distance(BACKWARD, 35, 590);
		Right_Motor_Distance(FORWARD, 35, 590);
	}
	if (Left_Is_Finish() && Right_Is_Finish())
	{
		if (arg->dump)
		{
			arg->dump = false;
			*state = PREDUMP;
		}
		else
		{
//            SetIRPID(BACKWARD, 35, 0);
            Left_Motor_PID(BACKWARD, 40);
            Right_Motor_PID(BACKWARD, 40);
            vTaskDelay(400);
//            StopIRPID();
            Left_Motor_Distance(FORWARD, 35, 550);
            Right_Motor_Distance(FORWARD, 35, 550);
//            vTaskDelay(400);
			*state = STANDBY;
		}
        _state_machine_send_status(prev, state);
	}
}

void _state_machine_predump(Lori_States * state, Lori_States * prev, struct StateMachineParams * arg)
{
    if (*prev != PREDUMP)
    {
        *prev = PREDUMP;
//        SetIRPID(BACKWARD, 35, 0);
        Left_Motor_PID(BACKWARD, 40);
        Right_Motor_PID(BACKWARD, 40);
    }
	if (arg->bumper)
	{
        SetServo1PWM(150);
		vTaskDelay(100);
//        StopIRPID();
		Left_Motor_Distance(FORWARD, 35, 400);
		Right_Motor_Distance(FORWARD, 35, 400);
		vTaskDelay((TickType_t) 320);
		arg->bumper = false;
		*state = TURN_RIGHT;
        _state_machine_send_status(prev, state);
	}
}

void _state_machine_dump(Lori_States * state, Lori_States * prev, struct StateMachineParams * arg)
{
	if(*prev != DUMP)
    {
        *prev = DUMP;
        arg->bumper =false;
        Left_Motor_PID(BACKWARD, 40);
        Right_Motor_PID(BACKWARD, 40);
    }
	if (arg->bumper)
	{
        vTaskDelay(100);        
        Left_Motor_PID(FORWARD, 0);
		Right_Motor_PID(FORWARD, 0);
	}	
    if (arg->cipangoready && arg->bumper)
    {
        Left_Motor_PID(FORWARD, 0);
		Right_Motor_PID(FORWARD, 0);
        SetServo2PWM(800);
        vTaskDelay((TickType_t) 225);
        SetServo2PWM(35);
        vTaskDelay((TickType_t) 225);
        SetServo2PWM(0);
        Left_Motor_Distance(FORWARD, 35, 200);
        Right_Motor_Distance(FORWARD, 35, 200);
        vTaskDelay((TickType_t) 225);
        arg->bumper = false;
        arg->current_row++;
        arg->dump = false;
        arg->standby = false;
        *state = (arg->current_row >= 6) ? END : TURN_LEFT;
        _state_machine_send_status(prev, state);
    }
}


void _state_machine_send_status(Lori_States * prev, Lori_States * curr)
{
    struct JsonRequest jsr = {PIC_ID, 's', 0, 62, 0, *curr, *prev, 0, 0};
    SendOverWiFi(jsr);
}

void requeststatus(TimerHandle_t xTimer)
{
    struct JsonRequest jsr = {PIC_ID, 'r', 0, 60, 0, 0, 0, 0, 0};
    SendOverWiFi(jsr);
}