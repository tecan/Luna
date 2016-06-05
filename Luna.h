#ifndef PHYSIC
#define PHYSIC

#include <vector>
#include <string>
#include <sstream>
#include <map>

//#include <pthread.h>

#include "Events/Events.h"
#include "Events/InGameEventReceiver.h"
#include "Scene/customNodes.h"

#include <cAudio.h>

#include "Net/irrNetClient.h"
#include "entities/player.h"
//#include "Encryption/Blowfish.h"
#include "Physics/Physics.h"
//#include "Physics/Vehicle.h"
#include "Scene/Scene.h"
#include <irrNet.h>
#include "./Scene/decals/decalscenenode.h"
#include "TerrainFactory/Terrain.h"
#include <irrNet.h>

//#include "TerrainFactory/GrassSceneNode/CGrassPatchSceneNode.h"

class Luna
{
	public:
		Luna ( int argc, char** argv );
		~Luna(); // Cleans up the engine
		int Run();
		IrrlichtDevice *device;
		unsigned int resolution[2];
        IVideoDriver *driver;
		ISceneManager *smgr;


		int init();
		int shutdown();
		int lobby();
		int mainloop();
		int devloop();
		int doLogin ( const std::wstring &username, const std::wstring &password );
		int handleMessages();

		int AddShader();

        void CheckKeyStates(void);

		IGUIEnvironment *guienv;

		EventRec events;
		InGameEventReceiver m_cInGameEvents;

        // Factory threads
		//pthread_t soundThread

        //AUDIO--------------------------
        cAudio::IAudioManager* manager;
        cAudio::IAudioSource* mysound;

		// Encryption--------------------
            //Encryption::Blowfish enc;
		// Network related

       // net::SOutPacket packet;

        // Character related
		std::wstring username;
		std::wstring password;

		// Player Physics---------------
        Player *m_cPlayer;
        //  Scene *m_cScene;
		Physics *m_cPhysics;

        SKeyMap keyMap[8]; // KEYMAP
        f32 frameDeltaTime;

        //video::ITexture *tex1;
        //video::ITexture *tex2;
        //    scene::CGrassPatchSceneNode *grass[100];
        //core::array<video::E_MATERIAL_TYPE> modes;
        //
        //scene::IWindGenerator *wind;

    int MakeTrees();
    void recursiveFillMetaSelector(scene::ISceneNode* node, scene::IMetaTriangleSelector* meta );

    scene::IMetaTriangleSelector* metaSelector;
        scene::ISceneNodeAnimatorCollisionResponse* anim;
  //      ICameraSceneNode* camera;

	private:

};




#endif