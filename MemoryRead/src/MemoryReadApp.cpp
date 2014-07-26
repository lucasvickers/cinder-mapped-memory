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

class MemoryReadApp : public AppNative {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
	void shutdown();

  protected:
	windows_shared_memory	mMem;
	mapped_region			mRegion;

	string					mSharedName;

};

void MemoryReadApp::setup()
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

}

void MemoryReadApp::shutdown()
{
}

void MemoryReadApp::mouseDown( MouseEvent event )
{
}

void MemoryReadApp::update()
{
	char *mem = static_cast<char*>(mRegion.get_address());
	if(*mem == 1) {
		console() << "clicked!" << endl;
		memset(mRegion.get_address(), 0, 1);
	}
}

void MemoryReadApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP_NATIVE( MemoryReadApp, RendererGl )
