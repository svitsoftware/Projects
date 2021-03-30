#include "App.h"

void App::checkClick(RECT* rect)
{

}

size_t GetSizeOfFile(const std::wstring& path)
{
    struct _stat fileinfo;
    _wstat(path.c_str(), &fileinfo);
    return fileinfo.st_size;
}

std::wstring LoadUtf8FileToString(const std::wstring& filename)
{
    std::wstring buffer;            // stores file contents
    FILE* f = _wfopen(filename.c_str(), L"rtS, ccs=UTF-8");

    // Failed to open file
    if (f == NULL)
    {
        // ...handle some error...
        return buffer;
    }

    size_t filesize = GetSizeOfFile(filename);

    // Read entire file contents in to memory
    if (filesize > 0)
    {
        buffer.resize(filesize);
        size_t wchars_read = fread(&(buffer.front()), sizeof(wchar_t), filesize, f);
        buffer.resize(wchars_read);
        buffer.shrink_to_fit();
    }

    fclose(f);

    return buffer;
}

void App::initDefaultStyles()
{
    Object* h1 = new Object("h1", new Params(Color::Transparent, Color::Black, 40, 1));
    Object* h2 = new Object("h2", new Params(Color::Transparent, Color(50, 60, 50), 35, 1));
    Object* h3 = new Object("h3", new Params(Color::Transparent, Color(50, 60, 50), 32, 0));
    Object* h4 = new Object("h4", new Params(Color::Transparent, Color(50, 60, 50), 28, 0));
    Object* h5 = new Object("h5", new Params(Color::Transparent, Color(50, 60, 50), 25, 0));
    Object* h6 = new Object("h6", new Params(Color::Transparent, Color(50, 60, 50), 22, 0));
    Object* p = new Object("p", new Params(Color::Transparent, Color(50, 60, 50), 20, 0));
    Object* b = new Object("b", new Params(Color::Transparent, Color::Black, 20, 1));
    Object* pre = new Object("pre", new Params(Color::Transparent, Color(59, 60, 50), 02, 0));
    Object* hr = new Object("hr", new Params(Color::Black, Color::Transparent, 0, 0));
    Object* button = new Object("button", new Params(Color(210, 200, 215), Color::Black, 20, 0));

    this->dfobjects.push_back(h1);
    this->dfobjects.push_back(h2);
    this->dfobjects.push_back(h3);
    this->dfobjects.push_back(h4);
    this->dfobjects.push_back(h5);
    this->dfobjects.push_back(h6);
    this->dfobjects.push_back(p);
    this->dfobjects.push_back(b);
    this->dfobjects.push_back(pre);
    this->dfobjects.push_back(hr);
    this->dfobjects.push_back(button);
}

App::App(HWND& hwnd, int width, int height)
{
    this->WIDTH = width;
	this->HEIGHT = height;

    this->ren = new Renderer(hwnd);

    this->initHome();

    this->initDefaultStyles();
    this->cssom = CSSOM(this->dfobjects);

    Nodes* tre = new Nodes("", "", vector<string>(), vector<string>());

    this->parser->ParseHtml(LoadUtf8FileToString(L"C:\\Users\\zoran\\Desktop\\file.txt\\"), tre, *&this->cssom);

    this->htmlren->RenderHtml(tre, this->ren, *&this->cssom);
}

App::~App()
{
    
}

void App::update(HWND& hwnd)
{
	mouseMove(hwnd);
	this->ren->Render();
}

void App::mouseDown(POINT p)
{
	this->downMousePoint = p;
	this->mousePressed = true;
    this->ren->higherRefresh();
}

void App::mouseMove(HWND& hwnd)
{
	if (this->mousePressed && this->downMousePoint.y < 35)
	{
		GetCursorPos(&movingMousePoint);
		MoveWindow(hwnd, movingMousePoint.x - downMousePoint.x, movingMousePoint.y - downMousePoint.y, this->WIDTH, this->HEIGHT, true);
	}
}

void App::mouseUp(POINT p)
{
	this->mousePressed = false;
    this->ren->CheckClick(&p);
    this->ren->lowerRefresh();
}

void App::initHome()
{
    this->ren->DrawRectangle(0, 0, WIDTH, 35, Color(80, 30, 200), Color::Black, 0, true);
    this->ren->DrawString(5, 5, "SVIT Browser", 0, 20, Color(0, 0, 0), Decoration::none, true);
    this->ren->DrawImageFromFIle(WIDTH - 46, 4, "close.png", Vector2f(0.4f, 0.4f));
}

void App::Navigate(string url)
{
}

void App::mouseWheel(short delta)
{
    if (delta < 0)
    {
        this->ren->Scroll(-20);
    }
    else if (delta > 0)
    {
        this->ren->Scroll(20);
    }
}


