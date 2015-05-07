// MiddleManager2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MiddleManager2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// The one and only application object

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(NULL);

	if (hModule != NULL)
	{
		// initialize MFC and print and error on failure
		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{
			// TODO: change error code to suit your needs
			_tprintf(_T("Fatal Error: MFC initialization failed\n"));
			nRetCode = 1;
		}
		else
		{
			// TODO: code your application's behavior here.
			
			TCHAR data[500] = { 0 };
			serial::Serial myserial("COM3", 115200, serial::Timeout::simpleTimeout(1000));
			if (myserial.isOpen())
			{
				cout << "Opened COM3" << endl;
				size_t bytes_wrote;
				string result;
				stringstream ss;
				string buf;
				string data;
				string command;
				
				while (true)
				{	
					myserial.flush();
					result = myserial.readline(10, "\n");
					cout << result << endl;
					ss.clear();
					ss.flush();
					ss.str(result);
					buf = "";
					while (ss >> buf)
					{
						if (ss.fail()) cout << "Failed" << endl;
						bool good = buf.compare("Range");
						if (buf.compare("Range") == 0)
						{
							buf = "";
							ss >> buf;
							data = "range ";
							data.append(buf);
							command = "node C:\\Users\\jmluc_000\\repositories\\topTier\\poster.js ";
							command.append(data);
							system(command.c_str());
							cout << "Logged: " << command << endl;
						}
						if (buf.compare("Light") == 0)
						{
							buf = "";
							ss >> buf;
							data = "light ";
							data.append(buf);
							command = "node C:\\Users\\jmluc_000\\repositories\\topTier\\poster.js ";
							command.append(data);
							system(command.c_str());
							cout << "Logged: " << command << endl;
						}
					}
					//cout << result << endl;
				}
			}
			else cout << "Could not open COM3" << endl;
		}
	}
	else
	{
		// TODO: change error code to suit your needs
		_tprintf(_T("Fatal Error: GetModuleHandle failed\n"));
		nRetCode = 1;
	}

	return nRetCode;
}
