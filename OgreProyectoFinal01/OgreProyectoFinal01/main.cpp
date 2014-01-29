#include "Ogre\Ogre.h"
#include "OIS\OIS.h"
#include <iostream>

Ogre::SceneNode* eje;
Ogre::SceneNode* padreDI;
Ogre::SceneNode* padreDS;
Ogre::SceneNode* padreII;
Ogre::SceneNode* padreIS;
Ogre::SceneNode* _nodeRuedaSimple0; 
Ogre::SceneNode* _nodeRuedaSimple1; 
Ogre::SceneNode* _nodeRuedaSimple2; 
Ogre::SceneNode* _nodeRuedaSimple3; 
Ogre::SceneNode* _nodeRuedaSimple00; 
Ogre::SceneNode* _nodeRuedaSimple11; 
Ogre::SceneNode* _nodeRuedaSimple22; 
Ogre::SceneNode* _nodeRuedaSimple33; 
Ogre::SceneNode* _nodeChasisCarro; 
int desplazamiento = 0;
int i = 0;
class AppFrameListener : public Ogre::FrameListener
{

private:

	Ogre::SceneManager* _sManager;
	OIS::InputManager* _InputManager;
	OIS::Keyboard* _Keyboard;
	OIS::Mouse* _Mouse;
	Ogre::Camera* _Cam;
	float _movementspeed;

public:

		AppFrameListener(Ogre::RenderWindow* win, Ogre::Camera* cam, Ogre::SceneManager* _sceneManager){

		OIS::ParamList parameters;
		unsigned int windowHandle = 0;
		std::ostringstream windowHandleString;
		win->getCustomAttribute("WINDOW", &windowHandle);
		windowHandleString << windowHandle;
		parameters.insert(std::make_pair("WINDOW", windowHandleString.str()));
		_InputManager = OIS::InputManager::createInputSystem(parameters);
		_Keyboard = static_cast<OIS::Keyboard*>(_InputManager->createInputObject( OIS::OISKeyboard, false ));
		_Mouse = static_cast<OIS::Mouse*>(_InputManager->createInputObject( OIS::OISMouse, false ));
		_sManager = _sceneManager;
		_Cam = cam;
		_movementspeed = 25;


		}


	~AppFrameListener(){
		_InputManager->destroyInputObject(_Keyboard);
		_InputManager->destroyInputObject(_Mouse);
		OIS::InputManager::destroyInputSystem(_InputManager);
	}

	bool intersection(float distancia, float diametro){

		if (distancia > diametro) 
			return false;
		else
			return true;


	}

	std::string convertInt(int number){
		std::stringstream ss;//create a stringstream
		ss << number;//add number to the stream
		return ss.str();//return a string with the contents of the stream
	}

