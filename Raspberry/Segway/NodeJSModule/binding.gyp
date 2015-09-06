{
  "targets": [
    {
      "target_name": "robot",
      "sources": [ "Robot.cpp", "RobotWrapper.cpp"],
      "include_dirs": [ 
	    "<!(node -e \"require('nan')\")",
		"/media/workspace/temp/NetBeansLib/HelloLibrary/"
	  ],
	  #"libraries": ["/media/workspace/temp/NetBeansLib/HelloLibrary/libhellolibrary.a"],      
    }
  ]
}