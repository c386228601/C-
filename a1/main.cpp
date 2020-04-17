#include "pch.h"

int main(int argc, char* argv[])
{
       //process the input parameters
        get_input(argv);

       //start detect process
        initial_detect();

      //print and output the detect process into a txt file
        output_results();

        return 0;
}

