/*
 ============================================================================
 Name        : timer_test.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/time.h>

void timer_handler(int signum);
void runCounter (void);

int timer_trigger;

int main(void)
{
	// set up timer
	struct sigaction sa;
	struct itimerval timer;
	//	 struct itimerspec timer;
	/* Install timer_handler as the signal handler for SIGVTALRM. */
	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &timer_handler;
	//	 sigaction (SIGVTALRM, &sa, NULL);
	sigaction(SIGALRM, &sa, NULL);
	/* Configure the timer to expire after 1 sec... */
	timer.it_value.tv_sec = 1;
	timer.it_value.tv_usec = 0;
	/* ... and every 1 sec after that. */
	timer.it_interval.tv_sec = 1;
	timer.it_interval.tv_usec = 0;
	/* Start a virtual timer. It counts down whenever this process is
	 executing. */
	setitimer(ITIMER_REAL, &timer, NULL);

	while(1){
		runCounter();
	}
}

void timer_handler(int signum) {
	timer_trigger = 1;
}

void runCounter (void) {

	if(timer_trigger == 1) {
		printf("timer triggered\n");
		timer_trigger = 0;
	}
}