	bool frameStarted(const Ogre::FrameEvent& evt){
		
		Ogre::Vector3 translate(0,0,0);
		
		_Keyboard->capture();
			

		if(_Keyboard->isKeyDown(OIS::KC_ESCAPE)){
			return false;
		}


		if(_Keyboard->isKeyDown(OIS::KC_W)){
			translate += Ogre::Vector3(0,0,-1);
		}

		if(_Keyboard->isKeyDown(OIS::KC_S)){
			translate += Ogre::Vector3(0,0,1);
		}

		if(_Keyboard->isKeyDown(OIS::KC_A)){
			translate += Ogre::Vector3(-1,0,0);
		}

		if(_Keyboard->isKeyDown(OIS::KC_D)){
			translate += Ogre::Vector3(1,0,0);
		}

		/* Agregadas por mi */

		if(_Keyboard->isKeyDown(OIS::KC_UP)){
			_nodeRuedaSimple0->pitch(Ogre::Radian(-10));
			_nodeRuedaSimple1->pitch(Ogre::Radian(-10));
			_nodeRuedaSimple2->pitch(Ogre::Radian(-10));
			_nodeRuedaSimple3->pitch(Ogre::Radian(-10));

			_nodeRuedaSimple0->translate(0,0,5);
			_nodeRuedaSimple1->translate(0,0,5);
			_nodeRuedaSimple2->translate(0,0,5);
			_nodeRuedaSimple3->translate(0,0,5);
			_nodeChasisCarro->translate(0,0,5);
			eje->translate(0.0,0.0,5.0);
			desplazamiento += 5;

			if (desplazamiento >= 6500 && i<25) {
				eje->scale(1.1,1.1,1.1);
				i++;
			}
		}

		if(_Keyboard->isKeyDown(OIS::KC_RIGHT)){
/*			_nodeRuedaSimple00->yaw(Ogre::Radian(5));
			_nodeRuedaSimple11->yaw(Ogre::Radian(5));
			_nodeRuedaSimple22->yaw(Ogre::Radian(5));
			_nodeRuedaSimple33->yaw(Ogre::Radian(5));*/

			_nodeRuedaSimple0->translate(-3,0,0);
			_nodeRuedaSimple1->translate(-3,0,0);
			_nodeRuedaSimple2->translate(-3,0,0);
			_nodeRuedaSimple3->translate(-3,0,0);
			_nodeChasisCarro->translate(-3,0,0);
		}

		if(_Keyboard->isKeyDown(OIS::KC_LEFT)){
		/*	_nodeRuedaSimple00->yaw(Ogre::Radian(-5));
			_nodeRuedaSimple11->yaw(Ogre::Radian(-5));
			_nodeRuedaSimple22->yaw(Ogre::Radian(-5));
			_nodeRuedaSimple33->yaw(Ogre::Radian(-5)); */

			_nodeRuedaSimple0->translate(3,0,0);
			_nodeRuedaSimple1->translate(3,0,0);
			_nodeRuedaSimple2->translate(3,0,0);
			_nodeRuedaSimple3->translate(3,0,0);
			_nodeChasisCarro->translate(3,0,0);
		}


		_Cam->moveRelative(translate*evt.timeSinceLastFrame * 600);
		

		_Mouse->capture();
		float rotX = _Mouse->getMouseState().X.rel * evt.timeSinceLastFrame* -1;
		float rotY = _Mouse->getMouseState().Y.rel * evt.timeSinceLastFrame * -1;
		_Cam->yaw(Ogre::Radian(rotX));
		_Cam->pitch(Ogre::Radian(rotY));


		return true;
	}
	

	bool frameEnded(const Ogre::FrameEvent& evt){
		//std::cout << "Frame ended" << std::endl;
		return true;
	}

	bool frameRenderingQueued(const Ogre::FrameEvent& evt){
		//std::cout << "Frame queued" << std::endl;
		return true;
	}


};

class cAplicacion {

	private:
		Ogre::SceneManager* _sceneManager;
		Ogre::Root* _root;
		AppFrameListener* _listener;
		Ogre::Camera* camera;
		bool _keepRunning;
		

		public:

			// Constructor de la clase
			cAplicacion(){
				_sceneManager = NULL;
				_root = NULL;
				_listener = NULL;
			}

			~cAplicacion(){
				delete _root;
				delete _listener;
			}

			// Funcion que permite cargar los recursos de OGRE esto simplifica tener que cargarlos uno por uno
			void loadResources(){
				Ogre::ConfigFile cf;
				cf.load("resources_d.cfg");

				Ogre::ConfigFile::SectionIterator sectionIter = cf.getSectionIterator();
				Ogre::String sectionName, typeName, dataname;
				
				while (sectionIter.hasMoreElements()){
					sectionName = sectionIter.peekNextKey();
					Ogre::ConfigFile::SettingsMultiMap *settings = sectionIter.getNext();
					Ogre::ConfigFile::SettingsMultiMap::iterator i;

					for (i = settings->begin(); i != settings->end(); ++i){
						typeName = i->first;
						dataname = i->second;
						Ogre::ResourceGroupManager::getSingleton().addResourceLocation(dataname, typeName, sectionName);
					}
				
				}

				Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
			}


