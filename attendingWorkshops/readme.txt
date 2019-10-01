A student signed up for n workshops and wants to attend the maximum number of workshops where no two workshops overlap. You must do the following:

Implement 2 structures:

    struct Workshop having the following members:
        The workshop's start time.
        The workshop's duration.
        The workshop's end time.

    struct Available_Workshops having the following members:
        An integer n (the number of workshops the student signed up for).
        An array of type Workshop array having size n


Implement 2 functions:

    Available_Workshops* initialize (int start_time[], int duration[], int n)
    Creates an Available_Workshops object and initializes its elements using
    the elements in the start_time and duration f)parameters (both are of size
    n). Here, start_time and duration are the respective start time and
    duration for the ith workshop. This function must return a pointer to an Available_Workshops object.

int CalculateMaxWorkshops(Available_Workshops* ptr)
Returns the maximum number of workshops the student can attend—without overlap. The next workshop cannot be attended until the previous workshop ends.
