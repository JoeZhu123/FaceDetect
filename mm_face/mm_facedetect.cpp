#include<stdio.h>
#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/objdetect/objdetect.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;
/** Function Headers **/
void detectAndDisplay(Mat frame);

/** Global variables */
//-- Note, either copy these two files from opencv/data/haarscascades to your current folder, or change these locations
String face_cascade_name = "haarcascade_frontalface_alt.xml";
String mouth_cascade_name = "haarcascade_mcs_mouth.xml";
String nose_cascade_name = "haarcascade_mcs_nose.xml";
//String leftear_cascade_name = "haarcascade_mcs_leftear.xml";
//String rightear_cascade_name = "haarcascade_mcs_rightear.xml";
String eyes_cascade_name = "haarcascade_eye.xml";//\\home\\joezhu\\opencv_P\\opencv-2.4.9\\data\\harrcascades\\路径问题怎么破
CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;
CascadeClassifier mouth_cascade;
CascadeClassifier nose_cascade;
//CascadeClassifier leftear_cascade;
//CascadeClassifier rightear_cascade;
string window_name = "Capture - MM Face detection";
RNG rng(12345);

int main(int argc,char** argv)
{
  	//-- 1. Load the cascades
  	if( !face_cascade.load( face_cascade_name ) ){ printf("--(!)Error loading\n"); return -1; };
  	if( !eyes_cascade.load( eyes_cascade_name ) ){ printf("--(!)Error loading\n"); return -1; };
	if( !mouth_cascade.load( mouth_cascade_name ) ){ printf("--(!)Error loading\n"); return -1; };
  	if( !nose_cascade.load( nose_cascade_name ) ){ printf("--(!)Error loading\n"); return -1; };
	//if( !leftear_cascade.load( leftear_cascade_name ) ){ printf("--(!)Error loading\n"); return -1; };
  	//if( !rightear_cascade.load( rightear_cascade_name ) ){ printf("--(!)Error loading\n"); return -1; };
 	//-- 2. Read the mm image
	if(argc!=2)
	{
		cout<<"usage: DisplayImage.out <Image_Path>\n"<<endl;
		return -1;	
	}
	Mat image;
	image=imread(argv[1],1);	
	//-- 3. Apply the classifier to the frame
      	if( !image.empty() )
       	{ detectAndDisplay( image ); }
      	else
       	{
		cout<<"No image data"<<endl;	
		return -1;
	}

      	int c = waitKey(0);
      	if( (char)c == 'c' ) { destroyWindow("window_name"); }

	return 0;
}

/**
 * @function detectAndDisplay
 */
void detectAndDisplay( Mat frame )
{
   std::vector<Rect> faces;
   Mat frame_gray;

   cvtColor( frame, frame_gray, COLOR_BGR2GRAY );
   equalizeHist( frame_gray, frame_gray );
   //-- Detect faces
   face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );

   for( size_t i = 0; i < faces.size(); i++ )
    {
      Point center( faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2 );
      ellipse( frame, center, Size( faces[i].width/2, faces[i].height/2), 0, 0, 360, Scalar( 255, 0, 255 ), 2, 8, 0 );

      Mat faceROI = frame_gray( faces[i] );
      std::vector<Rect> eyes;
      std::vector<Rect> mouth;
      std::vector<Rect> nose;
      std::vector<Rect> leftear;
      std::vector<Rect> rightear;

      //-- In each face, detect mouth
      mouth_cascade.detectMultiScale( faceROI, mouth, 1.1, 2, 0 |CV_HAAR_SCALE_IMAGE, Size(30, 30) );

      for( size_t j = 0; j < mouth.size(); j++ )
       {
         Point mouth_center( faces[i].x + mouth[j].x + mouth[j].width/2, faces[i].y + mouth[j].y + mouth[j].height/2 );
         int radius = cvRound( (mouth[j].width + mouth[j].height)*0.25 );
         circle( frame, mouth_center, radius, Scalar( 255, 0, 0 ), 3, 8, 0 );
       }
     //-- In each face, detect nose
      nose_cascade.detectMultiScale( faceROI, nose, 1.1, 2, 0 |CV_HAAR_SCALE_IMAGE, Size(30, 30) );

      for( size_t j = 0; j < nose.size(); j++ )
       {
         Point nose_center( faces[i].x + nose[j].x + nose[j].width/2, faces[i].y + nose[j].y + nose[j].height/2 );
         int radius = cvRound( (nose[j].width + nose[j].height)*0.25 );
         circle( frame, nose_center, radius, Scalar( 255, 0, 0 ), 3, 8, 0 );
       }
/*
	//-- In each face, detect leftear
      leftear_cascade.detectMultiScale( faceROI, leftear, 1.1, 2, 0 |CV_HAAR_SCALE_IMAGE, Size(30, 30) );

      for( size_t j = 0; j < leftear.size(); j++ )
       {
         Point leftear_center( faces[i].x + leftear[j].x + leftear[j].width/2, faces[i].y + leftear[j].y + leftear[j].height/2 );
         int radius = cvRound( (leftear[j].width + leftear[j].height)*0.25 );
         circle( frame, leftear_center, radius, Scalar( 255, 0, 0 ), 3, 8, 0 );
       }
	//-- In each face, detect rightear
      rightear_cascade.detectMultiScale( faceROI, rightear, 1.1, 2, 0 |CV_HAAR_SCALE_IMAGE, Size(30, 30) );

      for( size_t j = 0; j < rightear.size(); j++ )
       {
         Point rightear_center( faces[i].x + rightear[j].x + rightear[j].width/2, faces[i].y + rightear[j].y + rightear[j].height/2 );
         int radius = cvRound( (rightear[j].width + rightear[j].height)*0.25 );
         circle( frame, rightear_center, radius, Scalar( 255, 0, 0 ), 3, 8, 0 );
       }
*/
	//-- In each face, detect eyes
      eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0 |CV_HAAR_SCALE_IMAGE, Size(30, 30) );

      for( size_t j = 0; j < eyes.size(); j++ )
       {
         Point eye_center( faces[i].x + eyes[j].x + eyes[j].width/2, faces[i].y + eyes[j].y + eyes[j].height/2 );
         int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
         circle( frame, eye_center, radius, Scalar( 255, 0, 0 ), 3, 8, 0 );
       }
    }
   //-- Show what you got
   imshow( window_name, frame );
}

