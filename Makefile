NAME = indie_studio
RM = rm -f
CC = g++

ECS = ecs
ENTITY = $(ECS)/entity
SYSTEMS = $(ECS)/systems
INPUT_SYSTEM = $(SYSTEMS)/inputSystem
PHYSIC_SYSTEM = $(SYSTEMS)/physicSystem
EVENT_HANDLER = eventHandler
EVENT_MANAGER = eventManager
EXCEPTION = exception
KEYCOLLECTION = keyCollection
SAVECOLLECTION = saveCollection
ENGINE = engine
MODELS = model
GAME_MODEL = $(MODELS)/gameModel
IA_SYSTEM = $(SYSTEMS)/bindingSystem
VIEW_SYSTEM = $(SYSTEMS)/graphicSystem
DAMAGE_SYSTEM = $(SYSTEMS)/damageSystem
ATTACK_SYSTEM = $(SYSTEMS)/attackSystem
ANIMATION_SYSTEM = $(SYSTEMS)/animationSystem
HANDLER_SYSTEM	= $(SYSTEMS)/handlerEntitySystem
INVENTORY_SYSTEM	= $(SYSTEMS)/inventorySystem
DROP_SYSTEM	= $(SYSTEMS)/dropSystem
GRAPHIC_MENU = menu
EVENTM	= ./eventManager/
LIBCEGUIDIR	= ./cegui
MENUMODEL	= ./model/menuModel/
AUDIO		= ./audio
DIRLOADER	= ./loader
DIR_SPAWNER	= ./spawner
DIR_SPAWN_SYSTEM	= $(SYSTEMS)/spawnSystem
DIR_SCORE_SYSTEM	= $(SYSTEMS)/scoreSystem


ENTITY_INCLUDE = $(ENTITY)/include_files
INPUT_SYSTEM_INCLUDE = $(INPUT_SYSTEM)/include_files
EVENT_HANDLER_INCLUDE = $(EVENT_HANDLER)/include_files
EXCEPTION_INCLUDE = $(EXCEPTION)/include_files
KEYCOLLECTION_INCLUDE = $(KEYCOLLECTION)/include_files
COMPONENTS = $(ECS)/component/components
COMPONENT_COLLECTION = $(ECS)/component
PHYSIC_SYSTEM_INCLUDE = $(PHYSIC_SYSTEM)/include_files
ADDONS_SYSTEM = $(SYSTEMS)/include_files
ADDONS_COMPONENT = $(ECS)/component/include_files
ENGINE_INCLUDE = $(ENGINE)/include_files
INCLUDE_MODEL = $(MODELS)/include_files
INCLUDE_GAME_MODEL = $(GAME_MODEL)/include_files
INCLUDE_IA_SYSTEM = $(IA_SYSTEM)/include_files
INCLUDE_LUA_BINDING = ./lib/selene/aux
INCLUDE_LUA_SELENE = ./lib/selene/
INCLUDE_LUA_SELENE_FILES = ./lib/selene/selene
INCLUDE_GRAPHIC	= $(VIEW_SYSTEM)/include_files
INCLUDE_OGRE	= ./install/include/OGRE
INCLUDE_IOS	= ./install/include/IOS
INCLUDE_OVERLAY	= $(INCLUDE_OGRE)/Overlay
INCLUDE_TERRAIN	= $(INCLUDE_OGRE)/Terrain
INCLUDE_OIS	= ./lib/OIS/includes
INCLUDE_SAVE	= $(SAVECOLLECTION)/include_files
INCLUDE_EVENTM	= $(EVENT_MANAGER)/include_files
INCLUDE_GRAPHIC_MENU = $(GRAPHIC_MENU)/include_files
INCLUDE_CEGUI	= ./install/include/cegui-0/CEGUI/
INCLUDE_CEGUIABS	= ./install/include/cegui-0/
INCLUDE_EVENTM	= $(EVENTM)include_files
INCLUDE_MENU	= $(MENUMODEL)include_files
INCLUDE_AUDIO	= audio
INCLUDE_LOADER	= $(DIRLOADER)/include_files
INCLUDE_ATTACK_SYSTEM	= $(ATTACK_SYSTEM)/include_files
INCLUDE_DAMAGE_SYSTEM	= $(DAMAGE_SYSTEM)/include_files
INCLUDE_HANDLER_SYSTEM	= $(HANDLER_SYSTEM)/include_files
INCLUDE_ANIMATION	= $(ANIMATION_SYSTEM)/include_files
INCLUDE_INVENTORY	= $(INVENTORY_SYSTEM)/include_files
INCLUDE_SPAWNER		= $(DIR_SPAWNER)/include_files
INCLUDE_GAME_OVER	= $(DIR_GAME_OVER)/include_files
INCLUDE_DROP_SYSTEM	= $(DROP_SYSTEM)/include_files
INCLUDE_SPAWN_SYSTEM	= $(DIR_SPAWN_SYSTEM)/include_files
INCLUDE_SCORE_SYSTEM	= $(DIR_SCORE_SYSTEM)/include_files

