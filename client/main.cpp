#include <sdbus-c++/sdbus-c++.h>

#include <iostream>
#include <string>
#include <unistd.h>
#include <vector>

void onConcatenated(sdbus::Signal& signal)
{
    std::string concatenatedString;
    signal >> concatenatedString;

    std::cout << "Received signal with concatenated string " << concatenatedString << std::endl;
}

int main(int argc, char *argv[])
{
    // Create proxy object for the concatenator object on the server side. Since here
    // we are creating the proxy instance without passing connection to it, the proxy
    // will create its own connection automatically, and it will be system bus connection.
    const char* destinationName = "org.sdbuscpp.concatenator";
    const char* objectPath = "/org/sdbuscpp/concatenator";
    auto conn = sdbus::createSessionBusConnectionWithAddress("unix:path=/tmp/bus.socket");
    auto concatenatorProxy = sdbus::createProxy(std::move(conn), destinationName, objectPath);

    // Let's subscribe for the 'concatenated' signals
    const char* interfaceName = "org.sdbuscpp.Concatenator";
    concatenatorProxy->registerSignalHandler(interfaceName, "concatenated", &onConcatenated);
    concatenatorProxy->finishRegistration();

    std::vector<int> numbers = {1, 2, 3};
    std::string separator = ":";

    while (true) {
        try {
            // Invoke concatenate on given interface of the object
            {
                auto method = concatenatorProxy->createMethodCall(interfaceName, "concatenate");
                method << numbers << separator;
                auto reply = concatenatorProxy->callMethod(method);
                std::string result;
                reply >> result;
                assert(result == "1:2:3");
            }

            // Invoke concatenate again, this time with no numbers and we shall get an error
            {
                auto method = concatenatorProxy->createMethodCall(interfaceName, "concatenate");
                method << std::vector<int>() << separator;
                try
                {
                    auto reply = concatenatorProxy->callMethod(method);
                    assert(false);
                }
                catch(const sdbus::Error& e)
                {
                    std::cerr << "Got concatenate error " << e.getName() << " with message " << e.getMessage() << std::endl;
                }
            }
        } catch (const sdbus::Error& err) {
            std::cerr << err.getMessage() << std::endl;
        }

        // Give sufficient time to receive 'concatenated' signal from the first concatenate invocation
        sleep(5);
    }

    return 0;
}
