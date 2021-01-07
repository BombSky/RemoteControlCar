#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>

int g_PWM_GPIO_1 = 18;


int main(void)
{
    wiringPiSetupGpio();

    pinMode(g_PWM_GPIO_1, PWM_OUTPUT);      //������������ʽ
    pwmSetMode(PWM_MODE_MS);
    pwmSetRange(2000);
    pwmSetClock(192);
    int ms;
    while (1)
    {
        scanf("%d", &ms);
        pwmWrite(g_PWM_GPIO_1, ms);        //100-390
        //450����

    }

    return 0;
}