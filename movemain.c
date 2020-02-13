#define USR_SPOT_X 16	// user spot define
#define USR_SPOT_Y 16
#define RANGE 0.8		// adc range

// header include
#include <stdio.h>
#include <signal.h>
#include <rc/adc.h>
#include <rc/encoder_eqep.h>
#include <getopt.h>
#include <rc/motor.h>
#include <rc/time.h>

// for save spots
struct Spot
{
        int x;
        int y;
};

// for save goal information
struct Goal_info
{
        int x;
        int y;
        int spin;       
};

double duty[3];	// save adc value

int cal_token(void);
int re_cal_token(int token, int channel);      
struct Goal_info cal_goal(int token, int channel);
struct Spot now_spot(int token);
void Drive_go(struct Spot start, struct Goal_info goal);
//int Drive_back(struct Spot start, struct Goal_info goal);       
void encoder_check_left();   
void encoder_check_right();     
void encoder_check_forward();  
//void encoder_check_backward();  

int main()
{
	int token;  // declare to find it's spot
	int freq_hz = RC_MOTOR_DEFAULT_PWM_FREQ;       // motors frequency
	int channel;    // select channel
	struct Goal_info goal;
	struct Spot start;      

	// rc function init
	if(rc_adc_init())       
	{
		fprintf(stderr,"ERROR: failed to run rc_init_adc()\n");
		return -1;
	}

	if(rc_encoder_eqep_init())      
	{
		fprintf(stderr,"ERROR: failed to run rc_encoder_init\n");
		return -1;
	}

	if(rc_motor_init_freq(freq_hz)) return -1;      

	printf("Please wait\n");     

	token = cal_token();   // calculate token
	printf("token = %d\n", token);  
	rc_adc_cleanup();  // after calculate adc finish

	start = now_spot(token);       // calculate robot's now spot

	printf("\n채널 번호 입력(1=2.1, 2=3.1, 3=5.1) : ");
	scanf("%d", &channel);	// select channel

	token = re_cal_token(token, channel);  // useless token delete
	goal = cal_goal(token, channel);        // calculate goal information


	// drive by each token and goal information
	if(token == 1)
		Drive_go(start ,goal);  
	else if(token == 2)
	{
		Drive_go(start ,goal);  
	}
	else if(token == 3)
	{
		Drive_go(start ,goal); 
	}
	else if(token == 4)
	{
		Drive_go(start ,goal);  
	}
	else if(token == 5)
	{
		Drive_go(start ,goal);  
	}
	else if(token == 6)
	{
		Drive_go(start ,goal); 
	}
	// if token deleted finish
	else
	{
		rc_encoder_eqep_cleanup();
		rc_motor_cleanup();
		return 0;
	}
	return 0;
} // main close

// cal_token by robot's adc value
int cal_token(void)
{
	int token;

	if(rc_adc_read_volt(2)>RANGE &&  rc_adc_read_volt(3)>RANGE)             
		token = 1;     
	else if(rc_adc_read_volt(1)>RANGE && rc_adc_read_volt(2)>RANGE && rc_adc_read_volt(3)>RANGE)
		token = 2;      
	else if(rc_adc_read_volt(1)>RANGE && rc_adc_read_volt(2)>RANGE)
		token = 3;     
	else if(rc_adc_read_volt(0)>RANGE && rc_adc_read_volt(3)>RANGE)
		token = 4;    
	else if(rc_adc_read_volt(0)>RANGE && rc_adc_read_volt(1)>RANGE && rc_adc_read_volt(3)>RANGE)
		token = 5;     
	else if(rc_adc_read_volt(0)>RANGE && rc_adc_read_volt(1)>RANGE)
		token = 6;  
	else;

	return token;
}

// for delete useless token at each channel
int re_cal_token(int token, int channel)
{
	if(channel==1 && token>3)       
		token = 0;
	else if(channel == 2 && token>4)        
		token = 0;
	else if(channel == 3)  
		token = token;

	return token;
}

// calculate robot's now spot
struct Spot now_spot(int token)
{
	struct Spot start;
	
	if(token == 1)
	{
		start.x = 10;
		start.y = 7;
	}
	else if(token == 2)
	{
		start.x = 7;
		start.y = 7;
	}
	else if(token == 3)
	{
		start.x = 4;
		start.y = 7;
	}
	else if(token == 4)
	{
		start.x = 10;
		start.y = 4;
	}
	else if(token == 5)
	{
		start.x = 7;
		start.y = 4;
	}
	else if(token == 6)
	{
		start.x = 4;
		start.y = 4;
	}
	else;

