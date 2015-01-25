#include <cstdlib>
#include "opencv/cv.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "RaspiCamCV.h"
#include <time.h>
#include <stdio.h>

using namespace std;

int main(int argc, char** argv) {
    RaspiCamCvCapture* capture = raspiCamCvCreateCameraCapture(320,240,0);
    IplImage* frame;
    CvMemStorage* pStorage = cvCreateMemStorage(0);

    time_t start, end;
    double fps, sec;
    printf("Start measuring FPS.\n");
    fflush(stdout);
    
    while (1) {
        time(&start);

        for(int i=0; i<100; i++)
        {
                frame = raspiCamCvQueryFrame(capture);
        }
        time(&end);
        
        sec = difftime(end, start);

        fps = 100.0 / sec;
        printf("FPS = %.2f\n", fps);
        if (!frame) {
            printf("Error");
            break;
        }
        fflush(stdout);
    }
    
    raspiCamCvReleaseCapture(&capture);    
    return 0;
}