INCLUDES =	-I $(EVENT_HANDLER_INCLUDE) \
		-I $(ENTITY_INCLUDE) \
		-I $(INPUT_SYSTEM_INCLUDE) \
		-I $(EXCEPTION_INCLUDE) \
		-I $(KEYCOLLECTION_INCLUDE) \
		-I $(COMPONENTS) \
		-I $(COMPONENT_COLLECTION) \
		-I $(PHYSIC_SYSTEM_INCLUDE) \
		-I $(ADDONS_SYSTEM) \
		-I $(ADDONS_COMPONENT) \
		-I $(ENGINE_INCLUDE) \
		-I $(INCLUDE_MODEL) \
		-I $(INCLUDE_GAME_MODEL) \
		-I $(INCLUDE_IA_SYSTEM) \
		-I $(INCLUDE_LUA_BINDING) \
		-I $(INCLUDE_LUA_SELENE) \
		-I $(INCLUDE_LUA_SELENE_FILES) \
		-I $(INCLUDE_GRAPHIC) \
		-I $(INCLUDE_OGRE) \
		-I $(INCLUDE_IOS) \
		-I $(INCLUDE_OVERLAY) \
		-I $(INCLUDE_TERRAIN) \
		-I $(INCLUDE_OIS) \
		-I $(INCLUDE_SAVE) \
		-I $(INCLUDE_CEGUI) \
		-I $(INCLUDE_GRAPHIC_MENU) \
		-I $(INCLUDE_EVENTM) \
		-I $(INCLUDE_CEGUIABS) \
		-I $(INCLUDE_MENU) \
		-I $(INCLUDE_AUDIO) \
		-I ./install/include/ \
		-I ./install/include/CEGUI \
		-I $(INCLUDE_LOADER) \
		-I $(INCLUDE_ATTACK_SYSTEM) \
		-I $(INCLUDE_DAMAGE_SYSTEM) \
		-I $(INCLUDE_HANDLER_SYSTEM) \
		-I $(INCLUDE_ANIMATION) \
		-I $(INCLUDE_INVENTORY) \
		-I $(INCLUDE_SPAWNER) \
		-I $(INCLUDE_DROP_SYSTEM) \
		-I $(INCLUDE_SPAWN_SYSTEM) \
		-I $(INCLUDE_SCORE_SYSTEM) \

CXXFLAGS =	-std=c++11 $(INCLUDES)

LDFLAGS	=	-ljsoncpp -L $(KEYCOLLECTION_INCLUDE) \
		-llua -L $(INCLUDE_LUA_BINDING) \
		-lboost_system -lOgreMain -lOgreOverlay -lOIS -lOgreTerrain \
		-lCEGUIBase-0 \
		-lCEGUIOgreRenderer-0 \
		-lsfml-system \
		-L lib/sfml -lsfml-audio -lsfml-system \

SRCS =		$(EVENT_HANDLER)/EventHandler.cpp \
		$(ENTITY)/entityCollection.cpp \
		$(INPUT_SYSTEM)/InputSystem.cpp \
	 	$(EXCEPTION)/CollectionException.cpp \
		$(EXCEPTION)/CustomException.cpp \
		$(EXCEPTION)/EventHandlerException.cpp \
		$(EXCEPTION)/KeyCollectionException.cpp \
		$(EXCEPTION)/EngineException.cpp \
		$(EXCEPTION)/IaSystemException.cpp \
		$(EXCEPTION)/SaveCollectionException.cpp \
		$(EXCEPTION)/MenuLoaderException.cpp \
		$(EXCEPTION)/GameException.cpp \
		$(KEYCOLLECTION)/KeyCollection.cpp \
		$(PHYSIC_SYSTEM)/PhysicSystem.cpp \
		$(ENGINE)/Engine.cpp \
		$(MODELS)/AModel.cpp \
		$(GAME_MODEL)/GameModel.cpp \
		$(GAME_MODEL)/menuGame.cpp \
		$(IA_SYSTEM)/IaSystem.cpp \
		$(IA_SYSTEM)/IaBinding.cpp \
		$(VIEW_SYSTEM)/Entity.cpp \
		$(VIEW_SYSTEM)/ViewInit.cpp \
		$(VIEW_SYSTEM)/ViewScene.cpp \
		$(VIEW_SYSTEM)/NewMOC.cpp \
		$(SAVECOLLECTION)/SaveCollection.cpp \
		$(GRAPHIC_MENU)/GraphicMenu.cpp \
		$(EVENTM)EventManager.cpp \
		$(EVENTM)FrameListener.cpp \
		$(MENUMODEL)MenuModel.cpp \
		$(AUDIO)/Audio.cpp \
		$(GRAPHIC_MENU)/MenuLoader.cpp \
		$(MENUMODEL)/SettingModel.cpp \
		$(MENUMODEL)/CommandModel.cpp \
		$(DIRLOADER)/loader.cpp \
		$(MODELS)/AMenuModel.cpp \
		$(IA_SYSTEM)/BinderComponent.cpp \
		$(DAMAGE_SYSTEM)/DamageSystem.cpp \
		$(ATTACK_SYSTEM)/AttackSystem.cpp \
		$(HANDLER_SYSTEM)/HandlerEntitySystem.cpp \
		$(ANIMATION_SYSTEM)/AnimationSystem.cpp \
		$(INVENTORY_SYSTEM)/InventorySystem.cpp \
		$(DIR_SPAWNER)/Spawner.cpp \
		$(DROP_SYSTEM)/DropSystem.cpp \
		$(DIR_SPAWN_SYSTEM)/SpawnSystem.cpp \
		$(DIR_SCORE_SYSTEM)/ScoreSystem.cpp \
		main.cpp


OBJS = $(SRCS:.cpp=.o)

all: main-build

blinux: LDFLAGS = -ljsoncpp \
		  -llua -L $(INCLUDE_LUA_BINDING) \
		  -lboost_system -lOgreMain -lOgreOverlay -lOIS -lOgreTerrain \
		  -lCEGUIBase-0 \
		  -lCEGUIOgreRenderer-0 \
		  -lsfml-system \
		  -lsfml-audio -lsfml-system \
		  -Wl,-rpath=./install/lldlib -L ./install/lldlib/
blinux: main-build
blinux:
	./install/export_env.sh
install: pre-build

pre-build:
	./install/install.sh

debug:	CXXFLAGS += -g3
debug:	fclean all

main-build: $(NAME)

$(NAME):	$(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
