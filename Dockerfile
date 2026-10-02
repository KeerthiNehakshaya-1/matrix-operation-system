FROM debian:bookworm-slim

RUN apt-get update && \
    apt-get install -y g++ && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY backend /app/backend
COPY frontend /app/frontend

WORKDIR /app/backend

RUN g++ -std=c++17 -pthread server.cpp -o server

CMD ["./server"]