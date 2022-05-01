cmake_minimum_required(VERSION 3.9 FATAL_ERROR)

project(mm_tox_chat_demo CXX C)

add_executable(mm_tox_chat_demo
	./setup_services.hpp
	./setup_services.cpp

	./screens/test_screen.hpp
	./screens/test_screen.cpp

	./main.cpp
)

target_link_libraries(mm_tox_chat_demo PUBLIC
	imgui_service
	screen_director

	opengl_renderer_s
	imgui_render_task

	imgui_tools
	imgui_opengl_renderer_tools

	mm_tox
	mm_tox_imgui
	#mm_logo_screen
)

if(EMSCRIPTEN)
	set_target_properties(mm_tox_chat_demo PROPERTIES COMPILE_FLAGS "-s USE_SDL=2")

	set_target_properties(mm_tox_chat_demo PROPERTIES LINK_FLAGS "-flto -s USE_SDL=2 -s MIN_WEBGL_VERSION=2 -s MAX_WEBGL_VERSION=2 -s FULL_ES2=1 -s FULL_ES3=1 -s ALLOW_MEMORY_GROWTH=1")
endif()

