FSM_H_FILE			:= $(shell find module_fsm/ -maxdepth 3 -type f -name "*.h" )
FSM_CPP_FILE		:= $(shell find module_fsm/ -maxdepth 3 -type f -name "*.cpp" )
FSM_DIR				:= $(shell find module_fsm/ -maxdepth 3 -type d -name "*" )
FSM_PATH			:= $(addprefix -I, $(FSM_DIR))
FSM_OBJ_FILE		:= $(addprefix build/obj/, $(FSM_CPP_FILE))
FSM_OBJ_FILE		:= $(patsubst %.cpp, %.o, $(FSM_OBJ_FILE))

build/obj/module_fsm/%.o:	module_fsm/%.cpp
	@echo [CPP] $<
	@mkdir -p $(dir $@)
	@$(CPP) $(CPP_FLAGS) $(FSM_PATH) -c $< -o $@

# Добавляем к общим переменным проекта.
PROJECT_PATH			+= $(FSM_PATH)
PROJECT_OBJ_FILE		+= $(FSM_OBJ_FILE)