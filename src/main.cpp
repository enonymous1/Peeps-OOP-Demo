#include "App.h"

/// Main entry point for the Peeps-OOP-Demo application.
///
/// This function constructs the top-level application controller and
/// delegates execution to `App::Run()`. It returns 0 to indicate success
/// to the operating system.
int main()
{
    App app;
    app.Run();
    return 0;
}