			// funcion que configura la camara
			void createCamera(Ogre::RenderWindow* window){
				camera = _sceneManager->createCamera("Camera");
				camera->setPosition(Ogre::Vector3(0,60,-100));
				camera->lookAt(Ogre::Vector3(0,0,50));
				camera->setNearClipDistance(5);

				Ogre::Viewport* viewport = window->addViewport(camera);
				viewport->setBackgroundColour(Ogre::ColourValue(0.0,0.0,0.0));
				camera->setAspectRatio(Ogre::Real(viewport->getActualWidth())/Ogre::Real(viewport->getActualHeight()));

			}

			// funcion donde se coloca lo que se desea desplegar.
			void createScene(){
								

				_sceneManager->setAmbientLight(Ogre::ColourValue(0.2,0.2,0.2));
				_sceneManager->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
				

			
				// LUZ
				

				Ogre::Light* LuzPuntual01 = _sceneManager->createLight("Luz01");
				LuzPuntual01->setType(Ogre::Light::LT_DIRECTIONAL);
				LuzPuntual01->setDiffuseColour(1.0,1.0,1.0);
				LuzPuntual01->setDirection(Ogre::Vector3( 1, -1, -1 ));

				Ogre::Light* LuzPuntual02 = _sceneManager->createLight("Luz02");
				LuzPuntual02->setType(Ogre::Light::LT_DIRECTIONAL);
				LuzPuntual02->setDiffuseColour(1.0,1.0,1.0);
				LuzPuntual02->setDirection(Ogre::Vector3( -1, -1, -1 ));



				//Chasis Carro
				_nodeChasisCarro = _sceneManager->createSceneNode("ChasisCarro");
				_sceneManager->getRootSceneNode()->addChild(_nodeChasisCarro);
				
				Ogre::Entity* _entChasisCarro = _sceneManager->createEntity("ChasisCarro", "chasisCarro.mesh");
				_nodeChasisCarro->attachObject(_entChasisCarro);



				/* Ruedas Izquierdas */
				_nodeRuedaSimple0 = _sceneManager->createSceneNode("RuedaSimple0");
				_sceneManager->getRootSceneNode()->addChild(_nodeRuedaSimple0);
			//	_nodeRuedaSimple00 = _nodeRuedaSimple0->createChildSceneNode("RuedaSimple00");
			//	_sceneManager->getRootSceneNode()->addChild(_nodeRuedaSimple00);

				Ogre::Entity* _entRuedaSimple0 = _sceneManager->createEntity("RuedaSimple0", "RuedaDetallada.mesh");
				_nodeRuedaSimple0->attachObject(_entRuedaSimple0);
			//	_nodeRuedaSimple00->attachObject(_entRuedaSimple0);

				_nodeRuedaSimple0->translate(9,3,5);


				_nodeRuedaSimple2 = _sceneManager->createSceneNode("RuedaSimple2");
				_sceneManager->getRootSceneNode()->addChild(_nodeRuedaSimple2);
			//	_nodeRuedaSimple22 = _nodeRuedaSimple2->createChildSceneNode("RuedaSimple22");
			//	_sceneManager->getRootSceneNode()->addChild(_nodeRuedaSimple22);
				
				Ogre::Entity* _entRuedaSimple2 = _sceneManager->createEntity("RuedaSimple2", "RuedaDetallada.mesh");
				_nodeRuedaSimple2->attachObject(_entRuedaSimple2);
			//	_nodeRuedaSimple22->attachObject(_entRuedaSimple2);

				_nodeRuedaSimple2->translate(9,3,-5);

				/* Ruedas Derechas */
				_nodeRuedaSimple1 = _sceneManager->createSceneNode("RuedaSimple1");
				_sceneManager->getRootSceneNode()->addChild(_nodeRuedaSimple1);
			//	_nodeRuedaSimple11 = _nodeRuedaSimple1->createChildSceneNode("RuedaSimple11");
			//	_sceneManager->getRootSceneNode()->addChild(_nodeRuedaSimple11);

				Ogre::Entity* _entRuedaSimple1 = _sceneManager->createEntity("RuedaSimple1", "RuedaDetallada.mesh");
				_nodeRuedaSimple1->attachObject(_entRuedaSimple1);
			//	_nodeRuedaSimple11->attachObject(_entRuedaSimple1);

				_nodeRuedaSimple1->translate(-7,3,5);


				_nodeRuedaSimple3 = _sceneManager->createSceneNode("RuedaSimple3");
				_sceneManager->getRootSceneNode()->addChild(_nodeRuedaSimple3);
			//	_nodeRuedaSimple33 = _nodeRuedaSimple3->createChildSceneNode("RuedaSimple33");
				//_sceneManager->getRootSceneNode()->addChild(_nodeRuedaSimple33);
				
				Ogre::Entity* _entRuedaSimple3 = _sceneManager->createEntity("RuedaSimple3", "RuedaDetallada.mesh");
				_nodeRuedaSimple3->attachObject(_entRuedaSimple3);
				//_nodeRuedaSimple33->attachObject(_entRuedaSimple3);

				_nodeRuedaSimple3->translate(-7,3,-5);


				/* ALA DERECHA INFERIOR

				Se crea el nodo padre de la nave llamado eje */
				eje = _sceneManager->getRootSceneNode()->createChildSceneNode("eje");

				padreDI = eje->createChildSceneNode("padreDI");

				Ogre::ManualObject* alad = _sceneManager->createManualObject("alad"); 

				alad->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_TRIANGLE_FAN);
				alad->colour(Ogre::ColourValue(0.0, 0.5, 0.0, 0.0));

