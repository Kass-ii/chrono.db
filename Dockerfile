
FROM gcc:latest

WORKDIR /app

COPY . .

RUN gcc -o mydb *.c

CMD ["./mydb"]