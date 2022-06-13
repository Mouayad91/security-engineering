#include<stdio.h>
#include<time.h>

int main() {
    // Set time_t variable;
    time_t with_ctime = time(0);
    // Set char variable
    char with_l_time[100];
    // Print ctime using string formatting and ctime method
    printf("With ctime = %s", ctime(&with_ctime));

    // Call localtime and set variable with return value
    struct tm *time = localtime(&with_ctime);
    // Convert tm struct into date and time representation and add to with_l_time
    strftime(with_l_time, sizeof(with_l_time), "%c", time);
    // Print localtime
    printf("With Localtime = %s", with_l_time);
    return 0;
}