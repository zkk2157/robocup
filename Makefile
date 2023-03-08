EXECUTABLE = CIT3D_binary

export MAINDIR =./
export M_Agent=./Agent/
export M_Conn=./Connection/
export M_Eff=./Effectors
export M_Log=./log/

export M_Play=./Player/
export M_Sensor=./Sensor/
export M_Skills=./Skills/
export M_Strategy=./Strategy/
export M_Utility=./Utility/
export M_Worldmodel=./Worldmodel/
export RUBYDIR =/usr/lib64/ruby/1.8/x86_64-linux/
export SERVERLIBDIR =/usr/local/include/simspark/
export LIBDIR=/usr/local/lib/simspark
#export LIBDIR=./citlib
#export SERVERLIBDIR=./citlib

export INCLUDEFLAG = -I$(RUBYDIR) -I$(SERVERLIBDIR)  

#BOOST_THREADS_LIB = -boost_thread
#/usr/local/include/simspark/rcssnet
export CC = g++
export CPPFLAGS =
export CFLAGS = -DHAVE_CONFIG_H -pipe -Wall
export CXXFLAGS = $(CFLAGS)
export COMPILE = $(CC) $(CPPFLAGS) $(CFLAGS) -c



CITOBJ = \
	$(MAINDIR)Sensor/NumFilter.o\
	$(MAINDIR)main.o \
	$(MAINDIR)Player/agentstrategy.o \
	$(MAINDIR)Player/CITPlayer.o \
	$(MAINDIR)log/logger.o \
	$(MAINDIR)Utility/Geometry.o \
	$(MAINDIR)Utility/CITMath.o \
	$(MAINDIR)Connection/socket.o \
	$(MAINDIR)Connection/Communit.o \
	$(MAINDIR)Connection/Tcpconnection.o \
	$(MAINDIR)Connection/Udpconnection.o \
	$(MAINDIR)Connection/Fileinput.o \
	$(MAINDIR)Agent/agent.o \
	$(MAINDIR)Sensor/perceptor.o \
	$(MAINDIR)Worldmodel/playerinfo.o\
	$(MAINDIR)Worldmodel/SaveCoordinate.o\
	$(MAINDIR)Worldmodel/worldmodel.o \
	$(MAINDIR)Effectors/jointEffector.o \
	$(MAINDIR)Effectors/formatInfoToServer.o \
	$(MAINDIR)Utility/timer.o \
	$(MAINDIR)Skill/theNewWalk.o \
	$(MAINDIR)Skill/basicMotion.o\
	$(MAINDIR)Skill/standup.o\
	$(MAINDIR)conf/Configure.o\
	$(MAINDIR)Utility/Queue.o\
	$(MAINDIR)Utility/Cout.o\
	$(MAINDIR)Utility/convert.o\
	$(MAINDIR)Effectors/Say.o\
	$(MAINDIR)Sensor/Hear.o\
	$(MAINDIR)MonitorDraw/DrawBuffer.o\
	$(MAINDIR)MonitorDraw/MDrawer.o
all:edit

edit :  $(CITOBJ)
	$(CC) -g -o $(EXECUTABLE) $(CITOBJ)\
    $(LIBDIR)/liboxygen.so.6\
    $(LIBDIR)/librcssnet3D.so.0 \
    -lode $(BOOST_THREADS_LIB) -lm\
    $(LIBDIR)/libzeitgeist.so.3\
    -L/usr/lib64/ruby/1.8/x86_64-linux \
    $(LIBDIR)/libsalt.so\
    -Wl,--rpath -Wl,$(LIBDIR)
	cp ./CIT3D_binary CIT3D/CIT3D_binary
$(MAINDIR)%.d:%.cpp
	@$(CC) -M $(INCLUDEFLAG) $(CPPFLAGS) $< > $@
	@$(CC) -M $(INCLUDEFLAG) $(CPPFLAGS) $< | sed s/\\.o/.d/ > $@
$(MAINDIR)%.o:%.cpp
	@$(COMPILE) $(INCLUDEFLAG) -o $@ $<
$(M_Agent)%.d:%.cpp
	@$(CC) -M $(INCLUDEFLAG) $(CPPFLAGS) $< > $@
	@$(CC) -M $(INCLUDEFLAG) $(CPPFLAGS) $< | sed s/\\.o/.d/ > $@
