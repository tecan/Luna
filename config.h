 #ifndef INCLUDES
 #define INCLUDES
 //#define PYTHON  // defined in the codeblocks project option defines for target management and testing builds

 #define COMPRESS //needed for empython
 #define EXTRAS

 #ifndef __EMSCRIPTEN__
 //#define SOUND
 //todo put in simple openal sound
 #endif

//#define _DEBUG_MODE_
//#define _PLAY_SOUND_
//#define AgAudio      //- not currently working
//#define SDLMixers
//#define OPENAL
//#define SDLsound

   // #define IRRCD   // irrlicht Collision Detection
    #define EVENTS
    #define FPS
    #define CSG
   // #define SGRAPH2D
   // #define WIND
    #define SCENE
   // #define IRRc
 //   #define PostProcess
  //  #define ReflectiveWater
  //  #define ReflectWater-Main
  //#define SPARK
  #define PHYSICS
 // #define SKELETON
//#define PostProcess
  //#define VEGETATION
  //  #define TREES //very cpu intensive
  //  #define ATMOSPHERE  //  freezes when no video acceleration is used
                        //  or as a user without access to video rights is used
    //  #define FLARE
    //#define FLARES
  //  #define FLARE2  // more realistic and working

   // #define DECALS2       // simple decals
    //#define DECALS       //decalmanager sortof working slow tho
  #define TESSELATE

  //  #define CODEEDITOR
  //  #define FLAG    //
  //  #define FLAG2   //FMX
   // #define COMPASS
  //  #define BOIDS
  #define TERRAIN
  //  #define occlusion.
//#define OCCLUSION
  //  #define FPSWEAPON // no uses diff event receiver than player so wont drive car or shoot cubes // screws with the flare2

  //if bullet carnot enabled with physics and car calls it crashes FIXME
    #define BULLETCAR // if FPSWEAPON is enabled the car wont work. diff event rec
    #define LOADLEVELS // dont use this without bullet or with occlusion its slow?
  //  #define BULLETBLEND
  //  #define RAG   //bulletRagdoll
   // #define EXTRAS
  //  #define DESTRUCTION
  //  #define FORMATIONDEMO
    #define HUD
    #define Image2D // Just testing out
  //  #define CHOPPER
  //  #define  OPENSTEER
  //  #define SQLITE

//  #define SCALC
//#define FT2
//#define SPRITES
//#define PYTHON_MINIMALTEST


//    #define VIDEO
  //  #define PostProcess
  #endif
