/**
 * Basic OpenNI setup to read data from depth camera
 */


#include <stdio.h>
#include <OpenNI.h>

#define SAMPLE_READ_WAIT_TIMEOUT 2000
using namespace openni;

int main()
{
	OpenNI::initialize();
	Device depth_camera;
	depth_camera.open(ANY_DEVICE);
	
	VideoStream depth_stream;	
	depth_stream.create(depth_camera, SENSOR_DEPTH);
	depth_stream.start();
	
	VideoFrameRef depth_frame;

	while (true)
	{
		int changedStreamDummy;
		VideoStream* pStream = &depth_camera;
		OpenNI::waitForAnyStream(&pStream, 1, &changedStreamDummy, SAMPLE_READ_WAIT_TIMEOUT);
		
		depth_camera.readFrame(&depth_frame);				
		DepthPixel* pDepth = (DepthPixel*)depth_frame.getData();
		int middleIndex = (depth_frame.getHeight()+1)*depth_frame.getWidth()/2;

		printf("%8d\n", pDepth[middleIndex]);
	}

	depth_camera.stop();
	depth_camera.destroy();
	depth_camera.close();
	OpenNI::shutdown();

	return 0;
}