	return start;
}

// calculate token's goal information
struct Goal_info cal_goal(int token, int channel)
{
	struct Goal_info goal;

	// 2.1channel's goal cal
	if(channel == 1)
	{
		if(token == 1)
		{
			goal.x = USR_SPOT_X + 3;     
			goal.y = USR_SPOT_Y + 5;      
			goal.spin = 200; 
		}
		else if(token == 2)
		{
			goal.x = USR_SPOT_X;    
			goal.y = USR_SPOT_Y + 6;       
			goal.spin =  250; 
		}
		else if(token == 3)
		{
			goal.x = USR_SPOT_X - 3;       
			goal.y = USR_SPOT_Y + 5;       
			goal.spin = -200;  
		}
		else;
	}//2.1close

	// 3.1 channel's goal cal
	else if(channel == 2)
	{
		if(token == 1)
		{
			goal.x = USR_SPOT_X + 3;       
			goal.y = USR_SPOT_Y + 5;    
			goal.spin = 200;
		}
		else if(token == 2)
		{
			goal.x = USR_SPOT_X;   
			goal.y = USR_SPOT_Y + 6;       
			goal.spin = 250; 
		}
		else if(token == 3)
		{
			goal.x = USR_SPOT_X - 3;     
			goal.y = USR_SPOT_Y + 5;       
			goal.spin = -200; 
		}
		else if(token == 4)
		{
			goal.x = USR_SPOT_X;   
			goal.y = 4;     
			goal.spin = 0;  
		}
		else;
	}//3.1 close

	// 5.1 channel's goal calculate
	else if(channel == 3)
	{
		if(token == 1)
		{
			goal.x = USR_SPOT_X + 3;        
			goal.y = USR_SPOT_Y + 5;        
			goal.spin =   200;
		}
		else if(token == 2)
		{
			goal.x = USR_SPOT_X;   
			goal.y = USR_SPOT_Y + 6;        
			//goal.spin = 250;
		}
		else if(token == 3)
		{
			goal.x = USR_SPOT_X - 3;        
			goal.y = USR_SPOT_Y + 5;       
			goal.spin =   -200;
		}
		else if(token == 4)
		{
			goal.x = USR_SPOT_X + 5;        
			goal.y = USR_SPOT_Y - 2;        
			goal.spin = 93;
		}
		else if(token == 5)
		{
			goal.x = USR_SPOT_X -5; 
			goal.y = USR_SPOT_Y - 2;       
			goal.spin =  -93;
		}
		else if(token == 6)
		{
			goal.x = USR_SPOT_X;    
			goal.y = 4;     
			goal.spin =  0;
		}
		else;
	}//5.1channel if close

	return goal;
}

//drive fucntion to goal spot
void Drive_go(struct Spot start, struct Goal_info goal)
{
	int move_x = goal.x-start.x;	// how to move x
	int move_y = goal.y-start.y;	// how to move y

	while(!(rc_encoder_eqep_read(1)==(-120)))
	{
		encoder_check_right();
		rc_motor_set(1, -duty[0]);
		rc_motor_set(2, -duty[1]);
		rc_motor_set(3, -duty[2]);
	}
	rc_encoder_eqep_cleanup();
	rc_encoder_eqep_init();

	while(!(rc_encoder_eqep_read(1)==(move_x*40)))
	{
		encoder_check_forward();
		rc_motor_set(1, duty[0]);
		rc_motor_set(2, -duty[1]);
		rc_motor_set(3, 0);
	}
	rc_encoder_eqep_cleanup();
	rc_encoder_eqep_init();
	
	while(!(rc_encoder_eqep_read(1)==125))
	{
		encoder_check_left();
		rc_motor_set(1, duty[0]);
		rc_motor_set(2, duty[1]);
		rc_motor_set(3, duty[2]);
	}
	rc_encoder_eqep_cleanup();
	rc_encoder_eqep_init();
	
	while(!(rc_encoder_eqep_read(1)==(move_y*40)))  
	{
		encoder_check_forward();
		rc_motor_set(1, duty[0]);
		rc_motor_set(2, -duty[1]);
		rc_motor_set(3, 0);
	}
	rc_encoder_eqep_cleanup();
	rc_encoder_eqep_init();
	if(goal.spin>0)
	{
		while(!(rc_encoder_eqep_read(1)==goal.spin))
		{
			encoder_check_left();
			rc_motor_set(1, duty[0]);
			rc_motor_set(2, duty[1]);
			rc_motor_set(3, duty[2]);
		}
	}
	else if(goal.spin<0)
	{
		while(!(rc_encoder_eqep_read(1)==goal.spin))
		{
			encoder_check_right();
			rc_motor_set(1, -duty[0]);
			rc_motor_set(2, -duty[1]);
			rc_motor_set(3, -duty[2]);
		}
	}
}

