#include <core-systems.h>
#include <memory>

using std::unique_ptr;

class GraphicsWindow
{
public:
	bool TryInitialize(const WindowParameters& params)
	{
		m_window = unique_ptr<IWindow>(CoreSystems::CreateWindow());
		if (not m_window->TryInitialize(params))
		{
			return false;
		}
		
		m_graphics = unique_ptr<IGraphicsBackend>(CoreSystems::CreateGraphicsBackend(m_window.get()));
		if (not m_graphics->TryInitialize())
		{
			m_window->Finalize();
			return false;
		}
		return true;
	}
	
	bool ShouldClose() const
	{
		return m_window->ShouldClose();
	}

	void Draw(float r, float g, float b)
	{
		m_graphics->MakeCurrent();
		m_graphics->Clear(r, g, b);
		m_window->Process();
	}

	bool IsInitialized() const
	{
		return m_window->IsInitialized();
	}

	void Finalize()
	{
		m_graphics->Finalize();
		m_window->Finalize();
	}
private:
	unique_ptr<IWindow> m_window;
	unique_ptr<IGraphicsBackend> m_graphics;
};

int main()
{
	GraphicsWindow gw1 = GraphicsWindow();
	GraphicsWindow gw2 = GraphicsWindow();
	if (not gw1.TryInitialize({
		.title = L"Game window",
		.width = 1280,
		.height = 720
		}))
	{
		return 1;
	}

	if (not gw2.TryInitialize({
		.title = L"Debug window",
		.width = 640,
		.height = 480
		}))
	{
		gw1.Finalize();
		return 2;
	}
	
	while (not gw1.ShouldClose() or not gw2.ShouldClose())
	{
		if (gw1.ShouldClose() and gw1.IsInitialized())
		{
			gw1.Finalize();
		}
		else if (gw1.IsInitialized())
		{
			gw1.Draw(0.1f, 0.45f, 0.95f);
		}

		if (gw2.ShouldClose() and gw2.IsInitialized())
		{
			gw2.Finalize();
		}
		else if (gw2.IsInitialized())
		{
			gw2.Draw(0.9f, 0.65f, 0.05f);
		}
	}

	if (gw1.IsInitialized()) gw1.Finalize();
	if (gw2.IsInitialized()) gw2.Finalize();

	return 0;
}