# Лабораторна робота №1
## Налаштування середовища, Docker Compose, Healthcheck API, керування залежностями та GitHub Actions CI

Вебзастосунок на мові C++, розроблений у межах **Лабораторної роботи №1** з дисципліни *«Технології розроблення серверних компонентів»*.
Застосунок реалізує системні ендпоінти перевірки стану **Liveness** та **Readiness** за допомогою веб-фреймворку **Crow**, упакований у **Docker**-контейнер та підтримує запуск через **Docker Compose**.

---

### Стек технологій
* **Мова програмування:** `C++`
* **Веб-фреймворк:** `Crow`
* **Система збірки:** `CMake / Ninja`
* **Менеджер залежностей:** `vcpkg`
* **Контейнеризація:** `Docker, Docker Compose`
* **CI/CD:** `GitHub Actions`

---

### Системні ендпоінти
Сервіс прослуховує порт `8080` та надає два маршрути перевірки стану:

| Ендпоінт | HTTP Метод | Статус | Опис / JSON-структура |
| :--- | :---: | :---: | :--- |
| `/healthz/live` | `GET` | `200 OK` | **Liveness Probe** — перевірка виконання процесу застосунку |
| `/healthz/ready` | `GET` | `200 OK` | **Readiness Probe** — перевірка готовністі обробляти трафік |


Приклади JSON-відповідей:

* **GET `/healthz/live`**
  ```json
  {
    "status": "alive",
    "timestamp": "2026-10-14T15:00:00Z"
  }
  ```

  * **GET `/healthz/live`**
  ```json
  {
    "status": "ready",
    "database": "not_connected_yet",
    "timestamp": "2026-10-14T15:00:00Z"
  }
  ```

---

### Інструкція локального запуску через Docker Compose
Вимоги:
* Встановлений `Docker Desktop`.
* `git` для клонування репозиторію.

1. Клонування репозиторію

```bash
git clone https://github.com/ваше-ім'я-користувача/cpp-web-service.git
cd cpp-web-service
```

2. Запустіть контейнер

```bash
docker compose up --build
```

3. Для перевірки роботи сервісу перейдіть за адресами

http://localhost:8080/healthz/live

http://localhost:8080/healthz/ready

4. Зупинити контейнери

```bash
docker compose down
```
