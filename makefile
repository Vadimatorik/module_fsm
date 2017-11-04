ifndef MODULE_FSM_OPTIMIZATION
	MODULE_FSM_OPTIMIZATION = -g3 -O0
endif

FSM_CPP_FILE		:= $(shell find module_fsm/ -maxdepth 3 -type f -name "*.cpp" )
FSM_DIR				:= $(shell find module_fsm/ -maxdepth 3 -type d -name "*" )
FSM_PATH			:= $(addprefix -I, $(FSM_DIR))
FSM_OBJ_FILE		:= $(addprefix build/obj/, $(FSM_CPP_FILE))
FSM_OBJ_FILE		:= $(patsubst %.cpp, %.o, $(FSM_OBJ_FILE))

build/obj/module_fsm/%.o:	module_fsm/%.cpp
	@echo [CPP] $<
	@mkdir -p $(dir $@)
	@$(CPP) $(CPP_FLAGS) $(DEFINE_PROJ) $(USER_CFG_PATH) $(FSM_PATH) $(MODULE_FSM_OPTIMIZATION) -c $< -o $@

# Добавляем к общим переменным проекта.
PROJECT_PATH			+= $(FSM_PATH)
PROJECT_OBJ_FILE		+= $(FSM_OBJ_FILE)