$(M_Agent)%.o:%.cpp
	@$(COMPILE) $(INCLUDEFLAG) -o $@ $<
$(M_Conn)%.d:%.cpp
	@$(CC) -M $(INCLUDEFLAG) $(CPPFLAGS) $< > $@
	@$(CC) -M $(INCLUDEFLAG) $(CPPFLAGS) $< | sed s/\\.o/.d/ > $@
$(M_Conn)%.o:%.cpp
	@$(COMPILE) $(INCLUDEFLAG) -o $@ $<
$(M_Eff)%.d:%.cpp
	@$(CC) -M $(INCLUDEFLAG) $(CPPFLAGS) $< > $@
	@$(CC) -M $(INCLUDEFLAG) $(CPPFLAGS) $< | sed s/\\.o/.d/ > $@
$(M_Eff)%.o:%.cpp
	@$(COMPILE) $(INCLUDEFLAG) -o $@ $<
$(M_Log)%.d:%.cpp
	@$(CC) -M $(INCLUDEFLAG) $(CPPFLAGS) $< > $@
	@$(CC) -M $(INCLUDEFLAG) $(CPPFLAGS) $< | sed s/\\.o/.d/ > $@
$(M_Log)%.o:%.cpp
	@$(COMPILE) $(INCLUDEFLAG) -o $@ $<
$(M_Play)%.d:%.cpp
	@$(CC) -M $(INCLUDEFLAG) $(CPPFLAGS) $< > $@
	@$(CC) -M $(INCLUDEFLAG) $(CPPFLAGS) $< | sed s/\\.o/.d/ > $@
$(M_Play)%.o:%.cpp
	@$(COMPILE) $(INCLUDEFLAG) -o $@ $<
$(M_Sensor)%.d:%.cpp
	@$(CC) -M $(INCLUDEFLAG) $(CPPFLAGS) $< > $@
	@$(CC) -M $(INCLUDEFLAG) $(CPPFLAGS) $< | sed s/\\.o/.d/ > $@
$(M_Sensor)%.o:%.cpp
	@$(COMPILE) $(INCLUDEFLAG) -o $@ $<
$(M_Skills)%.d:%.cpp
	@$(CC) -M $(INCLUDEFLAG) $(CPPFLAGS) $< > $@
	@$(CC) -M $(INCLUDEFLAG) $(CPPFLAGS) $< | sed s/\\.o/.d/ > $@
$(M_Skills)%.o:%.cpp
	@$(COMPILE) $(INCLUDEFLAG) -o $@ $<
$(M_Strategy)%.d:%.cpp
	@$(CC) -M $(INCLUDEFLAG) $(CPPFLAGS) $< > $@
	@$(CC) -M $(INCLUDEFLAG) $(CPPFLAGS) $< | sed s/\\.o/.d/ > $@
$(M_Strategy)%.o:%.cpp
	@$(COMPILE) $(INCLUDEFLAG) -o $@ $<
$(M_Utility)%.d:%.cpp
	@$(CC) -M $(INCLUDEFLAG) $(CPPFLAGS) $< > $@
	@$(CC) -M $(INCLUDEFLAG) $(CPPFLAGS) $< | sed s/\\.o/.d/ > $@
$(M_Utility)%.o:%.cpp
	@$(COMPILE) $(INCLUDEFLAG) -o $@ $<
$(M_Worldmodel)%.d:%.cpp
	@$(CC) -M $(INCLUDEFLAG) $(CPPFLAGS) $< > $@
	@$(CC) -M $(INCLUDEFLAG) $(CPPFLAGS) $< | sed s/\\.o/.d/ > $@
$(M_Worldmodel)%.o:%.cpp
	@$(COMPILE) $(INCLUDEFLAG) -o $@ $<

	cp ./CIT3D_binary CIT3D/CIT3D_binary
clean:
	-rm   $(CITOBJ)  
	-rm   $(EXECUTABLE)
	-rm   CIT3D/CIT3D_binary
rebuild: clean edit

movelogs:
	-mv  ./Logs/*.log ./Logs/HistoryLogs/
	-mv  ./Logs/*.out ./Logs/HistoryLogs/
	-mv  ./Logs/*.err ./Logs/HistoryLogs/
	-mv ./Logs/分析Logs/*.fout ./Logs/HistoryLogs/
	-mv  ../../monitor/*.log ./Logs/HistoryLogs/
   	
