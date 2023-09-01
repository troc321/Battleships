################################################
# Two changes are needed. Replace references to DumbPlayerV2 with
# references to your object (easiest).
# (1) Change DumbPlayerV2.o to your player's .o file to CONTESTOBJECTS
# (2) Change DumbPlayerV2 references to your player's name in the
#     dependencies right after DumbPlayerV2's.
################################################

CXXFLAGS = -g -Wall -O0 -std=c++11
CXX = g++


################################################
# Change 1:
# Add your player on the line after GamblerPlayer 
################################################
CONTESTOBJECTS = AIContest.o BoardV3.o Message.o PlayerV2.o conio.o contest.o \
	blackPearl.o battlePearl.o CleanPlayerV2.o GamblerPlayerV2.o LearningGambler.o SemiSmartPlayerV2.o

TESTEROBJECTS = AIContest.o BoardV3.o Message.o PlayerV2.o conio.o tester.o \
	blackPearl.o battlePearl.o CleanPlayerV2.o GamblerPlayerV2.o LearningGambler.o SemiSmartPlayerV2.o 

HOST_NAME := $(shell hostname)
HOST_OK := no

$(info Checking that you are on matt or john ...)
ifeq ($(HOST_NAME),matt.cse.taylor.edu)
    $(info You are on matt. Good, carry on.)
    HOST_OK = yes
endif

ifeq ($(HOST_NAME),john)
    $(info You are on john. Good, carry on.)
    HOST_OK = yes
endif

ifneq ($(HOST_OK),yes)
    $(error Compile code on matt or john, or else hack this Makefile if you know what you are doing.)
endif

instructions:
	@echo "Make options: contest, testAI, clean, tar"

contest: $(CONTESTOBJECTS)
	g++ -o contest $(CONTESTOBJECTS)
	@echo "Contest binary is in 'contest'. Run as './contest'"

testAI: $(TESTEROBJECTS) 
	g++ -o testAI $(TESTEROBJECTS)
	@echo "Be sure to change DumbPlayerV2 to your AI in 'tester.cpp'"
	@echo "Tester is in 'testAI'. Run as './testAI'"

clean:
	rm -f contest testAI $(CONTESTOBJECTS) $(TESTEROBJECTS)

tar:
	g++ -c -Wall -O2 CleanPlayerV2.cpp
	g++ -c -Wall -O2 SemiSmartPlayerV2.cpp
	g++ -c -Wall -O2 GamblerPlayerV2.cpp
	g++ -c -Wall -O2 BoardV3.cpp
	tar -cvf binaries.tar CleanPlayerV2.o GamblerPlayerV2.o BoardV3.o SemiSmartPlayerV2.o

contest.o: contest.cpp defines.h Message.o
tester.o: tester.cpp defines.h Message.o
Message.o: Message.cpp Message.h defines.h
conio.o: conio.cpp conio.h
AIContest.o: AIContest.cpp AIContest.h Message.o defines.h

# Players here
blackPearl.o: blackPearl.cpp blackPearl.h defines.h PlayerV2.cpp PlayerV2.h Message.o
battlePearl.o: battlePearl.cpp battlePearl.h defines.h PlayerV2.cpp PlayerV2.h Message.o

################################################
# Change 2:
# Add your player dependency information below
################################################


# CleanPlayerV2.o and other provided binaries are only available as a linkable Linux binary, not as source code.
CleanPlayerV2.o: 
	tar -xvf binaries.tar CleanPlayerV2.o
GamblerPlayerV2.o:
	tar -xvf binaries.tar GamblerPlayerV2.o
LearningGambler.o: 
	tar -xvf binaries.tar LearningGambler.o
SemiSmartPlayerV2.o: 
	tar -xvf binaries.tar SemiSmartPlayerV2.o
BoardV3.o:
	tar -xvf binaries.tar BoardV3.o

