#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
void update_job(job* job, int id, int arrival, int processing);
void process_file(FILE* file_p, job* job_array);


int main(void)
{
    job job_array[12];
    
    int i;
    for (i = 0; i < 12; i++) {
        job_array[i].id = i + 1;
    }

    /* I'm eventually going to just read in a CSV or other file and update the jobs that way    *
     * with a for loop in the future                                                            */
    FILE* file_p = fopen("input.txt", "r");
    process_file(file_p, job_array);
    fclose(file_p);

    /* Variable setup for the loop that simulates a processor waiting for jobs. */
//    time_t start_time;
//    time(&start_time);
//    time_t x;
//    time_t current_time;
//    i = 0;
//    int number_processed = 0;

    /* simulate a processor (loop forever, waiting for jobs ) */
    /* (pretend each loop iteration is a millisecond) */
//    for ( ; ; ) {   /* NOTE: I treat each iteration of the loop as a micro-second */
//
//        if ( number_processed == 12 ) {
//            break;      /* Stop running, all jobs have been passed. */
//        }
//
//        /* If the current system time is */
//        if (job_array[i].arrival >= (int) current_time) {
//            run(job_array[i]);
//        } else {
//            continue;
//        }
//        i++;
//    }

    return 0;
}

/* Manually update the job passed to the function */
void update_job(job* job, int id_in, int arrival_time, int processing_time)
{
    job->id = id_in;
    job->arrival = arrival_time;
    job->processing = processing_time;

    printf("JOB ID: %d\tARRIVAL: %d\tPROCESSING: %d\n", job->id, job->arrival, job->processing);
}

void process_file(FILE* file_p, job* job_array)
{
    char line[16]; /* Is actually 15, leaves 1 char for \0 */
    int line_number = 0; /* allows you to give each job an ID */
    /* Loop over every line in the file */
    while ( fgets(line, sizeof(line), file_p) ) {

        /* Iterate across the line, storing the values in arrival_time and process_time */
        int arrival_time = 0, process_time = 0;
        char number_buffer[16];
        memset(number_buffer, 0, sizeof(number_buffer));

        /* First loop obtains arrival_time */
        int i;
        for (i = 0; i < sizeof(line); i++) {
            if ( line[i] != ' ' ) {
                number_buffer[i] = line[i];
            } else {
                arrival_time = atoi(number_buffer);
                break;
            }
        }

        memset(number_buffer, 0, sizeof(number_buffer));

        int j = 0;
        /* Second loop obtains process_time */
        for (i = i + 1; i < sizeof(line); i++) {
            if ( line[i] != '\0' ) {
                number_buffer[j] = line[i];
            } else {
                process_time = atoi(number_buffer);
                break;
            }
            j++;
        }

        /* job at index line_number will now have id, arrival_time, and process_time. */
        update_job(&job_array[line_number], (line_number + 1), arrival_time, process_time);

        line_number++;

    }
}
