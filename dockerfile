# Stage 1: Builder
FROM ubuntu:latest AS builder

# Вимикання інтерактивних запитів під час встановлення пакетів
ENV DEBIAN_FRONTEND=noninteractive

# Встановлення необхідних утиліт для збірки C++ проєкту
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    ninja-build \
    git \
    curl \
    zip \
    unzip \
    tar \
    pkg-config \
    && rm -rf /var/lib/apt/lists/*

# Встановлення менеджеру залежностей vcpkg
WORKDIR /opt/vcpkg
RUN git clone https://github.com/microsoft/vcpkg.git . \
    && ./bootstrap-vcpkg.sh -disableMetrics

# Перехід в робочу директорію проєкту
WORKDIR /app

# Копіювання конфігурації vcpkg
COPY vcpkg.json .

# Копіюємо всі файли проєкту
COPY . .

# Конфігурування та збирання проєкту у режимі Release через Ninja
RUN cmake -B build -S . \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_TOOLCHAIN_FILE=/opt/vcpkg/scripts/buildsystems/vcpkg.cmake \
    -G Ninja \
    && cmake --build build --config Release

# Stage 2: Runner
FROM ubuntu:latest AS runner

# Встановлення стандартних бібліотек С++
RUN apt-get update && apt-get install -y \
    libstdc++6 \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

# Копіювання з stage 1 виключно скомпільований виконуваний файл
COPY --from=builder /app/build/cpp-web-service .

# Відкривання порту 8080
EXPOSE 8080

# Точка входу для запуску сервісу
ENTRYPOINT ["./cpp-web-service"]
