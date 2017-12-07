#include "statemachine.h"
#include "Control.h"

extern QueueHandle_t receive_q;

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
                state = TARE;
            }
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
            StopIRPID();
            Left_Motor_PID(FORWARD, 0);
            Right_Motor_PID(FORWARD, 0);
			break;
		}
	}
    struct JsonResponse js;
    BaseType_t ret = xQueueReceive(receive_q, &js, (TickType_t) 0);
    if(ret == pdTRUE)
    {
        if(js.tsk == 61 && js.arg0 == 1)
            arg->bumper = true;
        else if(js.tsk == 60)
            arg->status = js.arg0;
        else if(js.tsk == 79)
            arg->cipangoready = (js.arg0 == 0) ? true : false;
    }
}

void _state_machine_standby(Lori_States * state, Lori_States * prev, struct StateMachineParams * arg)
{
	if (*prev != STANDBY)
	{
		*prev = STANDBY;
		Left_Motor_Distance(FORWARD, 35, 375 * (arg->current_row+1));
		Right_Motor_Distance(FORWARD, 35, 375 * (arg->current_row+1));
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
		Left_Motor_Distance(FORWARD, 35, 540);
		Right_Motor_Distance(BACKWARD, 35, 540);
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
        Left_Motor_PID(BACKWARD, 40);
        Right_Motor_PID(BACKWARD, 35);
    }
	if (arg->bumper)
	{
        vTaskDelay(200);
		*state = SWEEP;
        Left_Motor_PID(FORWARD, 0);
        Right_Motor_PID(FORWARD, 0);
        _state_machine_send_status(prev, state);
	}
}

void _state_machine_sweep(Lori_States * state, Lori_States * prev, struct StateMachineParams * arg)
{
	if (*prev != SWEEP)
	{
        vTaskDelay(125);
        PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_D, 6, 1);
		*prev = SWEEP;
        SetIRPID(FORWARD, 35, (arg->current_row + 1) * 50);
	}
    if (GetFrontIR() > 750)
    {
//        StopIRPID();
//        Left_Motor_PID(FORWARD, 0);
//        Right_Motor_PID(FORWARD, 0);
        *state = FORWARDTARE;
    }
}

void _state_machine_forwardtare(Lori_States * state, Lori_States * prev, struct StateMachineParams * arg)
{
    if (*prev != FORWARDTARE)
    {
        *prev = FORWARDTARE;
//        int pwm = 300;
//        for(pwm = 300; pwm <=680; pwm += 10)
//        {
//            SetServo1PWM(pwm);
//            vTaskDelay(15);
//        }
        vTaskDelay(400);
        StopIRPID();
        Left_Motor_PID(FORWARD, 0);
        Right_Motor_PID(FORWARD, 0);
        *state = BACK;
        arg->bumper = false;
//        SetServo1PWM(780);
//        Left_Motor_PID(FORWARD, 0);
//        Right_Motor_PID(FORWARD, 0);
//        PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_D, 6, 0);
//        vTaskDelay(125);
    }
}

void _state_machine_back(Lori_States * state, Lori_States * prev, struct StateMachineParams * arg)
{
    static bool isdown = true;
    if(*prev != BACK)
    {
        isdown = true;
        *prev = BACK;
        SetIRPID(BACKWARD, 35, (arg->current_row + 1) * 50);
    }
    if (GetFrontIR() < 680 && isdown)
    {
        isdown = false;
        int pwm = 300;
        for(pwm = 300; pwm <=680; pwm += 10)
        {
            SetServo1PWM(pwm);
            vTaskDelay(15);
        }        
        SetServo1PWM(780);
        PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_D, 6, 0);        
    }
	if (arg->bumper)
	{
        vTaskDelay(100);
        StopIRPID();
        Left_Motor_PID(FORWARD, 0);
        Right_Motor_PID(FORWARD, 0);
		Left_Motor_Distance(FORWARD, 35, 200);
		Right_Motor_Distance(FORWARD, 35, 200);
        while(!Left_Is_Finish() || !Right_Is_Finish());
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
		Left_Motor_Distance(BACKWARD, 35, 550);
		Right_Motor_Distance(FORWARD, 35, 550);
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
            Left_Motor_PID(BACKWARD, 41);
            Right_Motor_PID(BACKWARD, 40);
            vTaskDelay(500);
            while(!Left_Is_Finish() || !Right_Is_Finish());
			*state = STANDBY;
		}
        _state_machine_send_status(prev, state);
	}
}

void _state_machine_predump(Lori_States * state, Lori_States * prev, struct StateMachineParams * arg)
{
    if (*prev != PREDUMP)
    {
        arg->bumper = false;
        *prev = PREDUMP;
        Left_Motor_PID(BACKWARD, 32);
        Right_Motor_PID(BACKWARD, 31);
    }
	if (arg->bumper)
	{
		vTaskDelay(100);
		Left_Motor_Distance(FORWARD, 35, 200);
		Right_Motor_Distance(FORWARD, 35, 200);
		while(!Left_Is_Finish() || !Right_Is_Finish());
		arg->bumper = false;
		*state = TURN_RIGHT;
        _state_machine_send_status(prev, state);
	}
}

void _state_machine_dump(Lori_States * state, Lori_States * prev, struct StateMachineParams * arg)
{
    static bool f = true;
	if(*prev != DUMP)
    {
        *prev = DUMP;
        arg->bumper =false;
        Left_Motor_PID(BACKWARD, 42);
        Right_Motor_PID(BACKWARD, 40);
        f = true;
    }
	if (arg->bumper && f)
	{
        f = false;
        vTaskDelay(100);        
        Left_Motor_PID(FORWARD, 0);
		Right_Motor_PID(FORWARD, 0);
	}	
    if (arg->cipangoready && arg->bumper)
    {
//        arg->cipangoready = false;
        Left_Motor_Distance(FORWARD,35,150);
        Right_Motor_Distance(FORWARD, 35, 150);
        while(!Left_Is_Finish() || !Right_Is_Finish());
        Left_Motor_PID(FORWARD, 0);
		Right_Motor_PID(FORWARD, 0);
        SetServo1PWM(150);
        vTaskDelay((TickType_t) 200);
        SetServo2PWM(800);
        vTaskDelay((TickType_t) 315);
        SetServo2PWM(35);
        vTaskDelay((TickType_t) 225);
        SetServo2PWM(0);
        Left_Motor_Distance(FORWARD, 35, 200);
        Right_Motor_Distance(FORWARD, 35, 200);
        while(!Left_Is_Finish() || !Right_Is_Finish());
        arg->bumper = false;
        arg->current_row++;
        arg->dump = false;
        arg->standby = false;
        *state = (arg->current_row >= 4) ? END : TURN_LEFT;
        struct JsonRequest jsr = {PIC_ID, 's', 0, 79, 0, 1, 0, 0, 0};
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
    jsr.tgt = 1;
    jsr.tsk = 79;
    SendOverWiFi(jsr);
}