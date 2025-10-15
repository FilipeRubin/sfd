#include <core-systems.h>
#include <memory>

int main()
{
	typedef std::unique_ptr<IWindow> pwnd_t;
	pwnd_t window = pwnd_t(CoreSystems::CreateWindow());
	pwnd_t window2 = pwnd_t(CoreSystems::CreateWindow());

	if (not window->TryInitialize({
		.title = L"Simple app",
		.width = 1280,
		.height = 720
		}))
	{
		return 1;
	}

	if (not window2->TryInitialize({
		.title = L"Secondary window",
		.width = 680,
		.height = 480
		}))
	{
		window->Finalize();
		return 1;
	}

	while (not window->ShouldClose() or not window2->ShouldClose())
	{
		if (not window->ShouldClose())
		{
			window->Process();
		}
		else if (window->IsInitialized())
		{
			window->Finalize();
		}

		if (not window2->ShouldClose())
		{
			window2->Process();
		}
		else if (window2->IsInitialized())
		{
			window2->Finalize();
		}
	}

	if (window->IsInitialized())
	{
		window->Finalize();
	}
	if (window2->IsInitialized())
	{
		window2->Finalize();
	}

	return 0;
}