#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int file_size = 0;

/* Job struct */
typedef struct {
    int id;
    int arrival;
    int processing;
    int remaining;
    int finish;
} job;



/* Function prototypes */
void update_job(job* job, int id, int arrival, int processing);
void process_file(FILE* file_p, job* job_array);
void print_stats(job* job_in);



int main(int argc, char* argv[])
{
    /* Instance variables */
    int i;
    int job_counter = 0, job_counter2 = 1, job_counter3 = 2, job_counter4 = 3;

    char* filename = argv[1];
    FILE* file_p = fopen(filename, "r");

    job job_array[1000];

    /* Program argument checking */
    if (argc != 2) {
        printf("ffs\n");
        return 0;
    }

    /* Update each job with info from the .txt file */
    process_file(file_p, job_array); /* Fills job_array with the info from input.txt */
    fclose(file_p);

    /* Loop until a break is executed (will happen when all jobs are done) */
    for (i = 0; ; i++) {

        /* Cycle back to 0 if job_counter is out of range */
        if (job_counter >= file_size) {
            job_counter = 0;
        }

        /* If the arrival time still hasn't passed, then continue */
        if (job_array[job_counter].arrival > i) {
            continue;
        }

        /* Check to see if all jobs are done, and if so break */
        int j;
        int number_completed = 0;
        for (j = 0; j < file_size; j++) {
            if (job_array[j].remaining <= 0) {
                number_completed++;
            }
        }
        if (number_completed >= file_size) {
            printf("\nall jobs completed\n\n");
            break;
        }

        /* If the job is done, then continue. This iteration never happened. */
        if (job_array[job_counter].remaining <= 0) {
            job_counter++;
            i--;
            continue;
        }

        /* If 0 < remaining time < slice time */
        if (job_array[job_counter].remaining < 4 && job_array[job_counter].remaining > 0) {
            i += job_array[job_counter].remaining; /* The loop incrementing function handles 1µs */
            job_array[job_counter].remaining = 0;
            job_array[job_counter].finish = i;
            job_counter++;
            continue;
        }
        /* If remaining time == 4 */
        else if (job_array[job_counter].remaining == 4) {
            i += job_array[job_counter].remaining;
            job_array[job_counter].remaining = 0;
            job_array[job_counter].finish = i;
            job_counter++;
            continue;
        /* If remaining time > 4 */
        } else if (job_array[job_counter].remaining > 4) {
            i += 3; /* would be 4 but the loop incrementing function handles 4 */
            job_array[job_counter].remaining -= 4;
            job_counter++;
            continue;
        }
    }

    for (i = 0; i < file_size; i++) {
        print_stats(&job_array[i]);
    }

    long long unsigned sum = 0;
    for (i = 0; i < file_size; i++) {
        sum += (job_array[i].finish - job_array[i].arrival);
    }
    sum = sum / (file_size + 1);
    printf("\nAverage turnaround time : %llu\n\n", sum);

    printf("(Time is measured in ticks)\n");

    return 0;
}



/* Manually update the job passed to the function */
void update_job(job* job, int id_in, int arrival_time, int processing_time)
{
    job->id = id_in;
    job->arrival = arrival_time;
    job->processing = processing_time;
    job->remaining = processing_time;
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

    file_size = line_number;
}

void print_stats(job* job_in)
{
    printf("JOB # %d\n", job_in->id);
    printf("Arrival time    : %d\n", job_in->arrival);
    printf("Service time    : %d\n", job_in->processing);
    printf("Finish time     : %d\n", job_in->finish);
    printf("Turnaround time : %d\n", (job_in->finish - job_in->arrival));
}