				alad->position(4.0, -0.5, 0.0);  
				alad->position(15.0, -0.5, 0.0); 
				alad->position(15.0, 0.0, 0.0);
				alad->position(5.0, 0.0, 0.0);

				alad->index(0);
				alad->index(1);
				alad->index(2);
				alad->index(3);
				alad->index(0);

				alad->end();
				padreDI->attachObject(alad);


				Ogre::ManualObject* alad2 = _sceneManager->createManualObject("alad2");
				alad2->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_TRIANGLE_FAN);
				alad2->colour(Ogre::ColourValue(0.0, 0.6, 0.0, 0.0));
	
				alad2->position(5.0,  0.0, 0.0);  
				alad2->position(15.0,  0.0, 0.0); 
				alad2->position(14.0, 0.0, -3.0);
				alad2->position(5.0,  0.0, -4.0);

				alad2->index(0);
				alad2->index(1);
				alad2->index(2);
				alad2->index(3);
				alad2->index(0);

				alad2->end();
				padreDI->attachObject(alad2);

	
				/* ALA DERECHA SUPERIOR */

				padreDS = eje->createChildSceneNode("padreDS");

				Ogre::ManualObject* aladS = _sceneManager->createManualObject("aladS");
				aladS->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_TRIANGLE_FAN);
				aladS->colour(Ogre::ColourValue(0.0, 0.5, 0.0, 0.0));

				aladS->position(4.0, 0.0, 0.0);  
				aladS->position(15.0, 0.0, 0.0); 
				aladS->position(15.0, 0.5, 0.0);
				aladS->position(5.0, 0.5, 0.0);

				aladS->index(0);
				aladS->index(1);
				aladS->index(2);
				aladS->index(3);
				aladS->index(0);

				aladS->end();
				padreDS->attachObject(aladS);


				Ogre::ManualObject* aladS2 = _sceneManager->createManualObject("aladS2");
				aladS2->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_TRIANGLE_FAN);
				aladS2->colour(Ogre::ColourValue(0.0, 0.6, 0.0, 0.0));
	
				aladS2->position(5.0,  0.5, 0.0);  
				aladS2->position(15.0,  0.5, 0.0); 
				aladS2->position(14.0, 0.5, -3.0);
				aladS2->position(5.0,  0.5, -3.0);

				aladS2->index(0);
				aladS2->index(1);
				aladS2->index(2);
				aladS2->index(3);
				aladS2->index(0);

				aladS2->end();
				padreDS->attachObject(aladS2);



			/* ALA IZQUIERDA INFERIOR */

				padreII = eje->createChildSceneNode("padreII");

				Ogre::ManualObject* aladI = _sceneManager->createManualObject("aladI");
				aladI->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_TRIANGLE_FAN);
				aladI->colour(Ogre::ColourValue(0.0, 0.5, 0.0, 0.0));

				aladI->position(-15.0, -0.5, 0.0);
				aladI->position(5.0, -0.5, 0.0);		
				aladI->position(-5.0, 0.0, 0.0);  
				aladI->position(-15.0, 0.0, 0.0); 


				aladI->index(0);
				aladI->index(1);
				aladI->index(2);
				aladI->index(3);
				aladI->index(0);

				aladI->end();
				padreII->attachObject(aladI);


				Ogre::ManualObject* aladI2 = _sceneManager->createManualObject("aladI2");
				aladI2->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_TRIANGLE_FAN);
				aladI2->colour(Ogre::ColourValue(0.0, 0.6, 0.0, 0.0));
	
				aladI2->position(-15.0,  0.0, 0.0); 
				aladI2->position(-5.0,  0.0, 0.0);  
				aladI2->position(-5.0,  0.0, -4.0);
				aladI2->position(-14.0, 0.0, -3.0);



				aladI2->index(0);
				aladI2->index(1);
				aladI2->index(2);
				aladI2->index(3);
				aladI2->index(0);

				aladI2->end();
				padreII->attachObject(aladI2);


			/* ALA IZQUIERDA SUPERIOR */

				padreIS = eje->createChildSceneNode("padreIS");

				Ogre::ManualObject* aladIS = _sceneManager->createManualObject("aladIS");
				aladIS->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_TRIANGLE_FAN);
				aladIS->colour(Ogre::ColourValue(0.0, 0.5, 0.0, 0.0));

				aladIS->position(-15.0, 0.0, 0.0);
				aladIS->position(5.0, 0.0, 0.0);		
				aladIS->position(-5.0, 0.5, 0.0);  
				aladIS->position(-15.0, 0.5, 0.0); 


				aladIS->index(0);
				aladIS->index(1);
				aladIS->index(2);
				aladIS->index(3);
				aladIS->index(0);

				aladIS->end();
				padreIS->attachObject(aladIS);


				Ogre::ManualObject* aladIS2 = _sceneManager->createManualObject("aladIS2");
				aladIS2->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_TRIANGLE_FAN);
				aladIS2->colour(Ogre::ColourValue(0.0, 0.6, 0.0, 0.0));
	
				aladIS2->position(-15.0,  0.5, 0.0); 
				aladIS2->position(-5.0,  0.5, 0.0);  
				aladIS2->position(-5.0,  0.5, -3.0);
				aladIS2->position(-14.0, 0.5, -2.0);

				aladIS2->index(0);
				aladIS2->index(1);
				aladIS2->index(2);
				aladIS2->index(3);
				aladIS2->index(0);

				aladIS2->end();
				padreIS->attachObject(aladIS2);

				/* Rotaciones de las alas */
				eje->scale(2.5,2.5,2.5);
				eje->translate(0,5,0);
				eje->yaw(Ogre::Degree(180));

				/* Trasladar las alas */
				padreIS->translate(4,0,0);
				padreDS->translate(-4,0,0);
				padreDI->translate(-4,0,0);
				padreII->translate(4,0,0); 

				eje->scale(0.1,0.1,0.1);

				//BordePista
				Ogre::SceneNode* _nodeBPista = _sceneManager->createSceneNode("BordePista");
				_sceneManager->getRootSceneNode()->addChild(_nodeBPista);
				
				Ogre::Entity* _entBPista = _sceneManager->createEntity("BordePista", "bordePista02.mesh");
				_nodeBPista->attachObject(_entBPista);
				_entBPista->setMaterialName("Examples/pared");


				//PisoObstaculo
				Ogre::SceneNode* _nodePObstaculo = _sceneManager->createSceneNode("PistaObstaculo");
				_sceneManager->getRootSceneNode()->addChild(_nodePObstaculo);
				
				Ogre::Entity* _entPObstaculo = _sceneManager->createEntity("PistaObstaculo", "pisoObstaculo02.mesh");
				_nodePObstaculo->attachObject(_entPObstaculo);

				//PisoNOObstaculo
				Ogre::SceneNode* _nodePNObstaculo = _sceneManager->createSceneNode("PistaNoObstaculo");
				_sceneManager->getRootSceneNode()->addChild(_nodePNObstaculo);
				
				Ogre::Entity* _entPNOObstaculo = _sceneManager->createEntity("PistaNoObstaculo", "pisoNoObstaculo02.mesh");
				_nodePNObstaculo->attachObject(_entPNOObstaculo);
				_entPNOObstaculo->setMaterialName("Examples/piso");


				//PosterInicioFinal
				Ogre::SceneNode* _nodePoster = _sceneManager->createSceneNode("PosterInicioFinal");
				_sceneManager->getRootSceneNode()->addChild(_nodePoster);
				
				Ogre::Entity* _entPoster = _sceneManager->createEntity("PosterInicioFinal", "posterInicioFinal02.mesh");
				_nodePoster->attachObject(_entPoster);

				
				//BanderaInicial
				Ogre::SceneNode* _nodeBInicial = _sceneManager->createSceneNode("BanderaInicial");
				_sceneManager->getRootSceneNode()->addChild(_nodeBInicial);
				
				Ogre::Entity* _entBanderaI = _sceneManager->createEntity("BanderaInicial", "banderaInicial02.mesh");
				_nodeBInicial->attachObject(_entBanderaI);

				//BanderaFinal
				Ogre::SceneNode* _nodeBFinal = _sceneManager->createSceneNode("BanderaFinal");
				_sceneManager->getRootSceneNode()->addChild(_nodeBFinal);
				
				Ogre::Entity* _entBanderaF = _sceneManager->createEntity("BanderaFinal", "banderaFinal.mesh");
				_nodeBFinal->attachObject(_entBanderaF);

				_sceneManager->setSkyDome(true,"Examples/cielo",5,8);


			}


			void renderOneFrame(){
				Ogre::WindowEventUtilities::messagePump();
				_keepRunning = _root->renderOneFrame();
			}

			bool keepRunning(){
				return _keepRunning;
			}

			//Funcion que inicializa la aplicacion
			int startup(){
				_root = new Ogre::Root("plugins_d.cfg");
				
				//Muestra la ventana inicial...
				
				//if(!_root->showConfigDialog()){
				//	return -1;
				//}


				// Evitan cargar la ventana inicial...
				Ogre::RenderSystem* _rs = _root->getRenderSystemByName("Direct3D9 Rendering Subsystem");
				// or use "OpenGL Rendering Subsystem"
				_root->setRenderSystem(_rs);
				_rs->setConfigOption("Full Screen", "No");
				_rs->setConfigOption("Video Mode", "800 x 600 @ 32-bit colour");
				_rs->setConfigOption("FSAA", "0");
				_rs->setConfigOption("Floating-point mode", "Fastest");
				_rs->setConfigOption("Use Multihead", "Auto");
				_rs->setConfigOption("VSync", "No");
				_rs->setConfigOption("VSync Interval", "1");


			
				Ogre::RenderWindow* window = _root->initialise(true,"Ventana de Ogre3D");
				_sceneManager = _root->createSceneManager(Ogre::ST_GENERIC);

				
				loadResources();
				createScene();
				createCamera(window);



				_listener = new AppFrameListener(window,camera,_sceneManager);
				_root->addFrameListener(_listener);				


				//_root->startRendering();
				return 0;

				
			}


};




int main (void)
{
	cAplicacion app;
	app.startup();

	while(app.keepRunning()){
		app.renderOneFrame();
	}

	return 0;
		
}