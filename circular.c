#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* ints are how i'll keep track of whether or not the first and second processors are busy. */
static int processor1_busy = 0;
static int processor2_busy = 0;

/* Job struct */
typedef struct {
    int id;
    int arrival;
    int processing;
} job;

/* Function prototypes */
void update_job(job* job, int arrival, int processing);


int main(void)
{
    job job_array[12];
    
    int i;
    for (i = 0; i < 12; i++) {
        job_array[i].id = i + 1;
    }

    /* I'm eventually going to just read in a CSV or other file and update the jobs that way    *
     * with a for loop in the future                                                            */
    update_job(&job_array[0], 4, 9);
    update_job(&job_array[1], 15, 2);
    update_job(&job_array[2], 18, 16);
    update_job(&job_array[3], 20, 3);
    update_job(&job_array[4], 26, 29);

    /* Variable setup for the loop that simulates a processor waiting for jobs. */
    time_t start_time;
    time(&start_time);
    time_t x;
    time_t current_time;
    i = 0;

    /* simulate a processor (loop forever, waiting for jobs ) */
    /* (pretend each loop iteration is a millisecond) */
    for ( ; ; ) {

        if ( i == 12 ) {
            break;      /* Stop running, all jobs have been passed. */
        }

        /* If the current system time is */
        if (job_array[i].arrival >= (int) current_time) {
            run(job_array[i]);
        } else {
            continue;
        }
        i++;
    }

    return 0;
}

/* Manually update the job passed to the function */
void update_job(job* job, int arrival_time, int processing_time)
{
    job->arrival = arrival_time;
    job->processing = processing_time;

    printf("JOB ID: %d\tARRIVAL: %d\tPROCESSING: %d\n", job->id, job->arrival, job->processing);
}
