#include "Form1.h"

using namespace System;
using namespace System::Windows::Forms;


[STAThread]
void Main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	ILSTS_Sample_CPP::Form1 form;
	Application::Run(%form);
}