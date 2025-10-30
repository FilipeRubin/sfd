#include "graphics-window.h"
#include <algorithm>

vector<GraphicsWindow*> GraphicsWindow::s_instances = vector<GraphicsWindow*>();

bool GraphicsWindow::IsAnyWindowOpen()
{
	for (GraphicsWindow*& w : s_instances)
	{
		if (not w->ShouldClose())
		{
			return true;
		}
	}
	return false;
}

bool GraphicsWindow::TryInitialize(const WindowParameters& params)
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

	s_instances.emplace_back(this);

	return true;
}

bool GraphicsWindow::ShouldClose() const
{
	return m_window->ShouldClose();
}

void GraphicsWindow::Draw(float r, float g, float b)
{
	m_graphics->MakeCurrent();
	m_graphics->Clear(r, g, b);
	m_graphics->SwapBuffers();
	m_window->Process();
}

bool GraphicsWindow::IsInitialized() const
{
	return m_window->IsInitialized();
}

void GraphicsWindow::Finalize()
{
	using std::remove;

	if (not IsInitialized())
	{
		return;
	}

	m_graphics->Finalize();
	m_window->Finalize();
	s_instances.erase(remove(s_instances.begin(), s_instances.end(), this), s_instances.end());
}