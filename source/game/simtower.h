#ifndef OSS_CLASSIC_SIMTOWER_H
#define OSS_CLASSIC_SIMTOWER_H

#include "external.h"

#include "application.h"


namespace OSS {
	namespace Game {
		class SimTower : public Singleton<SimTower, Object> {
		private:
			//Resources
			class Resource : public Object {
			public:
				unsigned short id;
				unsigned short type;
				unsigned int length;
				void * data;
				std::string getName();
				std::string getDumpName();
			};
			
			typedef std::vector< Pointer<Resource> > ResourceVector;
			ResourceVector resources;
			Resource * getResource(unsigned short type, unsigned short id);
			
			//Resource Types
			enum {
				kBitmapResource			= 0x2,
				kPercellBitmapResource	= 0x7F02,
				kMenuResource			= 0x4,
				kDialogBoxResource		= 0x5,
				kStringTableResource	= 0x6,
				kSoundResource			= 0x7F0A
			};
			
			//Resource Names
			typedef struct {
				unsigned short resourceID;
				std::string name;
			} ResourceName;
			static ResourceName bitmapResourceNames[];
			static ResourceName soundResourceNames[];
			static std::string getNameForResource(Resource * resource);
			
			//Some default colors for later use
		private:
			static const color3d skyThroughWindow[];
			
		public:
			const Pointer<Application> application;
			SimTower(Application * application) : application(application) {}
			
			//Loads the resources of the SimTower executable
			void loadResources();
			
			//Extracts various components from the loaded resources
			void extractAll();
			void extractTextures();
			void extractSounds();
			
			//Creates one or more textures from the given information
			void postprocessTexture(std::string textureName, const void * buffer, unsigned int bufferLength);
			void applyReplacementPalette(unsigned short id);
			void spawnSkyTextures(std::string textureName, ILuint image);
			void spawnCloudTextures(std::string textureName, ILuint image);
			void spawnLobbyTextures(std::string textureName, ILuint image);
			void spawnElevatorTextures(std::string textureName, ILuint image);
			void spawnFloordigitTextures(std::string textureName, ILuint image);
			
			//Dumping textures to disk for debugging purposes
			std::string getDumpPath(std::string type, std::string name);
			void dumpTexture(Engine::Texture * texture);
			void dumpSound(std::string name, const void * buffer, unsigned int bufferLength);
		};
	}
}


#endif
