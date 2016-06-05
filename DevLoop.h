#ifndef NDEBUG // if debug build then do this one
#define PostProcesss

if ( !device->run() ) return 0;
    guienv->clear();
    smgr->clear();


    #define PYTHON
    #ifdef PYTHON
    //Python
        Python::registerIrrDevice(this,*device,m_cInGameEvents);
        Py_Initialize();            //Initialize Python
        Python::init_irr();         //Initialize our module
        Python::ExecuteScript("./functions-list.pys"); //Using our handy dandy script execution function
         //Python::PyIrr_LoadVehicle(m_cVehicle);
        //Python::PyIrr_addTerrain("1");
    #endif

//camera = smgr->addCameraSceneNodeFPS(0, 100, .1f, -1, keyMap, 8);
	//smgr->addCameraSceneNodeFPS();
    #ifdef PostProcess
     //PostProcessing
        IPostProc* ppRenderer = new CRendererPostProc( smgr, dimension2du( 1024, 512 ),
                                                    true, true, SColor( 255u, 100u, 101u, 140u ) );
        CEffectPostProc* ppBlurDOF   = new CEffectPostProc( ppRenderer, dimension2du( 1024, 512 ), PP_BLURDOF );
        CEffectPostProc* ppBlur          = new CEffectPostProc( ppRenderer, dimension2du( 1024, 512 ), PP_BLUR, 0.00081f );
        ppBlur->setQuality( PPQ_GOOD );
    #endif



    u32 then = device->getTimer()->getTime();
    int lastFPS;



/**
/////////////////////////////////////
//      DEVLOOP  //////////////////
///////////////////////////////////
**/

//    //    if (btrailNode){
//       //     rt->
//  //  }
////    btrailNode=1
//	video::ITexture* tex = driver->getTexture( "media/portal7.bmp" );
//    rt = new RibbonTrailSceneNode( device, camera, -1 );
////	rt->setPosition( core::vector3df( 0, -10, 300 ) );
//    rt->setMaterialTexture( 0, tex );
//   rt->setPoint1( core::vector3df(  50, 0, 0 ) );
//    rt->setPoint2( core::vector3df( -50, 0, 0 ) );
//    rt->setMaxDistance( 10 );
//	rt->setMaxQuads( 5000 );
//    rt->setStartingAlpha( 100 );
//	rt->setShowDebug( true );
//	rt->setEnabled( true );
device->getCursorControl()->setVisible(true);

    while ( device->run() && !this->m_cInGameEvents.Quit ) //&& !this->m_cInGameEvents.Quit
    {
        const u32 now = device->getTimer()->getTime();
		frameDeltaTime = (f32)(now - then) / 1000.f; // Time in seconds
		then = now;



        Python::PreRender();
        ///todo check for empty or missing files or impliment the using command
        // loop for key checking and loop for game  only execute script if there was an event
        // may need to put the loop where the checkkeystates was (after endscene)
    //            Python::ExecuteScript("./media/Lmain.pys");

        driver->beginScene ( true, true, SColor ( 0, 0, 0, 0 ) );
        Python::render();
        smgr->drawAll();

        #ifdef PostProcess
            ppBlur->render( NULL );
            ppBlurDOF->render( NULL );
        #endif

        guienv->drawAll();
 //       rt->render();
        Python::preEnd();
        driver->endScene();
    //    Python::CheckKeyStates();        //CheckKeyStates(); obsolete python does it above
                    Python::ExecuteScript("./RACING/racer/main.pys");
//        Python::mainLoop();


        int fps = driver->getFPS();
		if (lastFPS != fps)
		{
			core::stringw tmp(L"Luna Engine [");
			tmp += driver->getName();
			tmp += L"] fps: ";
			tmp += fps;

			device->setWindowCaption(tmp.c_str());
			lastFPS = fps;
		}
     //  device->sleep(5);
    }


//#ifdef HUD
// //     delete vidmaster;
//#endif
//    #ifdef BOIDS
//     delete flock;
//    #endif
//
//    #ifdef PostProcess
//	 delete ppBlurDOF;
//	 delete ppBlur;
//	 delete ppRenderer;
//    #endif
//
//	#ifdef ATMOSPHERE
//     delete atmo;
//    #endif
//
//	#ifdef ReflectiveWater
//	 delete water;
//	#endif
//
//	#ifdef RAG
//		for (std::vector<RagDoll*>::iterator it = v_RagDolls.begin(); it != v_RagDolls.end(); ++it)
//            (*it)->~RagDoll();
//	#endif
//
//	//delete CHUD2;
//	//delete m_cVehicle;
//
//	#ifdef COMPASS
//	 delete Compass1;
//	#endif
//
//	#ifdef FLAG     // should be the flagmanager
//	delete irrFlagNode;
//	#endif
//
//	#ifdef FLAG2     // should be the flagmanager
//	delete flag;
//	#endif

	#ifdef PYTHON
     Py_Finalize();
    #endif

    #ifdef DSOUND
		manager->releaseAllSources();
		manager->shutDown();
        cAudio::destroyAudioManager(manager);
    #endif
    #ifdef PHYSICS
clearBodies();
#endif

#ifdef SPARKA
	cout << "\nSPARK FACTORY BEFORE DESTRUCTION :" << endl;
	SPKFactory::getInstance().traceAll();
	SPKFactory::getInstance().destroyAll();
	cout << "\nSPARK FACTORY AFTER DESTRUCTION :" << endl;
	SPKFactory::getInstance().traceAll();
	device->drop();
#endif

//	delete videoPlayer;
#endif

/*
//		// I'm just using a basic cube scene node for the glass pane, "scaled to flatness".
//		ISceneNode* GlassPane = smgr->addCubeSceneNode();
//		GlassPane->setScale(vector3df(100,150,1));
//		GlassPane->setPosition(core::vector3df(0,0,0));
//		GlassPane->setRotation(vector3df(0,60,0));
//
//		// Here I make a RTT for the refraction, you can use a higher res one if you want,
//		// I chose 512^2 for compatibility. I also load the normalmap.
//		ITexture* RTTTex = driver->addRenderTargetTexture(dimension2du(512,512));
//		ITexture* NormMap = driver->getTexture("shaders/glass-bubble/media/NormalMap.png");
//
//		GlassPane->setMaterialTexture(0, RTTTex);
//		GlassPane->setMaterialTexture(1, NormMap);
//
//		io::path vshader = "shaders/glass-bubble/GlassV.glsl";
//        io::path pshader = "shaders/glass-bubble/GlassP.glsl";
//
//		video::IGPUProgrammingServices* gpu = driver->getGPUProgrammingServices();
//
//		// I create the shader material for the glass pane.
//		s32 GlassMat = gpu->addHighLevelShaderMaterialFromFiles(vshader,"main",EVST_VS_2_0,pshader,"main",EPST_PS_2_0,0);
//
//		GlassPane->setMaterialType(E_MATERIAL_TYPE(GlassMat));
*/