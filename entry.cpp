#include "dependencies/global_includes.hpp"

unsigned long __stdcall main_thread(void* res) {
	AllocConsole();
	SetConsoleTitleA("csso_internal");
	freopen_s((FILE**)stdin, "CONIN$", "r", stdin);
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);

	interfaces::initialize();
	
	/*
	* Have fun looking through this piece of shit
	* Anyways it is a cheat and you still have advantage over other players.
	* ATTENTION: MANY THINGS WERE pasted by 2nd collaborator of this project - twod1e; I AM (lethality1337) is not responsible for this mess.
	* I (lethality1337) tried to write clean and understandable code
	* This gave me some experience and i've accounted some mistakes i made while coding this
	* also thanks for designer & whoever made aristois as i took their code snippets / base / project structure as a reference from the source(s) of these guys.
	*/

	hooked::initialize();

	while (!GetAsyncKeyState(VK_END))
		std::this_thread::sleep_for(std::chrono::milliseconds(50));


	std::this_thread::sleep_for(std::chrono::milliseconds(100));

	fclose((FILE*)stdin);
	fclose((FILE*)stdout);
	FreeConsole();

	FreeLibraryAndExitThread(reinterpret_cast<HMODULE>(res), 0);
	return 0ul;
}

bool __stdcall DllMain(void* inst, unsigned long reason, void* reserved) {
	if (reason == DLL_PROCESS_ATTACH) 
	{
		CreateThread(0, 0, main_thread, inst, 0, 0);
	}
	return true;
}