// when spin left, encoder speed calculate
void encoder_check_left(void)
{
	duty[0] = 0.4;
	duty[1] = 0.4;
	duty[2] = 0.4;

	if(rc_encoder_eqep_read(1)<rc_encoder_eqep_read(2) && rc_encoder_eqep_read(1)<rc_encoder_eqep_read(3))
		duty[0] += 0.00001;
	else if(rc_encoder_eqep_read(1)>rc_encoder_eqep_read(2) && rc_encoder_eqep_read(1)>rc_encoder_eqep_read(3))
		duty[0] -= 0.00001;

	if(rc_encoder_eqep_read(2)<rc_encoder_eqep_read(1) && rc_encoder_eqep_read(2)<rc_encoder_eqep_read(3))
		duty[1] += 0.00001;
	else if(rc_encoder_eqep_read(2)>rc_encoder_eqep_read(1) && rc_encoder_eqep_read(2)>rc_encoder_eqep_read(3))
		duty[1] -= 0.00001;

	if(rc_encoder_eqep_read(3)<rc_encoder_eqep_read(1) && rc_encoder_eqep_read(3)<rc_encoder_eqep_read(2))
		duty[2] += 0.00001;
	else if(rc_encoder_eqep_read(3)>rc_encoder_eqep_read(1) && rc_encoder_eqep_read(3)>rc_encoder_eqep_read(2))
		duty[2] -= 0.00001;

	if(rc_encoder_eqep_read(1)==rc_encoder_eqep_read(2) && rc_encoder_eqep_read(1)==rc_encoder_eqep_read(3));
	else;
}

// when spin right, encoder speed calculate
void encoder_check_right(void)
{
	duty[0] = 0.4;
	duty[1] = 0.4;
	duty[2] = 0.4;

	if((-1)*rc_encoder_eqep_read(1)<(-1)*rc_encoder_eqep_read(2) && (-1)*rc_encoder_eqep_read(1)<(-1)*rc_encoder_eqep_read(3))
		duty[0] += 0.00001;
	else if((-1)*rc_encoder_eqep_read(1)>(-1)*rc_encoder_eqep_read(2) && (-1)*rc_encoder_eqep_read(1)>(-1)*rc_encoder_eqep_read(3))
		duty[0] -= 0.00001;

	if((-1)*rc_encoder_eqep_read(2)<(-1)*rc_encoder_eqep_read(1) && (-1)*rc_encoder_eqep_read(2)<(-1)*rc_encoder_eqep_read(3))
		duty[1] += 0.00001;
	else if((-1)*rc_encoder_eqep_read(2)>(-1)*rc_encoder_eqep_read(1) && (-1)*rc_encoder_eqep_read(2)>(-1)*rc_encoder_eqep_read(3))
		duty[1] -= 0.00001;

	if((-1)*rc_encoder_eqep_read(3)<(-1)*rc_encoder_eqep_read(1) && (-1)*rc_encoder_eqep_read(3)<(-1)*rc_encoder_eqep_read(2))
		duty[2] += 0.00001;
	else if((-1)*rc_encoder_eqep_read(3)>(-1)*rc_encoder_eqep_read(1) && (-1)*rc_encoder_eqep_read(3)>(-1)*rc_encoder_eqep_read(2))
		duty[2] -= 0.00001;

	if((-1)*rc_encoder_eqep_read(1)==(-1)*rc_encoder_eqep_read(2) && (-1)*rc_encoder_eqep_read(1)==rc_encoder_eqep_read(3));
	else;
}

// when go forward, encoder speed calculate
void encoder_check_forward(void)
{
	duty[0] = 0.7;
	duty[1] = 0.7;

	if(rc_encoder_eqep_read(1)<(-1*rc_encoder_eqep_read(2)))
		duty[0] += 0.00001;
	else if(rc_encoder_eqep_read(1)>(-1*rc_encoder_eqep_read(2)))
		duty[0] -= 0.00001;

	if((-1*rc_encoder_eqep_read(2))<rc_encoder_eqep_read(1))
		duty[1] += 0.00001;
	else if((-1*rc_encoder_eqep_read(2))>rc_encoder_eqep_read(1))
		duty[1] -= 0.00001;
	else;
}