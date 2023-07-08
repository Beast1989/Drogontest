
#include <drogon/drogon.h>
using namespace drogon;

int main()
{
	app()
		.setLogPath("./logs")
		.setLogLevel(trantor::Logger::kWarn)
		.addListener("127.0.0.1", 27019)
		.setThreadNum(0)
		//.loadConfigFile("./config.json")
		.run();
}
