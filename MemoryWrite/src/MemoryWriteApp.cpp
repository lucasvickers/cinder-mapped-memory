#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

#include <boost/interprocess/windows_shared_memory.hpp>
#include <boost/interprocess/mapped_region.hpp>

#include <cstring>
#include <cstdlib>
#include <string>

using namespace ci;
using namespace ci::app;
using namespace std;
using namespace boost::interprocess;


class MemoryWriteApp : public AppNative {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
	void shutdown();

  protected:
	windows_shared_memory 	mMem;
	mapped_region			mRegion;

	string					mSharedName;
};

void MemoryWriteApp::setup()
{
	mSharedName = "CinderMemoryFile";

	try {
		mMem = windows_shared_memory(open_or_create, mSharedName.c_str(), read_write, 1000);
	} catch ( interprocess_exception& e ) {
		console() << "Unable to create memory map: " << e.what() << endl;
	}

	try {
		mRegion = mapped_region(mMem, read_write);
	} catch ( interprocess_exception& e ) {
		console() << "Unable to map region: " << e.what() << endl;
	}

	// set it all to 0
	memset(mRegion.get_address(), 0, mRegion.get_size());
}

void MemoryWriteApp::shutdown()
{
}

void MemoryWriteApp::mouseDown( MouseEvent event )
{
	// set bit to 1
	memset(mRegion.get_address(), 1, 1);
}

void MemoryWriteApp::update()
{
}

void MemoryWriteApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP_NATIVE( MemoryWriteApp, RendererGl )
