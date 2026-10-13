// cpp-web-service.cpp : Defines the entry point for the application.
//

#include "cpp-web-service.h"

// Функція для отримання поточного часу в форматі UTC
std::string get_utc_timestamp() {

	// Отримання поточного системного часу
	std::time_t now = std::time(nullptr);

	// Створення масиву символів для збереження відформатованого рядка
	char buf[100];

	// std::gmtime перетворює суцільний час у структуру
	// std::strftime форматує структуру часу
	std::strftime(buf, sizeof(buf), "%Y-%m-%dT%H:%M:%SZ", std::gmtime(&now));

	return std::string(buf);
}

int main(int argc, char** argv)
{
	crow::SimpleApp app;

	// Liveness Probe
	CROW_ROUTE(app, "/healthz/live")([]() {

		crow::json::wvalue body;

		body["status"] = "alive";
		body["timestamp"] = get_utc_timestamp();

		return crow::response(200, body);
		});

	// Readiness Probe
	// CROW_ROUTE створює ендпоінт для обробки HTTP GET-запитів
	CROW_ROUTE(app, "/healthz/ready")([]() {

		crow::json::wvalue body;

		body["status"] = "ready";
		body["database"] = "not_connected";
		body["timesatmp"] = get_utc_timestamp();

		return crow::response(200, body);
		});

	// Запуск сервера на порту 8080
	try {
		app.port(8080).multithreaded().run();
	}
	catch (const std::exception& e) {
		std::cerr << "Error starting the server: " << e.what() << std::endl;
	}

	return 0;
}
