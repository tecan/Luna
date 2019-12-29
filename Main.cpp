#include "Luna.h"
#include <cstdio>

#ifdef __APPLE__
	#import <Cocoa/cocoa.h>
#endif

#ifdef WIN32
	#include <winsock2.h>
#endif

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif
int argc1=0;
 char** argv1;
bool init=true;

Luna game ( argc1,argv1 );

void main_loop(){
	while (!game.m_cInGameEvents.Quit){
		if ( init ){
				init=false;

				game.Run();
				//game.main_loop();
		}else{

				game.main_loop();
				//game.main_loop();
		}
	}
}


int main ( int argc, char** argv )
{
	#ifdef __OSX__
		NSApplicationLoad();
	#endif

	#ifdef __EMSCRIPTEN__
	emscripten_set_main_loop(main_loop,0,1);
#else
main_loop();
		#endif // __EMSCRIPTEN__
		system("PAUSE");
	return 0;
}

