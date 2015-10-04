{
  "targets": [
    {
      "target_name": "robot",
      "sources": [ "Robot.cpp", "RobotWrapper.cpp"],
      "include_dirs": [ 
	    "<!(node -e \"require('nan')\")",
		"../Robot",
		"../RobotController",
		"../RobotHead",
		"../PiCamera",
	  ],
      "conditions" : [
      	[
		  'OS=="linux"', {
     	    "cflags!": [ "-fno-exceptions" ],
     	    "cflags_cc!": [ "-fno-exceptions" , "-fno-rtti" ],
     	    "cflags_cc": [ "-std=c++0x" , "<!@(pkg-config --cflags opencv)" ],
            "cflags_cc+": ["-frtti"],			
			"ldflags": [ "<!@(pkg-config --libs --libs-only-other opencv)" ],
			"libraries": [ "<!@(pkg-config --libs opencv)" ],
			"cflags": [ "<!@(pkg-config --cflags opencv)" ],
      	  }
		]
      ],
	  "libraries": [
	    "/media/workspace/robot-projects/Raspberry/Segway/Robot/dist/Debug/GNU-Linux-x86/librobot.a",
        "/media/workspace/robot-projects/Raspberry/Segway/RobotController/dist/Debug/GNU-Linux-x86/librobotcontroller.a",
	    "/media/workspace/robot-projects/Raspberry/Segway/RobotHead/dist/Debug/GNU-Linux-x86/librobothead.a",
	    "/media/workspace/robot-projects/Raspberry/Segway/PiCamera/dist/Debug/GNU-Linux-x86/libpicamera.a",
	    "/media/workspace/robot-projects/Raspberry/Segway/PiCamera/lib/libraspicam.a",
		"/media/workspace/robot-projects/Raspberry/Segway/PiCamera/lib/libraspicam_cv.a",
		"/usr/local/lib/libraspicam.a",
		"-lopencv_core", 
		"-lopencv_imgproc", 
		"-lopencv_calib3d",
		"-lopencv_features2d", 
		"-lopencv_objdetect", 
		"-lopencv_video", 
		"-lopencv_highgui", 
		"-lopencv_contrib", 
		"-lopencv_flann", 
		"-lopencv_ml", 
		"-lopencv_gpu", 
		"-lopencv_legacy",
        "-lopencv_nonfree",		
		"/opt/vc/lib/libbcm_host.so",
		"/opt/vc/lib/libmmal.so",
	  ],      
    }
  ]
}