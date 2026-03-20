#include "App.h"
#include "base/kernel/Entry.h"
#include "base/kernel/Process.h"

#ifdef _WIN32
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif

namespace xmrig {
    // Global variables to store process and app pointers
    Process* process = nullptr;
    App* app = nullptr;
}

extern "C" {

    DLL_EXPORT int xmrig_start(int argc, char** argv)
    {
        using namespace xmrig;

        // Create the process object with command-line arguments
        process = new Process(argc, argv);

        // Determine the entry point based on command-line arguments
        const Entry::Id entry = Entry::get(*process);
        if (entry) {
            // If entry is valid, execute and return
            return Entry::exec(*process, entry);
        }

        // Initialize the main application
        app = new App(process);

        // Start the XMRig application
        return app->exec();
    }

    DLL_EXPORT void xmrig_stop()
    {
        using namespace xmrig;

        // Properly stop the XMRig application
        if (app) {
            app->onConsoleCommand((char)3); // Simulate sending a CTRL+C
        }

        // Clean up memory
        delete app;
        app = nullptr;

        delete process;
        process = nullptr;
    }
}