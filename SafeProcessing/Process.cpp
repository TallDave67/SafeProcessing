#include "Process.h"
#include <objbase.h>
#include <shobjidl_core.h>

Process::Process()
{
}

HRESULT Process::process()
{
    IFileSaveDialog* pFileProcess = nullptr;
    HRESULT hr = CoCreateInstance(__uuidof(FileSaveDialog), NULL, CLSCTX_ALL,
        IID_PPV_ARGS(&pFileProcess));

    if (FAILED(hr))
    {
        // Handle the error.
        MessageBox(NULL, (LPCWSTR)L"Could not create IFileSaveDialog COM object", (LPCWSTR)L"Failure", MB_ICONERROR | MB_OK);
    }
    else
    {
        // Set the file types
        COMDLG_FILTERSPEC rgSpec[] =
        {
            { L"Text", L"*.txt"}
        };
        hr = pFileProcess->SetFileTypes(1,rgSpec);
        if (SUCCEEDED(hr)) pFileProcess->SetTitle(L"Choose Output File");
        if (SUCCEEDED(hr)) pFileProcess->SetOkButtonLabel(L"Process");
        
        // Show the Save dialog box.
        if (SUCCEEDED(hr))
        {
            hr = pFileProcess->Show(NULL);

            // Get the file name from the dialog box.
            if (SUCCEEDED(hr))
            {
                IShellItem* pItem;
                hr = pFileProcess->GetResult(&pItem);
                if (SUCCEEDED(hr))
                {
                    PWSTR pszFilePath;
                    hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

                    // Display the file name to the user.
                    if (SUCCEEDED(hr))
                    {
                        int idx = 0;
                        while (pszFilePath[idx] != '\0' && pszFilePath[idx] != '.') idx++;
                        pszFilePath[idx] = '\0';
                        m_agent.m_filepath = std::wstring(pszFilePath) + std::wstring(L".txt");
                        CoTaskMemFree(pszFilePath);

                        std::wstring process;
                        std::wstring process_title;
                        auto found = m_agent.m_filepath.find(L"threadsafe");
                        if (found == std::wstring::npos)
                        {
                            process = L" in a thread-unsafe manner ?";
                            process_title = L"Process Thread Unsafe";
                            m_agent.m_threadsafe = false;
                        }
                        else
                        {
                            process = L" in a thread-safe manner ?";
                            process_title = L"Process Thread Safe";
                            m_agent.m_threadsafe = true;
                        }

                        std::wstring msg = L"Write output to " + m_agent.m_filepath + process;
                        std::wstring title = process_title + L" ?";
                        if (MessageBox(NULL, const_cast<LPWSTR>(msg.c_str()), const_cast<LPWSTR>(title.c_str()), MB_YESNO) == IDYES)
                        {
                            m_agent.process();
                        }
                    }
                    pItem->Release();
                }
            }
        }
        pFileProcess->Release();
    }

    return hr;
}

