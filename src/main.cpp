#include <mm/engine.hpp>
#include <mm/logger.hpp>
#include <spdlog/cfg/env.h>

#include "./setup_services.hpp"

#include <mm/services/opengl_renderer.hpp>
#include <mm/services/screen_director.hpp>
#include <mm/services/imgui_s.hpp>
#include <mm_tox/services/tox_service.hpp>

#include <mm/services/imgui_menu_bar.hpp>
#include <mm/services/engine_tools.hpp>
#include <mm/services/opengl_renderer_tools.hpp>
#include <mm/services/screen_director_tools.hpp>
#include <mm_tox/services/tox_chat.hpp>

bool setup_engine(MM::Engine& engine, int argc, char** argv) {
	return setup_engine_t<
		MM::Services::SDLService, // enabled by default
		MM::Services::FilesystemService, // enabled by default

		//MM::Services::SoundService,
		MM::Tox::Services::ToxService,

		MM::Services::OpenGLRenderer,

		MM::Services::ImGuiService,
		MM::Services::ImGuiMenuBar,
		MM::Services::ImGuiEngineTools,
		MM::Services::ImGuiOpenGLRendererTools,
		MM::Services::ImGuiScreenDirectorTools,
		MM::Tox::Services::ToxChat,

		// your services here

		// sd is allways the last, since it kicks of the first screen
		MM::Services::ScreenDirector
	>(engine, argc, argv);
}

static MM::Engine engine;

int main(int argc, char** argv) {
	spdlog::cfg::load_env_levels();

	if (!setup_engine(engine, argc, argv)) {
		SPDLOG_ERROR("SETUP FAILED!");
		return 1;
	}

	// queue first screen

	engine.run();

	// emscripten expects main to exit after setup
#ifndef __EMSCRIPTEN__
	engine.cleanup();
#endif

	return 0;
}

