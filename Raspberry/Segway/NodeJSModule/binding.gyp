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
     	    "cflags_cc": [ "-std=c++0x" ],
            "cflags_cc+": ["-frtti"],
      	  }
		]
      ],
	  #"libraries": ["/media/workspace/temp/NetBeansLib/HelloLibrary/libhellolibrary.a"],      
    }
  ]
}