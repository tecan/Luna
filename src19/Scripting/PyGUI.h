#ifndef PYGUI_H_INCLUDED
#define PYGUI_H_INCLUDED

//rename this to PyVIDEO later

PyObject * Python::PyIrr_ChatBox(PyObject * self,PyObject * args){
    gui::CGUIChatBox* chat = new gui::CGUIChatBox(  guienv, guienv->getRootGUIElement(),
                                                    230, core::rect<int>(20,40,300,500));

    for (int i=0;i < 100;i++){
        chat->addItem(L"(john) Kill that thing...");
        chat->addItem(L"(firestaff) lol", video::SColor(250, 220, 255, 255));
        chat->addItem(L"(juli) that's too big", video::SColor(0, 220, 0, 255));
    };
    //pretty basic needs some work....


    Py_RETURN_NONE;
}

PyObject * Python::PyIrr_2Dimage(PyObject * self,PyObject * args) {//active camera
    #ifdef Image2D
    bImage2d=1;
        //cImage*
        image = new cImage(driver->getTexture("data/sydney.bmp"),
                                    rect<s32>(0,256,512,512),rect<s32>(0,0,512,256));
       // image->SetTransparent(true);
      //  image->SetTransparentColor(SColor(0,255,0,255),driver);
      //  image->SetBilinearFilter(true);

//      draw2DImage ( const video::ITexture * texture,
//const core::rect< s32 > & destRect,
//const core::rect< s32 > & sourceRect,
//const core::rect< s32 > * clipRect = 0,
//const video::SColor *const colors = 0,
//bool useAlphaChannelOfTexture = false
//)

    #endif
        Py_RETURN_NONE;
}

PyObject * Python::PyIrr_aBillBoard(PyObject * self,PyObject * args) {//active camera

	char * tex_name;
	PyArg_ParseTuple(args,"s",&tex_name);

   scene::ISceneManager* smgr = device->getSceneManager();

    scene::IBillboardSceneNode * bill = smgr->addBillboardSceneNode();
    bill->setPosition(core::vector3df(0, 0, 3));
    bill->setMaterialTexture(0, driver->getTexture(tex_name));
    bill->setMaterialFlag(video::EMF_LIGHTING, false);
    bill->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
    bill->setSize(core::dimension2d<f32>(250.0f, 250.0f));
    bill->setScale(core::vector3df(1, 1, 1));

}

PyObject * Python::PyIrr_LoadTexture(PyObject * self,PyObject * args){
	char * tex_name;
	PyArg_ParseTuple(args,"s",&tex_name);
	//printf("hmmm %s", tex_name);
	texture_array.push_back(driver->getTexture(tex_name));
	//The line below is sorta kludgy, but it works.It won't hold up if you remove a texture
	//from the array though,so watch your step, kid. I'll leave it to you to come up with
	//a more intuitive method of storing the textures
	return Py_BuildValue("l",texture_array.size() - 1);

	// need a texture free function
};

PyObject * Python::PyIrr_SetTexture(PyObject * self,PyObject * args){
	s32 tex_id,node_id;
	PyArg_ParseTuple(args,"II",&node_id,&tex_id); //This is your new best friend, seriously
	/*Quite similar to the scanf family of functions, don't you think? It take a format
	string and some input data, and analyzes the input data and gives you the result
	in a manner specified by the format string*/
	ISceneNode * node = smgr->getSceneNodeFromId(node_id);
	printf("%i",node_id);
	printf("%i",tex_id);
	if(node != NULL)
	{
		node->setMaterialTexture(0,texture_array[tex_id]);
	};
	/*This line returns a value of Py_None, which is more or less the same thing as a
	function with a return type of void in C++, in other words, no output values */
	return Py_BuildValue("");
};


PyObject * Python::PyIrr_DrawText(PyObject * self,PyObject * args){

IGUIFont * default_font;
	//Must make this useful someday, not today
	char * message;
	s32 x,y,x1,y1;
	PyArg_ParseTuple(args,"sllll",&message,&x,&y,&x1,&y1); //may only need x,y when using ft2
	//The next three lines more or less give the procedure from converting a string of
	//type char* to wchar_t*...generally this is pretty useful in Irrlicht,so note well
//	int len = strlen(message) + 1;
//	wchar_t * conv_message = new wchar_t[len];
	///mbstowcs(0,conv_message,len,message,_TRUNCATE);

	//guienv->addStaticText(conv_message,rect<s32>(x,y,x1,y1),SColor(255,255,255,255));
//
//	delete [] conv_message;

//	guienv->addStaticText(L"sample text here!",rect<s32>(10,10,260,22), true);

	return Py_BuildValue("");



//
//	    CGUITTFont *font2;
//    CGUITTFace face;
//        font2 = new CGUITTFont(gui);
//    font2->attach(&face,24); // scale this number with the screen
//    font2->AntiAlias=1;

};


PyObject * Python::PyIrr_addHUD(PyObject * self,PyObject * args) //active camera
{
    #ifdef HUD
    int state, value;
    char * loadFile;
    PyArg_ParseTuple(args,"sf",&state,&value);
    enum states {openFile=0,Position,Rotation,Play,Pause};
  int istate =  states(state);

    switch (istate){
        case openFile:
                HUDENABLED=true;
                CHUD2->RegisterDevice(device);
                CHUD2->LoadHUD("data/HUD.xml");
            return Py_BuildValue("l",CHUD2);
        break;
        case 1:
                    break;
//        case 2:
}
    #endif

return Py_BuildValue("");
 }

/// GUI
PyObject * Python::PyIrr_addVideo(PyObject * self,PyObject * args){

vector3df loc;
char * videoFile;
PyArg_ParseTuple(args,"sfff",&videoFile,&loc.X,&loc.Y,&loc.Z);
        #ifdef VIDEO
        vidmaster = new CVideoMaster(device, true, 1);
        ITexture* cubeDiffuse = vidmaster->addVideoClip(videoFile, "TV", ESM_NONE, true);
        IMeshSceneNode *TV = smgr->addCubeSceneNode(50);
        TV->setScale(vector3df(1.0f, 1.0f, 0.001f));
        ///rotation ? perhaps hud /widget instance
        // Set video texture as diffuse
        TV->setMaterialTexture(0, cubeDiffuse);
        TV->setMaterialFlag(EMF_LIGHTING, false);
        //vidmaster->addVideoClip("./media/YUVTest.ogg", "YUV", dimension2du(128,128), true);
        return Py_BuildValue("l",vidmaster);
        #endif

    //OLD VideoPlayer based on theora or maybe this is the mplayer one
        //cVideoPlayer* videoPlayer;
        //videoPlayer = new cVideoPlayer(driver, device->getTimer(), "./media/123.avi",800,600);
        //videoPlayer->setLoop(false);
        //   videoPlayer->play();

return Py_BuildValue("");
}


PyObject * Python::PyIrr_tesselateImage(PyObject * self,PyObject * args){
// maybe try to stick this into a vector renderstack for main loop to allow more than one instance
//vector3df loc;
//PyArg_ParseTuple(args,"fff",&loc.X,&loc.Y,&loc.Z);
#ifdef TESSIMAGE
btesimage=1;
tesImage = new TesselatedImage(device, "media/fireball.bmp", vector3df(-600,0,500), vector3df(500, 550, 1000), vector3df(-130,50,100), 45, 1500, 10);
tesImage->startAnimation();
return Py_BuildValue("l",tesImage);
#endif
return Py_BuildValue("");
}
#endif // PYGUI_H_INCLUDED
