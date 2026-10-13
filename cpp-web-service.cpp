// cpp-web-service.cpp : Defines the entry point for the application.
//

#include "cpp-web-service.h"

int main(int argc, char** argv)
{
	crow::SimpleApp app;

	CROW_ROUTE(app, "/")([]() {
		return "Hello World!";
		});

	app.port(8080).multithreaded().run();

	return 0;
}
