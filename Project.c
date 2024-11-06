/*
Program: HSI255 Project 
Author: HELI JITENDRAKUMAR PATEL
Date: November 27, 2023
Purpose: This program initially begins with LEDs off and servo motor in the default position. First user will be prompt to enter a thresold tempertaure in degree Celsius. Then again ask the user for which exit strategy they would like to use, option 1 is ask the user how many seconds they want the program to run, and the program will run for that long. And option 2 is after how many servo motor activations the program will end after the threshold temperature has been activated. The program will monitor the temperature continuously. If temperature is above the threshold, the red LED will be lit , and when the temperature drops below the threshold, the red LED turns off and the blue LED turns on and the servo motor turns approximately 45 degrees and alert the user of low temperature. When the temperature goes back above the threshold, the red LED turns back on, the blue LED turns off and the servo motor returns to its default position. The console window updates the temperature 5 times per second regardless of the actual temperature.
*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "c:/Program Files (x86)/LabJack/Drivers/LabJackUD.h"

int main()
{
    LJ_ERROR lj_cue;
    LJ_HANDLE lj_handle = 0;

    double valAIN0, thresTemp;
    int userChoice, seconds, sActivations, time=0, counter = 0;

    lj_cue = OpenLabJack(LJ_dtU3, LJ_ctUSB, "1", 1, &lj_handle);
    lj_cue = ePut(lj_handle, LJ_ioPIN_CONFIGURATION_RESET, 0, 0, 0);

    lj_cue = AddRequest(lj_handle, LJ_ioGET_AIN, 0, 0, 0, 0);
    lj_cue = AddRequest(lj_handle, LJ_ioPUT_DAC, 0, 0, 0, 0);
    lj_cue = AddRequest(lj_handle, LJ_ioPUT_DAC, 1, 0, 0, 0);
    lj_cue = AddRequest(lj_handle, LJ_ioPUT_CONFIG, LJ_chTIMER_COUNTER_PIN_OFFSET, 4, 0, 0);       //FIO4
    lj_cue = AddRequest(lj_handle, LJ_ioPUT_CONFIG, LJ_chTIMER_CLOCK_BASE, LJ_tc48MHZ_DIV, 0, 0);  //48MHZ TCB with div
    lj_cue = AddRequest(lj_handle, LJ_ioPUT_CONFIG, LJ_chTIMER_CLOCK_DIVISOR, 15, 0, 0);           //divisor of 15
    lj_cue = AddRequest(lj_handle, LJ_ioPUT_CONFIG, LJ_chNUMBER_TIMERS_ENABLED, 1, 0, 0);          //enable the timer
    lj_cue = AddRequest(lj_handle, LJ_ioPUT_TIMER_MODE, 0, LJ_tmPWM16, 0, 0);                      //timer mode 16bit
    lj_cue = AddRequest(lj_handle, LJ_ioPUT_TIMER_VALUE, 0, 65535, 0, 0);
    lj_cue = Go();
   

        printf("\n\t\t*WELCOME TO THE TEMPERATURE MONITORING PROGRAM*\n\n");
        printf("\n1. This program initially begins with LEDs off and servo motor in the default position. \n2. First user will be prompt to enter a thresold tempertaure in degree Celsius. \n3. Then again ask the user for which exit strategy they would like to use. \n\ta) How many seconds they want the program to run, and the program will run for that long. \n\tb)After how many servo motor activations the program will end after the threshold temperature has been activated. \n4. The program will monitor the temperature continuously. \n5. If temperature is above the threshold, the red LED will be lit , and when the temperature drops below the threshold, the red LED turns off and the blue LED turns on and the servo motor turns approximately 45 degrees and alert the user of low temperature. \n   When the temperature goes back above the threshold, the red LED turns back on, the blue LED turns off and the servo motor returns to its default position. \n6. The console window updates the temperature 5 times per second regardless of the actual temperature.\n\n");

        system("pause");

        printf("\nEnter a threshold tempertaure (in degree Celsius): ");
        scanf("%lf", &thresTemp);

        printf("\n\nPlease choose the exit strategy:");
        printf("\n\n1. How many seconds do you want the program to run for: ");
        printf("\n2. Servo Motor Activation");
        scanf("%d", &userChoice);

        if (userChoice == 1)                                                              //loof for choice 1
        {
            printf("\n\n1. Enter the time(in seconds) you want the program to run for: ");
            scanf("%d", &seconds);

            while (time < (seconds * 5))                                                  //loop to check temperature for the specified time
            {
                lj_cue = AddRequest(lj_handle, LJ_ioGET_AIN, 0, 0, 0, 0);
                lj_cue = Go();
                valAIN0 = GetResult(lj_handle, LJ_ioGET_AIN, 0, &valAIN0);

                if (valAIN0 > (thresTemp * 50))
                {
                    lj_cue = AddRequest(lj_handle, LJ_ioPUT_DAC, 1, 0, 0, 0);              //BLUE LED OFF
                    lj_cue = AddRequest(lj_handle, LJ_ioPUT_DAC, 0, 5, 0, 0);              //RED LED ON

                    lj_cue = AddRequest(lj_handle, LJ_ioPUT_TIMER_VALUE, 0, 58000, 0, 0);  
                    lj_cue = Go();
                    printf("\n\nTemperature is above the Threshold Temperature!\nRED LED ON!!!\n");
                }
                if(valAIN0 < (thresTemp *50))
                {
                    lj_cue = AddRequest(lj_handle, LJ_ioPUT_DAC, 0, 0, 0, 0);              //RED LED OFF          
                    lj_cue = AddRequest(lj_handle, LJ_ioPUT_DAC, 1, 5, 0, 0);              //BLUE LED ON
                    lj_cue = AddRequest(lj_handle, LJ_ioPUT_TIMER_VALUE, 0, 59800, 0, 0);  //servo motors moves to 45 degrees
                    lj_cue = Go();
                    printf("\n\nTemperature is below the Threshold Temperature!\nBLUE LED ON!!!");  
                    printf("\nSrevo motor moves to 45 degrees!!\n");
                }

                printf("\nThe current temperature is: %.2lf degree Celcius\n\n", valAIN0 * 50);
                Sleep(200);
                time++;
            }
        }

        else if (userChoice == 2)                                                          //loop for choice 2
        {
            printf("\n\nEnter the number of servo motor activations you want: ");
            scanf("%d", &sActivations);

            while (counter < sActivations)                                                  //check for the number of servo motor activations 
            {
                int count = 0;                                          //Track the number of times a certain condition is met within loop(sticky key concept)
                lj_cue = AddRequest(lj_handle, LJ_ioGET_AIN, 0, 0, 0, 0);
                lj_cue = Go();
                valAIN0 = GetResult(lj_handle, LJ_ioGET_AIN, 0, &valAIN0);

                if (valAIN0 < (thresTemp * 50))
                {
                    while (valAIN0 < (thresTemp * 50))
                    {
                        lj_cue = AddRequest(lj_handle, LJ_ioGET_AIN, 0, 0, 0, 0);
                        lj_cue = Go();
                        valAIN0 = GetResult(lj_handle, LJ_ioGET_AIN, 0, &valAIN0);

                        if (valAIN0 < (thresTemp * 50))
                        {
                            lj_cue = AddRequest(lj_handle, LJ_ioPUT_DAC, 0, 0, 0, 0);              //RED LED OFF          
                            lj_cue = AddRequest(lj_handle, LJ_ioPUT_DAC, 1, 5, 0, 0);              //BLUE LED ON
                            lj_cue = AddRequest(lj_handle, LJ_ioPUT_TIMER_VALUE, 0, 59800, 0, 0);  //servo motors moves to 45 degrees
                            lj_cue = Go();
                            printf("\n\nTemperature is below the Threshold Temperature!\nBLUE LED ON!!!");
                            printf("\nSrevo motor moves to 45 degrees!!\n");
                            printf("\nThe current temperature is: %.2lf degree Celcius\n\n", valAIN0 * 50);
                            count++;
                        }

                        if (count == 1)
                        {
                            counter++;
                        }
                        Sleep(200);
                    }
                }

                if (valAIN0 > (thresTemp * 50))
                {
                      lj_cue = AddRequest(lj_handle, LJ_ioPUT_DAC, 1, 0, 0, 0);              //BLUE LED OFF
                      lj_cue = AddRequest(lj_handle, LJ_ioPUT_DAC, 0, 5, 0, 0);              //RED LED ON
                      lj_cue = AddRequest(lj_handle, LJ_ioPUT_TIMER_VALUE, 0, 58000, 0, 0);
                      lj_cue = Go();
                      printf("\n\nTemperature is above the Threshold Temperature!\nRED LED ON!!!\n");
                }

                printf("\nThe current temperature is: %.2lf degree Celcius\n\n", valAIN0 * 50);
                Sleep(200);
                    
            }
        }

        else
        {
            printf("Invalid input!! Please enter the valid input.");
        }

        lj_cue = ePut(lj_handle, LJ_ioPIN_CONFIGURATION_RESET, 0, 0, 0);
        lj_cue = AddRequest(lj_handle, LJ_ioPUT_DIGITAL_BIT, 4, 1, 0, 0);

        lj_cue = AddRequest(lj_handle, LJ_ioPUT_DAC, 1, 0, 0, 0);              
        lj_cue = AddRequest(lj_handle, LJ_ioPUT_DAC, 0, 0, 0, 0);              
        lj_cue = AddRequest(lj_handle, LJ_ioPUT_TIMER_VALUE, 0, 65535, 0, 0);
        lj_cue = Go();
      

        puts("\tEXIT!!!\n");
        system("pause");
        Close();
        return 0;
    }