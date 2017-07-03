##
## Makefile for Makefile in /home/jsx/Epitech/tek2/C++2/indiestudio/cpp_indie_studio/
##
## Made by jsx
## Login   <jean-sebastien.herbaux@epitech.eu>
##
## Started on  Mon May  1 01:13:42 2017 jsx
## Last update Fri Jun 16 14:20:53 2017 JSX
##

NAME 				= 		zappy_client

PWD					=			pwd

CC      		=    	g++

RM      		=  		rm -rf

CP      		=  		cp -rf

LDFLAGS			=			-L./Dependencies/Libs/																\
									-lIrrlicht																						\
									-lIrrKlang -Wl,-rpath=$(CURDIR)/Dependencies/Libs/ 		\
									-lGL 																									\
									-lXxf86vm																							\
									-lXext																								\
									-lX11																									\
									-ldl																									\
									-lpthread																							\

CPPFLAGS		=			-W -Wall -Wextra -Werror -std=c++14

CPPFLAGS		+=		-I./Dependencies/Includes/Irrlicht/										\
									-I./Dependencies/Includes/Irrklang/										\
									-I./Dependencies/Libs/Kirrlicht/											\
									-I./Dependencies/Libs/																\

CPPFLAGS		+=		-I./Srcs/Error/																				\
									-I./Srcs/Control/																			\
									-I./Srcs/Socket/																			\
									-I./Srcs/Module/																			\
									-I./Srcs/Module/ModuleLoader/													\
									-I./Srcs/Module/Connection/														\
									-I./Srcs/Module/Game/																	\
									-I./Srcs/Module/Command/															\

SRCS 				=			./Dependencies/Libs/Kirrlicht/Kirrlicht.cpp						\
									./Dependencies/Libs/Kirrlicht/EventReceiver.cpp				\

SRCS 				+=		./Srcs/main.cpp																				\
									./Srcs/Control/Control.cpp														\
									./Srcs/Socket/Socket.cpp															\
									./Srcs/Module/ModuleLoader/ModuleLoader.cpp						\
									./Srcs/Module/Connection/Connection.cpp								\
									./Srcs/Module/Game/Game.cpp														\
									./Srcs/Module/Command/Command.cpp											\

OBJS     		= 		$(SRCS:.cpp=.o)

all: $(NAME)
	@printf "\033[0;32mzappy_client successfully installed\n\033[0m"

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(NAME)

fclean: clean
	$(RM) $(OBJS)

uninstall: fclean
	$(RM) $(NAME)
	$(RM) ./Dependencies/Includes/Irrlicht/*.h
	$(RM) ./Dependencies/Includes/irrklang/*.h
	$(RM) ./Dependencies/Libs/*.a
	$(RM) ./Dependencies/Libs/*.so
	$(RM) ./Assets/
	$(RM) ./install

re: fclean all

install: uninstall
	mkdir ./install
	@printf "\033[0;32mAssets:\n\033[0m"
	wget 149.202.42.41/zappylosite/assets/Assets.zip ; mv Assets.zip ./install/ && unzip ./install/Assets.zip -d ./install && $(RM) ./install/Assets.zip
	$(CP) ./install/Assets/ ./
	@printf "\033[0;32mDone...\n\033[0m"
	@printf "\033[0;32mIrrklang:\n\033[0m"
	wget storage.bomberwatch.eu/libs/audio/irrklang.zip ; mv irrklang.zip ./install/ && unzip ./install/irrklang.zip -d ./install && $(RM) ./install/irrklang.zip
	$(CP) ./install/irrklang/include/* ./Dependencies/Includes/Irrklang
	$(CP) ./install/irrklang/libIrrKlang.so ./Dependencies/Libs/
	@printf "\033[0;32mIrrklang installed\n\033[0m"
	@printf "\033[0;32mIrrlicht:\n\033[0m"
	wget storage.bomberwatch.eu/libs/graphics/irrlicht-1.8.2.zip ; mv irrlicht-1.8.2.zip ./install/ && unzip ./install/irrlicht-1.8.2.zip -d ./install && $(RM) ./install/irrlicht-1.8.2.zip
	$(CP) ./install/irrlicht-1.8.2/include/* ./Dependencies/Includes/Irrlicht
	make -C ./install/irrlicht-1.8.2/source/Irrlicht/
	$(CP) ./install/irrlicht-1.8.2/source/Irrlicht/libIrrlicht.a ./Dependencies/Libs/
	@printf "\033[0;32mIrrlicht installed\n\033[0m"
	$(RM) ./install
	make -C ./

%.o : %.c
	$(CC) $(CXXFLAGS) -c $< -o $@
